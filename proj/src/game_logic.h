#ifndef _SRC_GAME_LOGIC_H_
#define _SRC_GAME_LOGIC_H_

#include "XPMs/background_cube.xpm"
#include "XPMs/end_screen.xpm"
#include "XPMs/finish_button.xpm"
#include "XPMs/ice_cube.xpm"
#include "XPMs/key.xpm"
#include "XPMs/level1.xpm"
#include "XPMs/level10.xpm"
#include "XPMs/level2.xpm"
#include "XPMs/level3.xpm"
#include "XPMs/level4.xpm"
#include "XPMs/level5.xpm"
#include "XPMs/level6.xpm"
#include "XPMs/level7.xpm"
#include "XPMs/level8.xpm"
#include "XPMs/level9.xpm"
#include "XPMs/lock.xpm"
#include "XPMs/mouse.xpm"
#include "XPMs/path_cube.xpm"
#include "XPMs/player.xpm"
#include "XPMs/quit_button.xpm"
#include "XPMs/red_cube.xpm"
#include "XPMs/start_button.xpm"
#include "XPMs/thin_ice_game.xpm"
#include "XPMs/thin_ice_start.xpm"
#include "XPMs/water.xpm"
#include "devices/keyboard/KBC.h"
#include "devices/mouse/mouse.h"
#include "devices/video/graphics.h"
#include "game_view.h"
#include "sprite.h"
#include <lcom/lcf.h>
#include <minix/sysutil.h>

#define MODE 0x115
#define FPS 60

typedef enum {
  RUNNING,
  EXIT,
} GameState;

typedef enum {
  START,
  GAME,
  FINISH
} MenuState;

typedef enum {
  LEVEL_1,
  LEVEL_2,
  LEVEL_3,
  LEVEL_4,
  LEVEL_5,
  LEVEL_6,
  LEVEL_7,
  LEVEL_8,
  LEVEL_9,
  LEVEL_10
} GameLevel;

typedef struct {
  int x;
  int y;
} PlayerPosition;

void update_timer();
void update_keyboard();
void update_mouse();
void update_start_and_finish_button();
void sprites_creation();

#endif
