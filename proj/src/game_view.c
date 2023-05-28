#include "game_view.h"

uint8_t *main_fb;
uint8_t *secondary_fb;
uint8_t *drawing_fb;
uint32_t fb_size;
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
Box ice_cubes[250];
Box water_path[250];
Box lock_cube;
bool key_check;
int water_counter = 0;
int path_counter = 0;
extern int timer_interrupts;
extern vbe_mode_info_t mode_info;
extern MouseInfo mouse_info;
extern MenuState menuState;
extern GameLevel gameLevel;

extern Sprite_t *mouse;
extern Sprite_t *start_screen;
extern Sprite_t *start_button;
extern Sprite_t *quit_button;
extern Sprite_t *game_screen;
extern Sprite_t *background_cube;
extern Sprite_t *water;
extern Sprite_t *player;
extern Sprite_t *end_screen;
extern Sprite_t *finish_button;

extern PlayerPosition playerPosition;
extern PlayerPosition copy;

int set_frame_buffers(uint16_t mode) {
  set_frame_buffer(mode, &main_fb);
  fb_size = mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8);
  if (DOUBLE_BUFFER_ACTIVATED) {
    secondary_fb = (uint8_t *) malloc(fb_size);
    drawing_fb = secondary_fb;
  }
  else {
    drawing_fb = main_fb;
  }
  return 0;
}

void swap_buffers() {
  memcpy(main_fb, secondary_fb, fb_size);
}

void draw_new_frame() {
  switch (menuState) {
    case START:
      draw_initial_menu();
      break;
    case GAME:
      draw_game_menu();
      switch (gameLevel) {
        case LEVEL_1:
          draw_game_level1();
          break;
        case LEVEL_2:
          draw_game_level2();
          break;
        case LEVEL_3:
          draw_game_level3();
          break;
        case LEVEL_4:
          draw_game_level4();
          break;
        case LEVEL_5:
          draw_game_level5();
          break;
        case LEVEL_6:
          draw_game_level6();
          break;
        case LEVEL_7:
          draw_game_level7();
          break;
        case LEVEL_8:
          draw_game_level8();
          break;
        case LEVEL_9:
          draw_game_level9();
          break;
        case LEVEL_10:
          draw_game_level10();
          break;
      }
      break;
    case FINISH:
      draw_finish_menu();
      break;
  }
  draw_mouse();
}

void draw_initial_menu() {
  draw_sprite(start_screen, 0, 0);
  draw_sprite(start_button, 260, 485);
  draw_sprite(quit_button, 415, 485);
}

void draw_game_menu() {
  draw_sprite(game_screen, 0, 0);
  int x_ = 117;
  int y_ = 61;
  draw_line(117, 60, 571, 0x77bbff, drawing_fb);
  draw_rectangle(116, 60, 1, 452, 0x77bbff, drawing_fb);
  for (int y = 0; y < 15; y++) {
    for (int x = 0; x < 19; x++) {
      draw_sprite(background_cube, x_, y_);
      x_ += 30;
    }
    x_ = 117;
    y_ += 30;
  }
  draw_line(117, 511, 571, 0x77bbff, drawing_fb);
  draw_rectangle(687, 60, 1, 452, 0x77bbff, drawing_fb);
}

void check_fell_into_water() {
  // check if player has fallen into the water
  for (int i = 0; i < 250; i++) {
    if (water_path[i].top_left_x == playerPosition.x && water_path[i].top_left_y == playerPosition.y) {
      draw_sprite(player, playerPosition.x, playerPosition.y);
      menuState = GAME;
      reset_all_draw_counters();
      break;
    }
  }
}

void ice_melt() {
  // checking if player moved and ice melted
  if (playerPosition.x != copy.x || playerPosition.y != copy.y) {
    Box wt;
    wt.top_left_x = copy.x;
    wt.top_left_y = copy.y;
    wt.bot_right_x = copy.x + 30;
    wt.bot_right_y = copy.y + 30;
    water_path[water_counter] = wt;
    water_counter++;
  }

  for (int i = 0; i < 250; i++) {
    if (water_path[i].top_left_x > 0 && water_path[i].top_left_y < 600) {
      draw_sprite(water, water_path[i].top_left_x, water_path[i].top_left_y);
    }
  }

  copy.x = playerPosition.x;
  copy.y = playerPosition.y;
}

bool check_all_ice_melted() {
  // check if player has melted all ice
  printf("water: %d blocks counted, path: %d blocks counted\n", water_counter, path_counter);
  if (water_counter != path_counter) {
    menuState = GAME;
    reset_all_draw_counters();
    return false;
  }
  return true;
}

void reset_all_draw_counters() {
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

void draw_finish_menu() {
  draw_sprite(end_screen, 0, 0);
  draw_sprite(finish_button, 340, 467);
}

void draw_mouse() {
  switch (menuState) {
    case START:
    case FINISH:
      draw_sprite(mouse, mouse_info.x, mouse_info.y);
      break;
    case GAME:
      break;
  }
}

int draw_sprite(Sprite_t *sprite, int x, int y) {
  uint16_t height = sprite->height;
  uint16_t width = sprite->width;
  uint32_t current_color;
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      current_color = sprite->colors[w + h * width];
      if (draw_pixel(x + w, y + h, current_color, drawing_fb) != 0)
        return 1;
    }
  }
  return 0;
}
