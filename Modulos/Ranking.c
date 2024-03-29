
#define MAX_TOPSCORE 5

// ===========================================================================
// 		Variaveis
// ===========================================================================

// Estrutura de dados para o topScore (top 5 do scoreboard)
typedef struct TOPSCORE{

    char playerName[16];
    int level;
    int score;

}TOPSCORE;

// Incializa o topscore 
TOPSCORE ranking[MAX_TOPSCORE];


// ===========================================================================
// 		Funções
// ===========================================================================

// Carrega do arquivo binario os dados do scoreboard
void CarregarArquivoRanking(){

    // Abre o arquivo
    FILE *arq = fopen(TextFormat("%s/ranking.bin", GetWorkingDirectory()), "rb");

    // Caso não exista cria um com os Dados ("Vazio", 0, 0)
    if(arq == NULL){

        // Inicializa os dados
        for(int i = 0; i < MAX_TOPSCORE; i++){
            ranking[i] = (TOPSCORE){"Vazio", 0, 0};
        }

        // Abre e cria um novo arquivo
        FILE *newArq = fopen(TextFormat("%s/ranking.bin", GetWorkingDirectory()), "wb");

        // Informa que deu erro na criação do arquivo
        if(newArq == NULL){
            TraceLog(LOG_INFO, " - Erro ao criar arquivo ranking.bin");
            return;
        }

        // Escreve os dados padrões no arquivo binário e fecha o arquivo
        fwrite(&ranking[0], sizeof(TOPSCORE), MAX_TOPSCORE, newArq);
        fclose(newArq);
        return;
    }

    // Caso o arquivo já exista lê os dados dele e coloca na estrutura TOPSCORE e fecha o arquivo
    fread(&ranking[0], sizeof(TOPSCORE), MAX_TOPSCORE, arq);
    fclose(arq);
}


// Salva os dados da array da estrutura topscore no arquivo binário
void SalvarArquivoRanking(){

    // Abre e verifica o arquivo
    FILE *newArq = fopen("ranking.bin", "wb");

    if(newArq == NULL){
        TraceLog(LOG_INFO, " - Erro ao salvar arquivo ranking.bin");
        return;
    }

    // Salva no arquivo os dados da array
    fwrite(&ranking, sizeof(TOPSCORE), MAX_TOPSCORE, newArq);
    
    // Fecha o arquivo
    fclose(newArq);
}

// Atualiza os dados do topscore e insere o jogador na posição caso ele atinja um novo recorde
void AtualizarRanking(int pos, char name[]){
    
    // Move os elementos da array um index para cima
    for(int i = MAX_TOPSCORE-1; i > pos; i--){
        ranking[i] = ranking[i-1];
    }

    // Insere o jogador na posição que bateu o recorde
    TextCopy(ranking[pos].playerName, name);
    ranking[pos].score = pontuacao;
    ranking[pos].level = dificuldadeArquivo;
}

// Verifica se o jogador atingiu um novo recorde e retorna a posição 
int VerificarPontuacao(){

    for(int i = 0; i < MAX_TOPSCORE; i++){
        if(pontuacao >= ranking[i].score) return i;
    }
    
    return -1;
}



