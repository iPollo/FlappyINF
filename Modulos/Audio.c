
// Numero máximo de sons
#define MAX_SOUNDS 36

// ===========================================================================
// 		Variáveis
// ===========================================================================

// Declaração global da música do menu e do jogo
Music SOM_MENU;
Music SOM_GAME;

// Enum dos efeitos sonoros
enum{
	SOM_GAMEOVER,
	SOM_MENU_BUTTON,
	SOM_PULO,
    SOM_PONTO,
};

// Declaração global dos efeitos sonoros
Sound sons[MAX_SOUNDS];

// ===========================================================================
// 		Funções
// ===========================================================================

// Responsável por reproduzir/pausar a música do menu
void TocarMusicaMenu(bool play){

	// Caso true toca a música
	if(play){
		SOM_MENU = LoadMusicStream(TextFormat("%s/Sons/MusicaMenu.mp3", GetWorkingDirectory())); 
		SOM_MENU.looping = true;
		PlayMusicStream(SOM_MENU);
	}

	// Caso contrário para a música
	else{
		StopMusicStream(SOM_MENU);
		UnloadMusicStream(SOM_MENU);
	}
}

// Responsável por reproduzir/pausar a música do jogo
void TocarMusicaJogo(bool play){

	// Caso true toca a música
	if(play){
		SOM_GAME = LoadMusicStream(TextFormat("%s/Sons/GameSong.mp3", GetWorkingDirectory())); 
		SOM_GAME.looping = true;
		PlayMusicStream(SOM_GAME);
		SetMusicVolume(SOM_GAME, 0.2);    
	}

	// Caso false para a música
	else{
		StopMusicStream(SOM_GAME);
		UnloadMusicStream(SOM_GAME);
	}
}

// Inicializa os efeitos sonoros, carregando-os respectivamente na array
void InicializarAudio(){
	sons[SOM_MENU_BUTTON] = LoadSound(TextFormat("%s/Sons/SomBotao.wav", GetWorkingDirectory()));
	sons[SOM_GAMEOVER] = LoadSound(TextFormat("%s/Sons/SomBatida.mp3", GetWorkingDirectory()));
	sons[SOM_PULO] = LoadSound(TextFormat("%s/Sons/SomPulo.mp3", GetWorkingDirectory()));
    sons[SOM_PONTO] = LoadSound(TextFormat("%s/Sons/SomPonto.mp3", GetWorkingDirectory()));
}


// Atualiza as músicas a cada frame (como demonstrado na documentação da biblioteca)
void AtualizarAudio(){
	if(IsMusicStreamPlaying(SOM_MENU)) UpdateMusicStream(SOM_MENU);
	if(IsMusicStreamPlaying(SOM_GAME)) UpdateMusicStream(SOM_GAME);
}