
// Cores utilizadas para debug
#define COLLOR_GOLDEN  CLITERAL(Color){ 255, 139, 49, 255 }

// ===========================================================================
// 		Variáveis
// ===========================================================================

// Enums para controlar as opções do menu (botões selecionados)
enum{
	OPCAO_JOGAR,
	OPCAO_DIFICULDADE,
	OPCAO_RANKING,
	OPCAO_SAIR,
};

// Enum para controlar os menus do jogo
enum{
	MENU_PRINCIPAL,
	MENU_RANKING,
	MENU_DIFICULDADE,
};

// Dados de controle do menu e dos botões 
int atualBotaoSelecionado = OPCAO_JOGAR;
int atualMenu = MENU_PRINCIPAL;

// Define a posição dos botões no menu principal
Vector2 botoes[4];

// ===========================================================================
// 		Funções
// ===========================================================================

// Inicializa o módulo do menu principal
void InicializarMenu(){

	// Define o status do jogo como não rodando
	jogoRodando = false;

	// Define a posição dos botões no menu principal
	botoes[0] = (Vector2){90, 439};
	botoes[1] = (Vector2){617, 439};
	botoes[2] = (Vector2){90, 558};
	botoes[3] = (Vector2){617, 558};
}

// Atualiza os dados e informações do módulo do menu
void AtualizarMenu(){

	// Executa apenas se não estiver rodando o jogo
	if(jogoRodando || fimDeJogo) return;

	// Processa a tecla enter e atualiza o menu (abre o menu de scoreboard caso clique ou inicializa o jogo em sí)
	if(IsKeyPressed(KEY_ENTER)){
		if((atualBotaoSelecionado == OPCAO_RANKING) && (atualMenu == MENU_PRINCIPAL)){
			atualMenu = MENU_RANKING;
		}
		else if(atualMenu == MENU_RANKING) atualMenu = MENU_PRINCIPAL;

	}

	// Desenha o menu do ranking
	if(atualMenu == MENU_RANKING){

		// Desennha o plano de fundo do ranking
		DrawTexture(sprites[SPRITE_MENURANKING], 0, 0, WHITE);  

		// Inclui os dados do ranking na tela para os melhores 5
		for(int i = 0; i < 5; i++){

			char name[16] = "Apollo";
			TextCopy(name, ranking[i].playerName);

			char date[32] = "DIFICULDADE 1";
			TextCopy(date, TextFormat("DIFICULDADE: %d", ranking[i].level));

			char pts[16] = "1000 PTS";
			TextCopy(pts, TextFormat("%d PONTOS", ranking[i].score));

			int dateSize, ptsSize;

			dateSize = MeasureText(date, 25);
			ptsSize = MeasureText(pts, 25);

			DrawText(TextFormat("%d.", i+1), 154, 378 + (64 * i), 25, DARKGRAY);
			DrawText(name, 180, 378 + (64 * i), 25, DARKGRAY);
			DrawText(date, 590 - dateSize/2, 378 + (64 * i), 25, DARKGRAY);
			DrawText(pts, 1045 - ptsSize, 378 + (64 * i), 25, DARKGRAY);

		}

		return;
	}

	// Desenha o menu da escolhe de dificuldade
	if(atualMenu == MENU_DIFICULDADE){
	
		// Escolhe a dificuldade de acordo com o botão pressionado
		if(IsKeyPressed(KEY_KP_1)){
			dificuldadeArquivo = 1;
			PlaySound(sons[SOM_MENU_BUTTON]);
		} 	
		if(IsKeyPressed(KEY_KP_2)){
			dificuldadeArquivo = 2;
			PlaySound(sons[SOM_MENU_BUTTON]);
		}
		if(IsKeyPressed(KEY_KP_3)){
			dificuldadeArquivo = 3;
			PlaySound(sons[SOM_MENU_BUTTON]);
		}

		// Desenha o botão selecionado
		switch(dificuldadeArquivo){
			case 1: DrawTexture(sprites[SPRITE_DIFICULDADE1], 0, 0, WHITE);	break;
			case 2: DrawTexture(sprites[SPRITE_DIFICULDADE2], 0, 0, WHITE);	break;
			case 3: DrawTexture(sprites[SPRITE_DIFICULDADE3], 0, 0, WHITE);	break;
		}

		// Caso o enter seja pressionado volta ao menu principal e atualiza a dificuldade
		if(IsKeyPressed(KEY_ENTER)){
			atualMenu = MENU_PRINCIPAL;
			EscolherDificuldade(dificuldadeArquivo);
		}

		return;
	}

	// Desenha os botões e o asset do menu principal
	DrawTexture(sprites[SPRITE_MENUBACKGROUND], 0, 0, WHITE);  
	DrawTexturePro(sprites[SPRITE_MENUBOTOES], (Rectangle){0,0,500,150}, (Rectangle){90, 439, 500,150}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(sprites[SPRITE_MENUBOTOES], (Rectangle){0,150,500,150}, (Rectangle){617, 439, 500,150}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(sprites[SPRITE_MENUBOTOES], (Rectangle){0,150*2,500,150}, (Rectangle){90, 558, 500,150}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(sprites[SPRITE_MENUBOTOES], (Rectangle){0,150*3,500,150}, (Rectangle){617, 558, 500,150}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(sprites[SPRITE_MENUBOTOES], (Rectangle){500,150*atualBotaoSelecionado,500,150}, (Rectangle){botoes[atualBotaoSelecionado].x, botoes[atualBotaoSelecionado].y, 500,150}, (Vector2){0,0},0, WHITE);

	// Atualiza o botão selecionado e toca o efeito sonoro caso clique na setas do teclado
	if(IsKeyPressed(KEY_RIGHT)){
		atualBotaoSelecionado++;
		if(atualBotaoSelecionado == 4) atualBotaoSelecionado = 0;
		PlaySound(sons[SOM_MENU_BUTTON]);

	}

	// Atualiza o botão selecionado e toca o efeito sonoro caso clique na setas do teclado
	if(IsKeyPressed(KEY_LEFT)){
		atualBotaoSelecionado--;
		if(atualBotaoSelecionado == -1){
			atualBotaoSelecionado = 3;
		}
		PlaySound(sons[SOM_MENU_BUTTON]);
	}

	// Verifica qual botão o jogador selecionou e clicou
	if(IsKeyPressed(KEY_ENTER)){
		if(atualBotaoSelecionado == OPCAO_SAIR) CloseWindow();
		else if(atualBotaoSelecionado == OPCAO_JOGAR) IniciarJogo();
		else if(atualBotaoSelecionado == OPCAO_DIFICULDADE) atualMenu = MENU_DIFICULDADE;
		PlaySound(sons[SOM_MENU_BUTTON]);
	}
}