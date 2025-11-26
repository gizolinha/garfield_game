/* definicoes basicas para os aspectos do jogo*/
#ifndef GAME_DEF 
#define GAME_DEF

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

/* constantes globais */
#define LARGURA_TELA 900
#define ALTURA_TELA 800
#define FPS 60
#define GRAVIDADE 1.5f
#define VELOCIDADE_PULO -32.0f 
#define MAX_VEL_QUEDA 20.0f 
#define QUEDA_MORTE (ALTURA_TELA + 100.0f) 

/* constantes player */
#define ESCALA_PLAYER 0.4 
#define FRAMES_PARADO 5 //quantidade de sprites
#define FPS_PARADO 15
#define FRAMES_ANDANDO 8
#define FPS_ANDANDO 6
#define FRAMES_PULANDO 9
#define FPS_PULANDO 6
#define FRAMES_ABAIXADO 3
#define FPS_ABAIXADO 6 //velocidade da animacao
#define NORMAL_SPEED 5.0f

/* constantes obstaculos */
#define ESCALA_OBST 0.5f
#define FRAMES_GREEN 5
#define FRAMES_FLOWY 5
#define FRAMES_CLOCK 2
#define FPS_OBSTACLE 4

/*estados do jogo */
typedef enum {
    MENU,
    JOGANDO,
    FIM_DE_JOGO,
    PAUSE,
    SAIR,
    VITORIA,
} gamestate;

/* estados para o botao de menu */
typedef enum {
    OPCAO_SAIR,
    OPCAO_INICIAR, 
    OPCAO_MENU,
} menu;

/* tipos de obstaculo */
enum {
    OBS_TYPE_GREEN = 0,
    OBS_TYPE_FLOWY = 1,
    OBS_TYPE_CLOCK = 2
};

#endif /* GAME_DEF */