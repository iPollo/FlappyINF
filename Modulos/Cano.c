
// Define inicial da criação dos canos
#define MAXIMOS_CANOS_CRIADOS 500

// ===========================================================================
// 		Variáveis
// ===========================================================================

// Conta quantos canos foram criados
int contadorCanos = -1;

// Estrutura que define o cano
typedef struct Cano
{
    Vector2 posicao; // Posicao no mundo
    int espacoEntre; // Espaco entre cano de cima e o de baixo
    int distanciaCima; // Distância entre o topo da tela e a parte de baixo do cano superior
    int distanciaBaixo; // Distância entre o fim da tela e a parte de cima do cano inferior
    int distanciaDoCeu; //  Distancia do céu até o espaço entre os canos
    bool colidiu; // Indica se o pássaro colidiu com aquele cano específico
    bool visivel; // Indica se o cano está visível na tela
    bool canoCriado; // Indica que o cano já foi criado no laço

} Cano;

// Definição dos canos
Cano canos[MAXIMOS_CANOS_CRIADOS];

// ===========================================================================
// 		Dependencias
// ===========================================================================

// ===========================================================================
// 		Funções
// ===========================================================================

// Função que cria um cano considerando a contagem total de canos e a posição do último cano criado
void CriarCano(){

    // Verifica a quantidade total de canos criados e se atigiu o limite (apenas para performance)
    if(contadorCanos >= MAXIMOS_CANOS_CRIADOS) return;

    // Ao chamar a função aumenta o contador de canos
    contadorCanos++;

    // Se for o primeiro cano a ser criado: Cria ele 5 pixels a partir do fim da tela 
    if(contadorCanos == 0){
        canos[contadorCanos].posicao.x = SCREEN_WIDTH + 5;
    }

    // Caso o cano atual a ser criado não seja o primeiro: Cria o próximo baseado na posição do último
    else{

        // Ou seja, a posição X do novo canos será a posição X do cano anterior + o GAP entre eles atual
        canos[contadorCanos].posicao.x = canos[contadorCanos-1].posicao.x + (dificuldade[GAP]);
    }

    // Define as propriedades e valores do cano criado baseado na dificuldade escolhida
    canos[contadorCanos].espacoEntre = dificuldade[DIF_MAX_ALTURA]; // Espaço entre o cano superior e o inferior
    canos[contadorCanos].distanciaCima = GetRandomValue(0, SCREEN_HEIGHT-150-canos[contadorCanos].espacoEntre); // Valor aleatório que define o altura que a abertura estará
    canos[contadorCanos].distanciaBaixo = canos[contadorCanos].distanciaCima+canos[contadorCanos].espacoEntre; // Valor aleatório que define o altura que a abertura estará
    canos[contadorCanos].colidiu = false;
    canos[contadorCanos].canoCriado = false;

    // Função que faz uma contagem e altere os dados da dificuldade de acordo com a posição e o número de canos criados
    IncrementarPontosParaDificuldade();

}

// Atualiza os canos em tempo real (chamado a cada frame)
void AtualizarCano(){

    // Executa apenas se o jogo estiver rodando
    if(!jogoRodando || fimDeJogo) return;

    // Atualiza a posição dos canos e desenha eles na tela
    for(int i = 0; i < MAXIMOS_CANOS_CRIADOS; i++){
        canos[i].posicao.x = canos[i].posicao.x - dificuldade[VEL_OBSTACULOS];        
       
        // Desenha os canos na tela se a posição deles for visivel, ou seja, se o cano estiver dentro dos limites da tela
        if(canos[i].posicao.x < SCREEN_WIDTH && canos[i].posicao.x + 100 > 0){
            DrawTexture(sprites[SPRITE_CANO_CIMA], canos[i].posicao.x, (-800+canos[i].distanciaCima), WHITE);
            DrawTexture(sprites[SPRITE_CANO_BAIXO], canos[i].posicao.x, canos[i].distanciaBaixo, WHITE);
        }
       
        // Se colidir no cano é fim de jogo
        if(CheckCollisionRecs((Rectangle){canos[i].posicao.x, canos[i].posicao.y, 100, canos[i].distanciaCima}, (Rectangle){passaro.posicao.x+20, passaro.posicao.y+20, 25, 25}) || CheckCollisionRecs((Rectangle){canos[i].posicao.x, canos[i].distanciaBaixo, 100, SCREEN_HEIGHT}, (Rectangle){passaro.posicao.x+20, passaro.posicao.y+20, 25, 25})){
            fimDeJogo = true;
            TocarMusicaJogo(false);
            PlaySound(sons[SOM_GAMEOVER]);
        }

        // Se não aumenta a pontuação
        else if(CheckCollisionRecs((Rectangle){passaro.posicao.x+20, passaro.posicao.y+20, 25, 25}, (Rectangle){canos[i].posicao.x, canos[i].posicao.y, 100, SCREEN_HEIGHT})){

            // Verifica se já contou a pontuação, para não contabilizar mais de uma vez
            if(!canos[i].colidiu){
            pontuacao++;
            PlaySound(sons[SOM_PONTO]);
            AtualizarVelocidade();
            canos[i].colidiu = true;
            }
        }
        
    }

}

// Função chamada quando o programa inicia, criando todos os canos
void InicializarCano(){

    contadorCanos = -1;

    for(int i = 0; i < MAXIMOS_CANOS_CRIADOS; i++){
        CriarCano();
    }
}