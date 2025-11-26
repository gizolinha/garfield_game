#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "resources.h"

/* acessar a struct de  recursos do allegro */
gameresources assets;

/* carrega todas as imagens, fontes, etc */
bool resources_load_all() {
    char path[100];

    /* carregamento animacao player parado */
    for(int i = 0; i < FRAMES_PARADO; i++) {
        // cria o caminho
        snprintf(path, 100, "assets/personagens/garfield/parado/parado_%d.png", i);
        
        assets.player_parado[i] = al_load_bitmap(path);
        
        if (!assets.player_parado[i]) {
            perror("ERRO: Falha ao carregar frame parado");
            return false;
        }
    } 
    /* carregamento animacao palyer andando */
    for(int i = 0; i < FRAMES_ANDANDO; i++) {
        snprintf(path, 100, "assets/personagens/garfield/andando/andando_%d.png", i);

        assets.player_andando[i] = al_load_bitmap(path);

        if(!assets.player_andando[i]) {
            perror("ERRO: Falha ao carregar frame andando");
            return false;
        }
    }
    /* carregamento animacao player pulando */
    for(int i = 0; i < FRAMES_PULANDO; i++) {
        snprintf(path, 100, "assets/personagens/garfield/pulando/pulando_%d.png", i);

        assets.player_pulando[i] = al_load_bitmap(path);

        if(!assets.player_pulando[i]) {
            perror("ERRO: Falha ao carregar frame pulando");
            return false;
        }
    }
    /* carregamento animacao play abaixado */
     for(int i = 0; i < FRAMES_ABAIXADO; i++) {
        snprintf(path, 100, "assets/personagens/garfield/abaixado/abaixado_%d.png", i);

        assets.player_abaixado[i] = al_load_bitmap(path);

        if(!assets.player_abaixado[i]) {
            perror("ERRO: Falha ao carregar frame abaixado");
            return false;
        }
    }
    /* carregamento dos sprites de vidas */
    for(int i = 0; i < 5; i++) {
        snprintf(path, 100, "assets/personagens/garfield/vida/vida_%d.png", i);
        
        assets.sprites_vida[i] = al_load_bitmap(path);

        if(!assets.sprites_vida[i]) {
            perror("ERRO: Falha ao carregar sprite de vida");
            return false;
        }
    }

    /* Carregamento sprites vilao green */
    for(int i = 0; i < FRAMES_GREEN; i++) {
        snprintf(path, 100, "assets/personagens/oddys/green/green_%d.png", i);

        assets.obst_green[i] = al_load_bitmap(path);

        if(!assets.obst_green[i]) {
            perror("ERRO: Falha ao carregar frame do oddys green");
            return false;
        }
    }

    /* Carregamento sprites vilao flowy */
    for(int i = 0; i < FRAMES_FLOWY; i++) {
        snprintf(path, 100, "assets/personagens/flowy/flowy_%d.png", i);

        assets.obst_flowy[i] = al_load_bitmap(path);

        if(!assets.obst_flowy[i]) {
            perror("ERRO: Falha ao carregar frame do flowy");
            return false;
        }
    }

    /* Carregamento sprites vilao clock */
    for(int i = 0; i < FRAMES_CLOCK; i++) {
        snprintf(path, 100, "assets/personagens/clock/clock_%d.png", i);

        assets.obst_clock[i] = al_load_bitmap(path);

        if(!assets.obst_clock[i]) {
            perror("ERRO: Falha ao carregar frame do clock");
            return false;
        }
    }

    /* carregar sprite de dash */
    assets.player_dash = al_load_bitmap("assets/personagens/garfield/dash/dash_0.png");
    if(!assets.player_dash) {
        perror("ERRO: Falha ao carregar dash_0.png");
        return false;
    }

    /* carregar sprite da lasanha da vitoria */
    assets.lasanha = al_load_bitmap("assets/itens/lasagna.png");
    if(!assets.lasanha) {
        perror("ERRO: Falha ao carregar lasagna.png");
        return false;
    }

    /* carregar sprite dao ursinho da vida */
    assets.urso = al_load_bitmap("assets/itens/ursi.png");
    if(!assets.urso) {
        perror("ERRO: Falha ao carregar ursi.png");
        return false;
    }

    /* carregamento da tela de menu*/
    assets.fundo_menu = al_load_bitmap("assets/background/fundo_menu.png");
    if(!assets.fundo_menu) {
        perror("ERRO: Falha ao carregar fundo_menu.png");
        return false;
    }
    /* carregamento da tela de game over */
    assets.fundo_gameover = al_load_bitmap("assets/background/tela_gameover.png");
    if(!assets.fundo_gameover) {
        perror("ERRO: Falha ao carregar tela_gameover.png");
        return false;
    }
    /* carregamento da tela de vitoria */
    assets.fundo_vitoria = al_load_bitmap("assets/background/tela_vitoria.png");
    if(!assets.fundo_vitoria) {
        perror("ERRO: Falha ao carregar tela_vitoria.png");
        return false;
    }
    /* carregamento do cenario do fundo do jogo*/
    assets.fundo_game = al_load_bitmap("assets/background/fundo_jogo2.png");
    if (!assets.fundo_game) {
        perror("ERRO: Falha ao carregar fundo_jogo.png");
        return false;
    }
    /* carregamento da tela  para jogo pausado */
    assets.fundo_pause = al_load_bitmap("assets/background/tela_pause.png");
    if(!assets.fundo_pause) {
        perror("ERRO: Falha ao carregar tela_pause.png");
        return false;
    }

    /* carregamento botao menu iniciar jogo, sair jogo e menu */
    assets.bt_iniciar = al_load_bitmap("assets/background/bt_iniciar.png");
    if(!assets.bt_iniciar) {
        perror("ERRO: Falha ao carregar bt_iniciar.png");
        return false;
    }
    assets.bt_sair = al_load_bitmap("assets/background/bt_sair.png"); 
    if(!assets.bt_sair) {
        perror("ERRO: Falha ao carregar bt_sair.png");
        return false;
    }
    assets.bt_menu = al_load_bitmap("assets/background/bt_menu.png"); 
    if(!assets.bt_menu) {
        perror("ERRO: Falha ao carregar bt_menu.png");
        return false;
    }

    /*carregamento plataforma grande */
    assets.plataform_ground = al_load_bitmap("assets/background/plataform_4.png");
    if(!assets.plataform_ground) {
        perror("ERRO: Falha ao carregar plataform_4.png");
        return false;
    }
    /*carregamento plataforma pequena */
    assets.plataform_small = al_load_bitmap("assets/background/plataform_0.png");
    if(!assets.plataform_small) {
        perror("ERRO: Falha ao carregar plataform_0.png");
        return false;
    }
    /*carregamento plataforma media */
    assets.plataform_med = al_load_bitmap("assets/background/plataform_2.png");
    if(!assets.plataform_med) {
        perror("ERRO: Falha ao carregar plataform_2.png");
        return false;
    }

    /* carregar musica do menu *///
    /* usamos buffer */
    assets.musica_menu = al_load_audio_stream("./assets/musica/main_menu.ogg", 4, 2048);
    if (assets.musica_menu) {
        al_set_audio_stream_playmode(assets.musica_menu, ALLEGRO_PLAYMODE_LOOP);
        al_attach_audio_stream_to_mixer(assets.musica_menu, al_get_default_mixer());
        al_set_audio_stream_playing(assets.musica_menu, false); // Começa pausado
    } 

    /* carregar musica do jogo */
    assets.musica_jogo = al_load_audio_stream("./assets/musica/fase.ogg", 4, 2048);
    if (assets.musica_jogo) {
        al_set_audio_stream_playmode(assets.musica_jogo, ALLEGRO_PLAYMODE_LOOP);
        al_attach_audio_stream_to_mixer(assets.musica_jogo, al_get_default_mixer());
        al_set_audio_stream_playing(assets.musica_jogo, false); // Começa pausado
    } 

    return true;
}

