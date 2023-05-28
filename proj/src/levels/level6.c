#include "levels/level8.h"

void update_player_starting_position6() {
  playerPosition.x = 537;
  playerPosition.y = 271;
  copy.x = 537;
  copy.y = 271;
}

void draw_game_level6() {
  memset(&ice_cubes, 0, sizeof(ice_cubes));
  path_counter = 0;

  if (level6_draw_counter == 0) {
    memset(&water_path, 0, sizeof(water_path));
    update_player_starting_position6();
    water_counter = 0;
    key_check = false;
    lock_cube.top_left_x = 477;
    lock_cube.top_left_y = 211;
    lock_cube.bot_right_x = 477 + 30;
    lock_cube.bot_right_y = 211 + 30;
  }

  int x_;
  int y_;

  // draw level6 tag
  // draw_sprite_xpm(level6_tag, 135, 32);

  // ice cubes
  x_ = 147;
  y_ = 121;
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

  x_ = 147;
  y_ = 151;
  for (int y = 0; y < 9; y++) {
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
  y_ = 391;
  for (int x = 0; x < 6; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }

  x_ = 327;
  y_ = 421;
  for (int x = 0; x < 8; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }

  x_ = 537;
  y_ = 391;
  for (int x = 0; x < 5; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }

  x_ = 657;
  y_ = 361;
  for (int y = 0; y < 7; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ -= 30;
  }

  x_ = 627;
  y_ = 181;
  for (int x = 0; x < 3; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ -= 30;
  }

  x_ = 567;
  y_ = 151;
  ic.top_left_x = x_;
  ic.top_left_y = y_;
  ic.bot_right_x = x_ + 30;
  ic.bot_right_y = y_ + 30;
  ice_cubes[ice_cube_counter] = ic;
  draw_sprite_xpm(ice_cube, x_, y_);
  ice_cube_counter++;

  x_ = 507;
  y_ = 181;
  for (int x = 0; x < 11; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ -= 30;
  }

  x_ = 267;
  y_ = 211;
  for (int x = 0; x < 3; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ -= 30;
  }

  x_ = 507;
  y_ = 241;
  for (int x = 0; x < 11; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ -= 30;
  }

  x_ = 597;
  y_ = 241;
  for (int x = 0; x < 1; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ -= 30;
  }

  x_ = 507;
  y_ = 271;
  for (int x = 0; x < 11; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ -= 30;
  }

  x_ = 597;
  y_ = 271;
  for (int x = 0; x < 2; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ -= 30;
  }

  x_ = 597;
  y_ = 301;
  for (int x = 0; x < 14; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ -= 30;
  }

  x_ = 597;
  y_ = 331;
  for (int x = 0; x < 4; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ -= 30;
  }

  x_ = 417;
  y_ = 331;
  for (int x = 0; x < 2; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ -= 30;
  }

  x_ = 237;
  y_ = 331;
  for (int x = 0; x < 2; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ -= 30;
  }

  // draw path cubes
  x_ = 177;
  y_ = 151;
  for (int x = 0; x < 13; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    path_counter++;
    x_ += 30;
  }

  x_ = 177;
  y_ = 181;
  for (int y = 0; y < 6; y++) {
    draw_sprite_xpm(path_cube, x_, y_);
    path_counter++;
    y_ += 30;
  }

  x_ = 297;
  y_ = 211;
  for (int x = 0; x < 12; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    path_counter++;
    x_ += 30;
  }

  x_ = 177;
  y_ = 361;
  for (int x = 0; x < 16; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    path_counter++;
    x_ += 30;
  }

  x_ = 357;
  y_ = 391;
  for (int x = 0; x < 6; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    path_counter++;
    x_ += 30;
  }

  x_ = 267;
  y_ = 331;
  for (int x = 0; x < 4; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    path_counter++;
    x_ += 30;
  }

  x_ = 447;
  y_ = 331;
  for (int x = 0; x < 2; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    path_counter++;
    x_ += 30;
  }

  x_ = 627;
  y_ = 241;
  for (int y = 0; y < 4; y++) {
    draw_sprite_xpm(path_cube, x_, y_);
    path_counter++;
    y_ += 30;
  }

  x_ = 567;
  y_ = 241;
  draw_sprite_xpm(path_cube, x_, y_);
  path_counter++;

  x_ = 537;
  y_ = 241;
  draw_sprite_xpm(path_cube, x_, y_);
  path_counter++;

  x_ = 537;
  y_ = 271;
  draw_sprite_xpm(path_cube, x_, y_);
  path_counter++;

  x_ = 537;
  y_ = 181;
  draw_sprite_xpm(path_cube, x_, y_);
  path_counter++;

  // check if player is on top of the key
  if (playerPosition.x == 177 && playerPosition.y == 211) {
    key_check = true;
  }

  // check if player has picked key
  if (!key_check) {
    draw_sprite_xpm(key, 177, 211);
    draw_sprite_xpm(lock, 477, 211);
  }
  else {
    memset(&lock_cube, 0, sizeof(lock_cube));
  }

  // draw red cube
  x_ = 297;
  y_ = 211;
  finish_level6.top_left_x = 297;
  finish_level6.top_left_y = 211;
  finish_level6.bot_right_x = 297 + 30;
  finish_level6.bot_right_y = 211 + 30;
  draw_sprite_xpm(red_cube, x_, y_);
  path_counter--;

  // player
  draw_sprite_xpm(player, playerPosition.x, playerPosition.y);

  ice_melt();

  // check if player has completed the path
  if (playerPosition.x == finish_level6.top_left_x && playerPosition.y == finish_level6.top_left_y) {
    if (check_all_ice_melted()) {
      menuState = END;
    }
    else {
      return;
    }
  }

  level6_draw_counter++;
  check_fell_into_water();
}
