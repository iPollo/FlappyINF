
// ===========================================================================
// 		Variaveis
// ===========================================================================

// Enum das propriedades e variáveis de dificuldade de acordo com o PDF do moodle
enum{
    SCORE_THERESHOLD,
    GAP,
    INC_GAP,
    DIF_MAX_ALTURA,
    INC_DIF_MAX_ALTURA,
    VEL_OBSTACULOS,
    INC_VEL_OBSTACULOS,
};

// Variável que gerencia as propriedades das dificuldades
int dificuldade[7];

// Contagem do scoreTheresHold e VelScoreTheresHold (de quantos em quantos pontos a velocidade e a dificuldade muda)
int scoreTheresHold = 0;
int velScoreTheresHold = 0;

// Dificuldade escolhida pelo jogador
int dificuldadeArquivo = 1;

// ===========================================================================
// 		Funções
// ===========================================================================


// FUnção chamada quando o jogador escolhe uma dificuldade, atualizando os valores lendo o arquivo da dificuldade específica
void EscolherDificuldade(int dif){

    // Abre o arquivo para leitura (escolhe o arquivo padrão como 1)
    FILE *arquivo = fopen("Dificuldades/dificuldade1.txt", "r");

    // Abre o arquivo para leitura caso tenha escolhido alguma dificuldade
    switch (dif)
    {
        case 1: arquivo = fopen("Dificuldades/dificuldade1.txt", "r"); break;
        case 2: arquivo = fopen("Dificuldades/dificuldade2.txt", "r"); break;
        case 3: arquivo = fopen("Dificuldades/dificuldade3.txt", "r"); break;
        
        default:
            break;
    }

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return; // Encerra o programa com código de erro
    }

    // Lê os valores do arquivo e os armazena nas variáveis
    fscanf(arquivo, "%d %d %d %d %d %d %d", &dificuldade[0], &dificuldade[1], &dificuldade[2], &dificuldade[3], &dificuldade[4], &dificuldade[5], &dificuldade[6]);

    // Fecha o arquivo após a leitura
    fclose(arquivo);

    // Zera os valores
    scoreTheresHold = 0;
    velScoreTheresHold = 0;
}

// Função que muda os valores da dificuldade em tempo de jogo caso tenha atingido o ScoreThereshold
void AtualizarDificuldade(){

    // Verifica se já atingiu o limite
    if(dificuldade[GAP] <= 0 || dificuldade[DIF_MAX_ALTURA] <= 50 ) return; 

    // Atualiza os valores
    dificuldade[GAP] -= dificuldade[INC_GAP];
    dificuldade[DIF_MAX_ALTURA] -= dificuldade[INC_DIF_MAX_ALTURA]; 

}

// Função que muda os valores da velocidade em tempo de jogo caso tenha atingido o ScoreThereshold
void AtualizarVelocidade(){
    velScoreTheresHold++;
    if(velScoreTheresHold == dificuldade[SCORE_THERESHOLD]){
        dificuldade[VEL_OBSTACULOS] += dificuldade[INC_VEL_OBSTACULOS];
        velScoreTheresHold = 0;
    }
}

// Função que faz a contagem dos pontos e verifica se atingiu o limite do scoreTheresHold 
void IncrementarPontosParaDificuldade(){
    scoreTheresHold++;
    if(scoreTheresHold == dificuldade[SCORE_THERESHOLD]){
        scoreTheresHold = 0;
        AtualizarDificuldade();
    }
}