/* destroi todos os recursos */
void resources_unload_all() {
    
    /* destruicao da aniamcao playes parado */
    // destruir cada sprite no array
    for (int i = 0; i < FRAMES_PARADO; i++) {
        if (assets.player_parado[i]) {
            al_destroy_bitmap(assets.player_parado[i]);
            // (Opcional, mas boa prática)
            assets.player_parado[i] = NULL; 
        }
    }

    /* destroi animacao do player andando */
    for(int i = 0; i < FRAMES_ANDANDO; i++) {
        if(assets.player_andando[i]) {
            al_destroy_bitmap(assets.player_andando[i]);
            assets.player_andando[i] = NULL;
        }
    }
    
    /*destroi animacao player pulando */
    for(int i = 0; i < FRAMES_PULANDO; i++) {
        if(assets.player_pulando[i]) {
            al_destroy_bitmap(assets.player_pulando[i]);
            assets.player_pulando[i] = NULL;
        }
    }

    /*destroi animacao player abaixado */
    for(int i = 0; i < FRAMES_ABAIXADO; i++) {
        if(assets.player_abaixado[i]) {
            al_destroy_bitmap(assets.player_abaixado[i]);
            assets.player_abaixado[i] = NULL;
        }
    }
    
    /* destroi animacao dos sprites de vida */
    for (int i = 0; i < 5; i++) {
        if (assets.sprites_vida[i]) {
            al_destroy_bitmap(assets.sprites_vida[i]);
            assets.sprites_vida[i] = NULL;
        }
    } 

    /* destruicao do sprite de lasanha */
    if(assets.lasanha) {
        al_destroy_bitmap(assets.lasanha);
        assets.lasanha = NULL;
    }

    /* destruicao do sprite de urso */
    if(assets.urso) {
        al_destroy_bitmap(assets.urso);
        assets.urso = NULL;
    }

    /* destruicao do sprite do player dash */
    if(assets.player_dash) {
        al_destroy_bitmap(assets.player_dash);
        assets.player_dash = NULL;
    }

    /* destruicao do fundo do menu */
    if(assets.fundo_menu) {
        al_destroy_bitmap(assets.fundo_menu);
        assets.fundo_menu = NULL;
    }

    /* destruicao do fundo gameover */
    if(assets.fundo_gameover) {
        al_destroy_bitmap(assets.fundo_gameover);
        assets.fundo_gameover = NULL;
    }

    /* destruicao do fundo vitoria */
    if(assets.fundo_vitoria) {
        al_destroy_bitmap(assets.fundo_vitoria);
        assets.fundo_vitoria = NULL;
    }

    /* destruicao dos botoes */
    if (assets.bt_iniciar) {
        al_destroy_bitmap(assets.bt_iniciar);
        assets.bt_iniciar = NULL;
    }
    if (assets.bt_sair) {
        al_destroy_bitmap(assets.bt_sair);
        assets.bt_sair = NULL;
    }
    if (assets.bt_menu) {
        al_destroy_bitmap(assets.bt_menu);
        assets.bt_menu = NULL;
    }

    /* destruicao do fundo do jogo */
    if (assets.fundo_game) {
        al_destroy_bitmap(assets.fundo_game);
        assets.fundo_game = NULL;
    }
    /* destruicao do fundo do pause */
    if (assets.fundo_pause) {
        al_destroy_bitmap(assets.fundo_pause);
        assets.fundo_pause = NULL;
    }

    /* destruicao plataforma grande */
    if(assets.plataform_ground) {
        al_destroy_bitmap(assets.plataform_ground);
        assets.plataform_ground = NULL;
    }

    /* destruicao plataforma pequena */
    if(assets.plataform_small) {
        al_destroy_bitmap(assets.plataform_small);
        assets.plataform_small = NULL;
    }

    /* destruicao plataforma media */
    if(assets.plataform_med) {
        al_destroy_bitmap(assets.plataform_med);
        assets.plataform_med = NULL;
    }

    /* destroi as musicas */
    if (assets.musica_menu) {
        al_destroy_audio_stream(assets.musica_menu);
        assets.musica_menu = NULL;
    }
    if (assets.musica_jogo) {
        al_destroy_audio_stream(assets.musica_jogo);
        assets.musica_jogo = NULL;
    }

}