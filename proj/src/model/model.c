#include "model.h"

// Variáveis externas importantes à construção e manipulação do modelo
extern uint8_t scancode;
extern uint8_t byte_index;
SystemState systemState = RUNNING;
MenuState menuState = START;
GameLevel gameLevel;
extern MouseInfo mouse_info;
extern vbe_mode_info_t mode_info;
extern int level1_draw_counter;
extern int level2_draw_counter;
extern int level3_draw_counter;
extern int level4_draw_counter;
extern int level6_draw_counter;
extern int level8_draw_counter;
extern Box ice_cubes[100];

// Objetos a construir e manipular com a mudança de estados
Sprite *mouse;
Sprite *start_screen;
Sprite *start_button;
Sprite *game_screen;
Sprite *background_cube;
Sprite *ice_cube;
Sprite *red_cube;
Sprite *water;
Sprite *player;
Sprite *path_cube;
Sprite *level1_tag;
Sprite *level2_tag;
Sprite *level3_tag;
Sprite *end_screen;
Sprite *finish_button;

//Posição do Jogador
PlayerPosition playerPosition;
PlayerPosition copy;

// Contador de interrupções do timer
int timer_interrupts = 0;

// Criação dos objetos via XPM e via comum
void setup_sprites() {
    mouse = create_sprite_xpm((xpm_map_t) mouse_xpm);
    start_screen = create_sprite_xpm((xpm_map_t) thin_ice_start_xpm);
    start_button = create_sprite_xpm((xpm_map_t) start_button_xpm);
    background_cube = create_sprite_xpm((xpm_map_t) background_cube_xpm);
    game_screen = create_sprite_xpm((xpm_map_t) thin_ice_game_xpm);
    ice_cube = create_sprite_xpm((xpm_map_t) ice_cube_xpm);
    red_cube = create_sprite_xpm((xpm_map_t) red_cube_xpm);
    water = create_sprite_xpm((xpm_map_t) water_xpm);
    player = create_sprite_xpm((xpm_map_t) player_xpm);
    path_cube = create_sprite_xpm((xpm_map_t) path_cube_xpm);
    level1_tag = create_sprite_xpm((xpm_map_t) level1_xpm);
    level2_tag = create_sprite_xpm((xpm_map_t) level2_xpm);
    level3_tag = create_sprite_xpm((xpm_map_t) level3_xpm);
    end_screen = create_sprite_xpm((xpm_map_t) end_screen_xpm);
    finish_button = create_sprite_xpm((xpm_map_t) finish_button_xpm);
}

// É boa prática antes de acabar o programa libertar a memória alocada
void destroy_sprites() {
    destroy_sprite(mouse);
    destroy_sprite(start_screen);
    destroy_sprite(start_button);
    destroy_sprite(background_cube);
    destroy_sprite(game_screen);
    destroy_sprite(ice_cube);
    destroy_sprite(red_cube);
    destroy_sprite(water);
    destroy_sprite(player);
    destroy_sprite(path_cube);
    destroy_sprite(level1_tag);
    destroy_sprite(level2_tag);
    destroy_sprite(level3_tag);
    destroy_sprite(end_screen);
    destroy_sprite(finish_button);
}

// Na altura da interrupção há troca dos buffers e incremento do contador
void update_timer_state() {
    if (DOUBLE_BUFFER) swap_buffers();
    timer_interrupts++;
}

// Sempre que uma nova tecla é pressionada há avaliação do scancode.
// No caso do Template o teclado influencia:
// - o systemState: se Q for pressionado, leva ao fim do programa
// - o menuState: se H, G, E forem pressionados, leva a um dos menus (start, game, end) disponíveis
void update_keyboard_state() {
    (kbc_ih)();
    switch (scancode) {
        case Q_KEY:
            systemState = EXIT;
            break;
        case H_KEY:
            menuState = START;
            level1_draw_counter = 0;
            level2_draw_counter = 0;
            level3_draw_counter = 0;
            level4_draw_counter = 0;
            level6_draw_counter = 0;
            break;
        case G_KEY:
            menuState = GAME;
            gameLevel = LEVEL_1;
            level1_draw_counter = 0;
            level2_draw_counter = 0;
            level3_draw_counter = 0;
            level4_draw_counter = 0;
            level6_draw_counter = 0;
            level8_draw_counter = 0;
            break;
        case E_KEY:
            menuState = END;
            level1_draw_counter = 0;
            level2_draw_counter = 0;
            level3_draw_counter = 0;
            level4_draw_counter = 0;
            level6_draw_counter = 0;
            level8_draw_counter = 0;
        case A_KEY:
            if (menuState == GAME) {
                bool check = true;
                for (int i = 0; i < 100; i++) {
                    if (ice_cubes[i].top_left_x == playerPosition.x-30 && ice_cubes[i].top_left_y == playerPosition.y) {
                        check = false;
                        break;
                    }
                }
                if (check) {
                    playerPosition.x -= 30;
                    }
            }
            break;
        case W_KEY:
            if (menuState == GAME) {
                bool check = true;
                for (int i = 0; i < 100; i++) {
                    if (ice_cubes[i].top_left_x == playerPosition.x && ice_cubes[i].top_left_y == playerPosition.y-30) {
                        check = false;
                        break;
                    }
                }
                if (check) playerPosition.y -= 30;
            }
            break;
        case S_KEY:
            if (menuState == GAME) {
                bool check = true;
                for (int i = 0; i < 100; i++) {
                    if (ice_cubes[i].top_left_x == playerPosition.x && ice_cubes[i].top_left_y == playerPosition.y+30) {
                        check = false;
                        break;
                    }
                }
                if (check) playerPosition.y += 30;
            }
            break;
        case D_KEY:
            if (menuState == GAME) {
                bool check = true;
                for (int i = 0; i < 100; i++) {
                    if (ice_cubes[i].top_left_x == playerPosition.x+30 && ice_cubes[i].top_left_y == playerPosition.y) {
                        check = false;
                        break;
                    }
                }
                if (check) playerPosition.x += 30;
            }
            break;            
        default:
            break;
    }
    draw_new_frame();
}

// Sempre que há um novo pacote completo do rato
// - muda o seu estado interno (x, y, left_pressed, right_pressed) - mouse_sync_info();
// - pode mudar o estado do botão por baixo dele - update_buttons_state();
void update_mouse_state() {
    (mouse_ih)();
    mouse_sync_bytes();
    if (byte_index == 3) {
        mouse_sync_info();
        update_start_button_state();
        draw_new_frame();
        byte_index = 0;
    }
}

void update_start_button_state() {
    if (mouse_info.left_click) {
        if (menuState == START) {
            if (mouse_info.x >= 340 && mouse_info.x <= 465 && mouse_info.y >= 476 && mouse_info.y <= 518)     {
            start_button->pressed = 1;
            menuState = GAME;
            gameLevel = LEVEL_1;
            level1_draw_counter = 0;
            level2_draw_counter = 0;
            level3_draw_counter = 0;
            level4_draw_counter = 0;
            level6_draw_counter = 0;
            level8_draw_counter = 0;
            }
        }
        if (menuState == END) {
            if (mouse_info.x >= 340 && mouse_info.x <= 465 && mouse_info.y >= 467 && mouse_info.y <= 506)     {
            finish_button->pressed = 1;
            menuState = START;
            }
        }
    } else {
        start_button->pressed = 0;
        finish_button->pressed = 0;
    }
}
