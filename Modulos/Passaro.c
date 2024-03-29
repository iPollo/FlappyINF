
// ===========================================================================
// 		Constantes
// ===========================================================================

// Propriedades constantes do pássaro
const float GRAVIDADE = 0.3f;
const float FORCA_PULO = -8.0f;

// ===========================================================================
// 		Variáveis
// ===========================================================================

// Define o passaro e suas propriedades
typedef struct Passaro
{    
    Vector2 posicao;
    Vector2 velocidade;

} Passaro;

// Define o pássaro no jogo
Passaro passaro;

// ===========================================================================
// 		Funções
// ===========================================================================

// Cria o pássaro no meio da tela
void CriarPassaro(Vector2 posicaoInicial){
    passaro.posicao = posicaoInicial;
    passaro.velocidade.x = 0;
    passaro.velocidade.y = 0;
}

// Atualiza o pássaro e sua posição a cada frame
void AtualizarPassaro(){

    // Executa apenas se estiver rodando o jogo
    if(!jogoRodando) return;

    // Executa o pulo do pássaro, aplicando uma força vertical
    if(IsKeyPressed(KEY_SPACE)){
        passaro.velocidade.y = FORCA_PULO;
        PlaySound(sons[SOM_PULO]);
    }

    // Aplica a gravidade 
    passaro.velocidade.y += GRAVIDADE;
    passaro.posicao.y += passaro.velocidade.y;

    // Desenha o pássaro
    DrawTexture(sprites[SPRITE_PASSARO], passaro.posicao.x, passaro.posicao.y, WHITE);

    // Verifica se o passaro está dentro da tela
    if(passaro.posicao.y < 0 || passaro.posicao.y > SCREEN_HEIGHT - 150){
            fimDeJogo = true;
            TocarMusicaJogo(false);
            PlaySound(sons[SOM_GAMEOVER]);
    }
}

// Função que inicializa o pássaro quando o programa inicia
void InicializarPassaro(){
    CriarPassaro((Vector2){500, 250});
}