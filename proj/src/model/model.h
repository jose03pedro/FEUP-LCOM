#ifndef _LCOM_MODEL_H_
#define _LCOM_MODEL_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "devices/keyboard/KBC.h"
#include "devices/mouse/mouse.h"
#include "devices/video/graphics.h"
#include "xpm/mouse.xpm"
#include "xpm/thin_ice_start.xpm"
#include "xpm/start_button.xpm"
#include "xpm/background_cube.xpm"
#include "xpm/thin_ice_game.xpm"
#include "xpm/ice_cube.xpm"
#include "xpm/red_cube.xpm"
#include "xpm/water.xpm"
#include "xpm/player.xpm"
#include "xpm/path_cube.xpm"
#include "xpm/level1.xpm"
#include "xpm/level2.xpm"
#include "xpm/level3.xpm"
#include "xpm/end_screen.xpm"
#include "xpm/finish_button.xpm"
#include "view/view.h"
#include "model/sprite.h"
#include "config.h"

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
    LEVEL_3
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
