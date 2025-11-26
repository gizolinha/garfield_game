#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <math.h> 
#include <stdbool.h>
#include <string.h>
#include "game.h"
#include "game_def.h"
#include "setup.h"


int main () {
    /* inicia o ambiente */
    if(!setup_init()) {
        perror("não foi possível iniciar o jogo");
        setup_end();
        return -1;
    }   

    /* inicia os recursos do jogo */
    if(!game_init()) {
        perror("não foi possível iniciar os recursos do jogo");
        setup_end();
        return -1;
    }

    /* redesenhar */
    bool redraw = true;

    while(1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        /* evento de relogio, verificacao se a tela deve ser atualizada*/
        if(event.type == ALLEGRO_EVENT_TIMER) {
            if(game_update() == SAIR) //logica do jogo
                break;

            redraw = true;
    
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //fecha janela
            break;
        else 
            game_input(event);

        if(redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            game_draw(); 
            al_flip_display(); //modificacoes na tela
        }   
    }
    
    /* destroi o sistema */
    game_end();
    setup_end();
    return 0;
}