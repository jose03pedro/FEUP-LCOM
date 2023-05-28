#include "levels/level1.h"

Box ice_cubes[250];
Box water_path[250];
Box lock_cube;
bool key_check;
int path_counter;
int water_counter;

void update_player_starting_position1() {
  playerPosition.x = 537;
  playerPosition.y = 361;
  copy.x = 537;
  copy.y = 361;
}

void draw_game_level1() {
  memset(&ice_cubes, 0, sizeof(ice_cubes));
  path_counter = 0;

  if (level1_draw_counter == 0) {
    memset(&water_path, 0, sizeof(water_path));
    update_player_starting_position1();
    water_counter = 0;
  }

  // draw level1 tag on the top left corner
  draw_sprite_xpm(level1_tag, 135, 32);

  // draw level1 ice cubes
  int x_ = 147;
  int y_ = 331;
  int ice_cube_counter = 0;
  Box ic;
  for (int x = 0; x < 15; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }
  ic.top_left_x = 147;
  ic.top_left_y = 361;
  ic.bot_right_x = 147 + 30;
  ic.bot_right_y = 361 + 30;
  ice_cubes[ice_cube_counter] = ic;
  draw_sprite_xpm(ice_cube, 147, 361);
  ice_cube_counter++;

  ic.top_left_x = 567;
  ic.top_left_y = 361;
  ic.bot_right_x = 567 + 30;
  ic.bot_right_y = 361 + 30;
  ice_cubes[ice_cube_counter] = ic;
  draw_sprite_xpm(ice_cube, 567, 361);
  ice_cube_counter++;

  x_ = 147;
  y_ = 391;
  for (int x = 0; x < 15; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }

  // draw level1 path cubes
  x_ = 177;
  y_ = 361;
  for (int x = 0; x < 13; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    path_counter++;
    x_ += 30;
  }

  // draw level1 red cube
  x_ = 177;
  y_ = 361;
  finish_level1.top_left_x = 177;
  finish_level1.top_left_y = 361;
  finish_level1.bot_right_x = 177 + 30;
  finish_level1.bot_right_y = 361 + 30;
  draw_sprite_xpm(red_cube, x_, y_);
  path_counter--;

  // draw player
  draw_sprite_xpm(player, playerPosition.x, playerPosition.y);

  ice_melt();

  // check if player has completed the path
  // check if player has completed the path
  if (playerPosition.x == finish_level1.top_left_x && playerPosition.y == finish_level1.top_left_y) {
    if (check_all_ice_melted()) {
      gameLevel = LEVEL_2;
    }
    else {
      return;
    }
  }

  level1_draw_counter++;
  check_fell_into_water();
}
