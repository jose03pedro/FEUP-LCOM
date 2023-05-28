#include "levels/level5.h"

void update_player_starting_position5() {
  playerPosition.x = 537;
  playerPosition.y = 271;
  copy.x = 537;
  copy.y = 271;
}

void draw_game_level5() {
  memset(&ice_cubes, 0, sizeof(ice_cubes));
  path_counter = 0;

  if (level5_draw_counter == 0) {
    memset(&water_path, 0, sizeof(water_path));
    update_player_starting_position5();
    water_counter = 0;
  }

  // draw_sprite_xpm(level2_tag, 135, 32);

  int x_ = 147;
  int y_ = 331;
  int ice_cube_counter = 0;
  Box ic;
  for (int x = 0; x < 3; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }

  x_ = 147;
  y_ = 391;

  for (int x = 0; x < 4; x++) {
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

  x_ = 207;
  y_ = 301;
  for (int x = 0; x < 11; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }

  x_ = 237;
  y_ = 421;
  for (int x = 0; x < 14; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }

  x_ = 507;
  y_ = 271;
  ic.top_left_x = x_;
  ic.top_left_y = y_;
  ic.bot_right_x = x_ + 30;
  ic.bot_right_y = y_ + 30;
  ice_cubes[ice_cube_counter] = ic;

  draw_sprite_xpm(ice_cube, x_, y_);
  ice_cube_counter++;
  x_ = 507;
  y_ = 241;
  for (int x = 0; x < 3; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }

  x_ = 567;
  y_ = 271;
  ic.top_left_x = x_;
  ic.top_left_y = y_;
  ic.bot_right_x = x_ + 30;
  ic.bot_right_y = y_ + 30;
  ice_cubes[ice_cube_counter] = ic;
  draw_sprite_xpm(ice_cube, x_, y_);
  ice_cube_counter++;

  x_ = 567;
  y_ = 301;

  for (int x = 0; x < 3; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }

  x_ = 627;
  y_ = 331;

  for (int y = 0; y < 3; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ += 30;
  }

  x_ = 177;
  y_ = 361;
  // path

  for (int x = 0; x < 15; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    path_counter++;
    x_ += 30;
  }

  x_ = 267;
  y_ = 391;
  for (int x = 0; x < 12; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    path_counter++;
    x_ += 30;
  }

  x_ = 237;
  y_ = 331;
  for (int x = 0; x < 13; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    path_counter++;
    x_ += 30;
  }

  x_ = 537;
  y_ = 271;
  draw_sprite_xpm(path_cube, x_, y_);
  path_counter++;

  x_ = 537;
  y_ = 301;
  draw_sprite_xpm(path_cube, x_, y_);
  path_counter++;

  // draw red cube
  x_ = 177;
  y_ = 361;
  finish_level5.top_left_x = 177;
  finish_level5.top_left_y = 361;
  finish_level5.bot_right_x = 177 + 30;
  finish_level5.bot_right_y = 361 + 30;
  draw_sprite_xpm(red_cube, x_, y_);
  path_counter--;

  // draw player
  draw_sprite_xpm(player, playerPosition.x, playerPosition.y);

  ice_melt();

  // check if player has completed the path
  if (playerPosition.x == finish_level5.top_left_x && playerPosition.y == finish_level5.top_left_y) {
    if (check_all_ice_melted()) {
      gameLevel = LEVEL_6;
    }
    else {
      return;
    }
  }

  level5_draw_counter++;
  check_fell_into_water();
}
