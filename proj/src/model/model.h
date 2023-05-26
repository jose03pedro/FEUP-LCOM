#ifndef _LCOM_MODEL_H_
#define _LCOM_MODEL_H_

#include "config.h"
#include "devices/keyboard/KBC.h"
#include "devices/mouse/mouse.h"
#include "devices/video/graphics.h"
#include "model/sprite.h"
#include "view/view.h"
#include "xpm/background_cube.xpm"
#include "xpm/end_screen.xpm"
#include "xpm/finish_button.xpm"
#include "xpm/ice_cube.xpm"
#include "xpm/key.xpm"
#include "xpm/level1.xpm"
#include "xpm/level2.xpm"
#include "xpm/level3.xpm"
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

typedef enum {
  RUNNING,
  EXIT,
} SystemState;

typedef enum {
  START,
  GAME,
  END
} MenuState;

typedef enum {
  LEVEL_1,
  LEVEL_2,
  LEVEL_3,
  LEVEL_4,
  LEVEL_5,
  LEVEL_6,
  LEVEL_7
} GameLevel;

typedef struct {
  int x;
  int y;
} PlayerPosition;

void update_timer_state();
void update_keyboard_state();
void update_mouse_state();
void update_start_button_state();
void setup_sprites();
void destroy_sprites();

#endif
