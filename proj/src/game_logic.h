#ifndef SRC_GAME_LOGIC_H_
#define SRC_GAME_LOGIC_H_

#include "devices/keyboard/KBC.h"
#include "devices/mouse/mouse.h"
#include "devices/video/graphics.h"
#include "game_view.h"
#include "sprite.h"
#include "xpm/background_cube.xpm"
#include "xpm/end_screen.xpm"
#include "xpm/finish_button.xpm"
#include "xpm/ice_cube.xpm"
#include "xpm/key.xpm"
#include "xpm/level1.xpm"
#include "xpm/level10.xpm"
#include "xpm/level2.xpm"
#include "xpm/level3.xpm"
#include "xpm/level4.xpm"
#include "xpm/level5.xpm"
#include "xpm/level6.xpm"
#include "xpm/level7.xpm"
#include "xpm/level8.xpm"
#include "xpm/level9.xpm"
#include "xpm/lock.xpm"
#include "xpm/mouse.xpm"
#include "xpm/path_cube.xpm"
#include "xpm/player.xpm"
#include "xpm/red_cube.xpm"
#include "xpm/start_button.xpm"
#include "xpm/thin_ice_game.xpm"
#include "xpm/thin_ice_start.xpm"
#include "xpm/water.xpm"
#include <lcom/lcf.h>
#include <minix/sysutil.h>

#define MODE 0x115
#define FPS 60
#define DOUBLE_BUFFER_ACTIVATED 1

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

void update_timer_state();
void update_keyboard_state();
void update_mouse_state();
void update_start_and_finish_button_state();
void sprites_creation();

#endif
