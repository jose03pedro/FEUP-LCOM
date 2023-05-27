#ifndef SRC_GAME_VIEW_H_
#define SRC_GAME_VIEW_H_

#include "devices/mouse/mouse.h"
#include "devices/video/graphics.h"
#include "game_levels/level1.h"
#include "game_levels/level10.h"
#include "game_levels/level2.h"
#include "game_levels/level3.h"
#include "game_levels/level4.h"
#include "game_levels/level5.h"
#include "game_levels/level6.h"
#include "game_levels/level7.h"
#include "game_levels/level8.h"
#include "game_levels/level9.h"
#include "game_logic.h"
#include "sprite.h"
#include <lcom/lcf.h>
#include <minix/sysutil.h>

typedef struct {
  int top_left_x;
  int top_left_y;
  int bot_right_x;
  int bot_right_y;
} Box;

int set_frame_buffers(uint16_t mode);
void draw_new_frame();
void draw_initial_menu();
void draw_game_menu();
void check_fell_into_water();
void ice_melt();
bool check_all_ice_melted();
void reset_all_draw_counters();
void draw_finish_menu();
void draw_mouse();
void swap_buffers();
int draw_sprite(Sprite_t *sprite, int x, int y);

#endif
