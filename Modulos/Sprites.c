// Define o número máximo de textras do jogo
#define MAXIMO_SPRITE 32

// ===========================================================================
// 		Variáveis
// ===========================================================================

// Enum responsável por controlar as texturas do jogo
enum{
	SPRITE_CANO_BAIXO,
	SPRITE_CANO_CIMA,
	SPRITE_FUNDO,
	SPRITE_CHAO,
	SPRITE_PASSARO,
	SPRITE_MENUBOTOES,
	SPRITE_MENUBACKGROUND,
	SPRITE_FIMDEJOGO,
	SPRITE_DIFICULDADE1,
	SPRITE_DIFICULDADE2,
	SPRITE_DIFICULDADE3,
	SPRITE_MENURANKING,
};

// Inicializa as texturas do jogo usando um Texture2D (Struct do próprio Raylib)
Texture2D sprites[MAXIMO_SPRITE];

// ===========================================================================
// 		Funções
// ===========================================================================

// Inicializa e carrega todas as textura (sprites)
void InicializarSprites(){

	sprites[SPRITE_CANO_BAIXO] = LoadTexture(TextFormat("%s/Sprites/Cano_Baixo.png", GetWorkingDirectory()));
	sprites[SPRITE_CANO_CIMA] = LoadTexture(TextFormat("%s/Sprites/Cano_Cima.png", GetWorkingDirectory()));
	sprites[SPRITE_FUNDO] = LoadTexture(TextFormat("%s/Sprites/Fundo.png", GetWorkingDirectory()));
	sprites[SPRITE_CHAO] = LoadTexture(TextFormat("%s/Sprites/Chao.png", GetWorkingDirectory()));
	sprites[SPRITE_PASSARO] = LoadTexture(TextFormat("%s/Sprites/Passaro.png", GetWorkingDirectory()));
	sprites[SPRITE_MENUBOTOES] = LoadTexture(TextFormat("%s/Sprites/Botoes_Menu_Principal.png", GetWorkingDirectory()));
	sprites[SPRITE_MENUBACKGROUND] = LoadTexture(TextFormat("%s/Sprites/Menu_Background.png", GetWorkingDirectory()));
	sprites[SPRITE_FIMDEJOGO] = LoadTexture(TextFormat("%s/Sprites/Fim_De_Jogo.png", GetWorkingDirectory()));
	sprites[SPRITE_DIFICULDADE1] = LoadTexture(TextFormat("%s/Sprites/Dificuldade_1.png", GetWorkingDirectory()));
	sprites[SPRITE_DIFICULDADE2] = LoadTexture(TextFormat("%s/Sprites/Dificuldade_2.png", GetWorkingDirectory()));
	sprites[SPRITE_DIFICULDADE3] = LoadTexture(TextFormat("%s/Sprites/Dificuldade_3.png", GetWorkingDirectory()));
	sprites[SPRITE_MENURANKING] = LoadTexture(TextFormat("%s/Sprites/Menu_Ranking.png", GetWorkingDirectory()));
}

// Desenha o background do FlappyInf
void MostrarFundo(){
	DrawTexture(sprites[SPRITE_FUNDO], 0, 0, WHITE);
}

// Desenha o chão do flappyInf
void MostrarChao(){
	DrawTexture(sprites[SPRITE_CHAO], 0, 0, WHITE);
}
