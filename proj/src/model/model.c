#include "model.h"

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
extern int level5_draw_counter;
extern int level6_draw_counter;
extern int level7_draw_counter;
extern int level8_draw_counter;
extern int level9_draw_counter;
extern int level10_draw_counter;
extern Box ice_cubes[250];
extern Box lock_cube;

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
Sprite *level4_tag;
Sprite *level5_tag;
Sprite *level6_tag;
Sprite *level7_tag;
Sprite *level8_tag;
Sprite *level9_tag;
Sprite *level10_tag;
Sprite *end_screen;
Sprite *finish_button;
Sprite *lock;
Sprite *key;

// Posição do Jogador
PlayerPosition playerPosition;
PlayerPosition copy;

int timer_interrupts = 0;

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
  level4_tag = create_sprite_xpm((xpm_map_t) level4_xpm);
  level5_tag = create_sprite_xpm((xpm_map_t) level5_xpm);
  level6_tag = create_sprite_xpm((xpm_map_t) level6_xpm);
  level7_tag = create_sprite_xpm((xpm_map_t) level7_xpm);
  level8_tag = create_sprite_xpm((xpm_map_t) level8_xpm);
  level9_tag = create_sprite_xpm((xpm_map_t) level9_xpm);
  level10_tag = create_sprite_xpm((xpm_map_t) level10_xpm);
  end_screen = create_sprite_xpm((xpm_map_t) end_screen_xpm);
  finish_button = create_sprite_xpm((xpm_map_t) finish_button_xpm);
  lock = create_sprite_xpm((xpm_map_t) lock_xpm);
  key = create_sprite_xpm((xpm_map_t) key_xpm);
}

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
  destroy_sprite(level4_tag);
  destroy_sprite(level5_tag);
  destroy_sprite(level6_tag);
  destroy_sprite(level7_tag);
  destroy_sprite(level8_tag);
  destroy_sprite(level9_tag);
  destroy_sprite(level10_tag);
  destroy_sprite(end_screen);
  destroy_sprite(finish_button);
  destroy_sprite(lock);
  destroy_sprite(key);
}

void update_timer_state() {
  if (DOUBLE_BUFFER)
    swap_buffers();
  timer_interrupts++;
}

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
      level5_draw_counter = 0;
      level6_draw_counter = 0;
      level7_draw_counter = 0;
      level8_draw_counter = 0;
      level9_draw_counter = 0;
      level10_draw_counter = 0;
      break;
    case G_KEY:
      menuState = GAME;
      gameLevel = LEVEL_1;
      level1_draw_counter = 0;
      level2_draw_counter = 0;
      level3_draw_counter = 0;
      level4_draw_counter = 0;
      level5_draw_counter = 0;
      level6_draw_counter = 0;
      level7_draw_counter = 0;
      level8_draw_counter = 0;
      level9_draw_counter = 0;
      level10_draw_counter = 0;
      break;
    case E_KEY:
      menuState = END;
      level1_draw_counter = 0;
      level2_draw_counter = 0;
      level3_draw_counter = 0;
      level4_draw_counter = 0;
      level5_draw_counter = 0;
      level6_draw_counter = 0;
      level7_draw_counter = 0;
      level8_draw_counter = 0;
      level9_draw_counter = 0;
      level10_draw_counter = 0;
    case A_KEY:
      if (menuState == GAME) {
        bool check = true;
        for (int i = 0; i < 250; i++) {
          if (ice_cubes[i].top_left_x == playerPosition.x - 30 && ice_cubes[i].top_left_y == playerPosition.y) {
            check = false;
            break;
          }
        }
        if (lock_cube.top_left_x == playerPosition.x - 30 && lock_cube.top_left_y == playerPosition.y) {
          check = false;
        }
        if (check) {
          playerPosition.x -= 30;
        }
      }
      break;
    case W_KEY:
      if (menuState == GAME) {
        bool check = true;
        for (int i = 0; i < 250; i++) {
          if (ice_cubes[i].top_left_x == playerPosition.x && ice_cubes[i].top_left_y == playerPosition.y - 30) {
            check = false;
            break;
          }
        }
        if (lock_cube.top_left_x == playerPosition.x && lock_cube.top_left_y == playerPosition.y - 30) {
          check = false;
        }
        if (check)
          playerPosition.y -= 30;
      }
      break;
    case S_KEY:
      if (menuState == GAME) {
        bool check = true;
        for (int i = 0; i < 250; i++) {
          if (ice_cubes[i].top_left_x == playerPosition.x && ice_cubes[i].top_left_y == playerPosition.y + 30) {
            check = false;
            break;
          }
        }
        if (lock_cube.top_left_x == playerPosition.x && lock_cube.top_left_y == playerPosition.y + 30) {
          check = false;
        }
        if (check)
          playerPosition.y += 30;
      }
      break;
    case D_KEY:
      if (menuState == GAME) {
        bool check = true;
        for (int i = 0; i < 250; i++) {
          if (ice_cubes[i].top_left_x == playerPosition.x + 30 && ice_cubes[i].top_left_y == playerPosition.y) {
            check = false;
            break;
          }
        }
        if (lock_cube.top_left_x == playerPosition.x + 30 && lock_cube.top_left_y == playerPosition.y) {
          check = false;
        }
        if (check)
          playerPosition.x += 30;
      }
      break;
    default:
      break;
  }
  draw_new_frame();
}

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
      if (mouse_info.x >= 340 && mouse_info.x <= 465 && mouse_info.y >= 476 && mouse_info.y <= 518) {
        start_button->pressed = 1;
        menuState = GAME;
        gameLevel = LEVEL_1;
        level1_draw_counter = 0;
        level2_draw_counter = 0;
        level3_draw_counter = 0;
        level4_draw_counter = 0;
        level5_draw_counter = 0;
        level6_draw_counter = 0;
        level7_draw_counter = 0;
        level8_draw_counter = 0;
        level9_draw_counter = 0;
        level10_draw_counter = 0;
      }
    }
    if (menuState == END) {
      if (mouse_info.x >= 340 && mouse_info.x <= 465 && mouse_info.y >= 467 && mouse_info.y <= 506) {
        finish_button->pressed = 1;
        menuState = START;
      }
    }
  }
  else {
    start_button->pressed = 0;
    finish_button->pressed = 0;
  }
}
