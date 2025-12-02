
# 🐱 Garfield's Lasagna Adventure

**Garfield's Lasagna Adventure** é um jogo de plataforma 2D desenvolvido em linguagem C utilizando a biblioteca multimídia **Allegro 5** para a disciplina de PROGRAMAÇÃO II . O jogador controla o Garfield, que deve atravessar um mapa cheio de obstáculos, inimigos e plataformas móveis para alcançar a "Lasanha da Vitória".

## Funcionalidades

  * **Movimentação Física:** Mecânicas de gravidade, pulo, andar, agachar e *Dash* (impulso).
  * **Plataformas Dinâmicas:** Sistema de colisão7, incluindo plataformas que caem após o jogador pisar nelas.
  * **Inimigos (Obstáculos):** 3 tipos de inimigos animados (Green, Flowey, Clock).
  * **Gerenciamento de Recursos:** Carregamento e liberação de memória para sprites e áudio.
  * **Estados de Jogo:** Menu Principal, Gameplay, Pause, Game Over e Vitória.
  * **Itens:** Coletáveis para vencer a fase (Lasanha) ou recuperar vida (Ursinho).

## Pré-requisitos

Para compilar e executar este jogo, você precisa de:

1.  **Compilador GCC**.
2.  **Biblioteca Allegro 5** instalada, incluindo os addons:
      * `allegro_image`, `allegro_font`, `allegro_ttf`, `allegro_audio`, `allegro_acodec`.
3.  **Ferramenta `make`** (Opcional, mas recomendado para usar o Makefile).
4.  **pkg-config** (Necessário se for usar o Makefile fornecido).

##  Como Compilar e Executar

Este projeto inclui um **Makefile** para facilitar a automação da compilação.

### Opção 1: Usando Make (Linux / MacOS / MSYS2) [Recomendado]

Abra o terminal na pasta raiz do projeto e execute:

```bash
make
```

Isso irá compilar todos os arquivos `.c`, linkar com as bibliotecas do Allegro e gerar o executável chamado **`garfield`**.

Para rodar o jogo:

```bash
./garfield
```

Para limpar os arquivos objetos (`.o`) e o executável gerados:

```bash
make clean
```

##  Controles

| Tecla | Ação (Jogo) | Ação (Menus) |
| :--- | :--- | :--- |
| **W** | Pular | Cima |
| **A** | Mover para Esquerda | - |
| **S** | Agachar | Baixo |
| **D** | Mover para Direita | - |
| **Right Shift** | Dash (Acelerar) | - |
| **Enter** | - | Selecionar Opção |
| **ESC** | Pausar Jogo | - |

##  Estrutura dos Arquivos

O código foi modularizado para separar responsabilidades. Cada módulo possui seu `.c` (implementação) e `.h` (definições):

  * **Core / Sistema:**

      * `main.c`: Loop principal e gerenciamento de eventos macro.
      * `setup.c/h`: Inicialização do Allegro, teclado, timer, display e áudio.
      * `resources.c/h`: Carregamento (`load`) e destruição (`unload`) de sprites e sons (`gameresources assets`).
      * `game.c/h`: Máquina de estados (Menu, Jogando, Pause, etc.) e loop lógico.
      * `game_def.h`: Constantes globais (FPS, Tamanho da Tela, Gravidade) e Enums.

  * **Entidades do Jogo:**

      * `player.c/h`: Lógica do personagem (física, animação, estados e input).
      * `plataform.c/h`: Inicialização do mapa, renderização e lógica de plataformas (chão, flutuantes e quebráveis).
      * `obstacle.c/h`: Gerenciamento da lista de inimigos e suas animações.
      * `itens.c/h`: Gerenciamento dos itens coletáveis (Lasanha e Vida).

## Observações Importantes

  * **Assets:** O executável deve estar na mesma pasta que contém o diretório `assets/`. O jogo buscará imagens em caminhos como `assets/personagens/...` e músicas em `assets/musica/...`.
  * **Áudio:** O jogo utiliza *audio streaming* para as músicas de fundo (`.ogg`). Certifique-se de que os drivers de áudio estão funcionando.

-----
