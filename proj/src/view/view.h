#ifndef _LCOM_MENU_H_
#define _LCOM_MENU_H_

#include "config.h"
#include "devices/mouse/mouse.h"
#include "devices/video/graphics.h"
#include "model/model.h"
#include "model/sprite.h"
#include <lcom/lcf.h>
#include <minix/sysutil.h>

typedef struct {
  int top_left_x;
  int top_left_y;
  int bot_right_x;
  int bot_right_y;
} Box;

void draw_new_frame();
void draw_initial_menu();
void draw_game_menu();
void check_fell_into_water();
void ice_melt();
void update_player_starting_position1();
void draw_game_level1();
void update_player_starting_position2();
void draw_game_level2();
void update_player_starting_position3();
void draw_game_level3();
void update_player_starting_position4();
void draw_game_level4();
void update_player_starting_position5();
void draw_game_level5();
void update_player_starting_position6();
void draw_game_level6();
void draw_finish_menu();
void draw_mouse();
void swap_buffers();
int draw_sprite_xpm(Sprite *sprite, int x, int y);
int set_frame_buffers(uint16_t mode);

#endif
