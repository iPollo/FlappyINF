
// ===========================================================================
// 		Imports Nativos
// ===========================================================================

// Bibliotecas Nativas e Raylib
#ifndef _RAYLIB_H
#define _RAYLIB_H
    #include "stdio.h"
    #include "string.h"
    #include "stdlib.h"
    #include "time.h"
    #include "math.h"
    #include "stdbool.h"
    #include "raylib.h"
#endif


// ===========================================================================
// 		Variáveis Globais/Constantes
// ===========================================================================

// Globais constantes
const int SCREEN_WIDTH = 1200;  
const int SCREEN_HEIGHT = 800;
    
// Globais de gerenciamento do game loop
bool jogoRodando = false;
bool fimDeJogo = false;

// Dados do inputBox (caixa para digitar nome quando perder o jogo)
char gameOverInputBox[16];
int letterCount = 0;

// Declaração das Funções principais
void IniciarJogo();
void FimDeJogo();

// ===========================================================================
// 		Dependencias do jogo (Módulos)
// ===========================================================================

// Inclui todos os arquivos e módulos neste única arquivo (FlappyINF)
#include "Modulos/Audio.c"
#include "Modulos/Dificuldade.c"
#include "Modulos/Pontuação.c"
#include "Modulos/Ranking.c"
#include "Modulos/Sprites.c"
#include "Modulos/Passaro.c"
#include "Modulos/Cano.c"
#include "Modulos/Menu.c"

// ===========================================================================
// 		Core
// ===========================================================================

// Função main (entrada)
int main(void){
	
	// Inicializa a janela (Raylib) no centro da tela
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FlappyINF");
	SetWindowPosition((GetMonitorWidth(GetCurrentMonitor())/2) - SCREEN_WIDTH/2, (GetMonitorHeight(GetCurrentMonitor())/2 - SCREEN_HEIGHT/2)+ 50);
   
    // Define como jogo rodando a false, assim a primeira coisa que aparece é o menu
    jogoRodando = false;

	// Inicializa o dispositivo de áudio (Raylib)
	InitAudioDevice();

	// Define o FPS para 60 (Raylib)
	SetTargetFPS(60);

    // Carrega o arquivo do ranking (ranking.bin) que contém as 5 melhores pontuações
    CarregarArquivoRanking();

	// Inicializa cada arquivo e suas dependências (Módulos)
    InicializarAudio();
    InicializarSprites();
    InicializarMenu();  

    // Como o menu é o primeiro a aparecer, primeiramente bota pra tocar a música do menu
    TocarMusicaMenu(true);

	// Game Loop principal
    while (!WindowShouldClose()) 
    {
    	// Raylib (Desenha e atualiza as 'variáveis do jogo)
        BeginDrawing();

        // Processa cada módulo e suas dependências e as atualiza a cada frame

        // Funções que atualizam caso o jogo esteja rodando
        if(!fimDeJogo && jogoRodando){
            MostrarFundo();
            AtualizarPassaro();
            AtualizarCano();
            MostrarChao();
            AtualizarPontuacao();
        }

        // Funções que atualizam caso o jogador tenha batido (mostra a tela de fim de jogo)
        else if(fimDeJogo && jogoRodando){
            MostrarFundo();
            MostrarChao();
            FimDeJogo();
        }

        // Função que atualiza caso o jogador estja no menu principal
        else{
            AtualizarMenu();
        }

        // Atualiza o audio para as músicas que tocam durante o jogo (Necessário de acordo com a documentação do Raylib)
        AtualizarAudio();

        // Raylib (Finaliza a atualização do frame)
        EndDrawing();

    }

    // Finaliza o dispositivo de áudio (Raylib)
    CloseAudioDevice(); 

    // Salva o ranking no arquivo
    SalvarArquivoRanking();
    
}

// Função que inicia o jogo (com o pássaro) e prepara as variáveis
void IniciarJogo(){

	// Atualiza o status do jogo
	jogoRodando = true;
	fimDeJogo = false;

    // Zera a pontuaçaõ
    pontuacao = 0;

    // Atualiza a dificuldade para a opção escolhida (padrão = 1)
    EscolherDificuldade(dificuldadeArquivo);

    // Inicializa novamente os módulos necessários que serão utilizados no jogo (pássaro e canos)
    InicializarPassaro();
    InicializarCano();

    // Para de tocar a música do menu e começa a tocar a música do jogo
    TocarMusicaMenu(false);
    TocarMusicaJogo(true);
}

// Função que chama o fim de jogo (caso o jogador colida com um cano) e mostra a tela dde gameover
void FimDeJogo(){

    // Sprite da tela de fundo de game over
    DrawTexture(sprites[SPRITE_FIMDEJOGO], 0, 0, WHITE);  

    // Mostra a quantidade de pontos e o level
    DrawText("PONTOS:", 300, 458, 20, WHITE);
    DrawText(TextFormat("%d", pontuacao), 900 - MeasureText(TextFormat("%d", pontuacao), 20), 458, 20, WHITE);

    // Atualiza os dados da inputbox, coletando o caractere e inserindo na string (nome do jogador que ele digite quando perde)
    char key = GetCharPressed();

    // Insere o caractere na array e define um novo final
    if ((key >= 32) && (key <= 125) && (letterCount < 15))
    {
        gameOverInputBox[letterCount] = (char)key;
        gameOverInputBox[letterCount+1] = '\0'; // Add null terminator at the end of the string.
        letterCount++;
    }

    // Apaga um caractere da array e define um novo final
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        letterCount--;
        if (letterCount < 0) letterCount = 0;
        gameOverInputBox[letterCount] = '\0';
    }

    // Processa os dados e o nome do jogador e volta ao menu principal, atualizando também o ranking caso necessário
    if(IsKeyPressed(KEY_ENTER)){
        
        // Atualiza o ranking caso atinja um novo recorde
        int novaPosicao = VerificarPontuacao();
        if(novaPosicao != -1){
           AtualizarRanking(novaPosicao, gameOverInputBox);
        }

        // Restaura as variáveis do jogo e volta para o menu
        fimDeJogo = false;
        jogoRodando = false;
        TocarMusicaMenu(true);

    }

    // Desenha o nome digitado e a tecla Enter apra continuar
    DrawText(TextFormat("NOME [%d/16]: %s", letterCount+1, gameOverInputBox), 582 - MeasureText(TextFormat("NOME[%d/16]: %s", letterCount, gameOverInputBox), 20)/2, 555, 20, WHITE);
    DrawText("PRESSIONE [E N T E R] PARA CONTINUAR", 582 - MeasureText("PRESSIONE [E N T E R] PARA CONTINUAR", 10)/2, 620, 10, WHITE);

}