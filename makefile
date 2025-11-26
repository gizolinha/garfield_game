parametrosCompilacao = -Wall -g

NOME_PROGRAMA = garfield

FONTES = main.c setup.c game.c player.c resources.c plataform.c obstacle.c itens.c 

OBJETOS = $(FONTES:.c=.o)

ALLEGRO_LIBS = $(shell pkg-config --libs --cflags allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5 allegro_primitives-5 allegro_dialog-5) -lm

all: $(NOME_PROGRAMA)

$(NOME_PROGRAMA): $(OBJETOS)
	gcc -o $@ $^ $(parametrosCompilacao) $(ALLEGRO_LIBS) 

%.o: %.c
	gcc -c $< -o $@ $(parametrosCompilacao)

clean:
	rm -f *.o $(NOME_PROGRAMA)