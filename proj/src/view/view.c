#include "view.h"

// Variáveis externas importantes à visualização do modelo e dos seus estados
uint8_t *main_frame_buffer;
uint8_t *secondary_frame_buffer;
uint8_t *drawing_frame_buffer;
uint32_t frame_buffer_size;
int level1_draw_counter = 0;
int level2_draw_counter = 0;
int level3_draw_counter = 0;
int level4_draw_counter = 0;
int level5_draw_counter = 0;
int level6_draw_counter = 0;
Box ice_cubes[150];
Box water_path[150];
int water_counter = 0;
Box finish_level1;
Box finish_level2;
Box finish_level3;
Box finish_level4;
Box finish_level5;
Box finish_level6;
extern int timer_interrupts;
extern vbe_mode_info_t mode_info;
extern MouseInfo mouse_info;
extern MenuState menuState;
extern GameLevel gameLevel;

// Objetos
extern Sprite *mouse;
extern Sprite *start_screen;
extern Sprite *start_button;
extern Sprite *game_screen;
extern Sprite *background_cube;
extern Sprite *ice_cube;
extern Sprite *red_cube;
extern Sprite *water;
extern Sprite *player;
extern Sprite *path_cube;
extern Sprite *level1_tag;
extern Sprite *level2_tag;
extern Sprite *level3_tag;
extern Sprite *end_screen;
extern Sprite *finish_button;

extern PlayerPosition playerPosition;
extern PlayerPosition copy;

// Alocação de memória ao(s) buffer(s)
// Se houver só um buffer, esse é o principal
// Se houver double buffering, há um secundário a alocar a mesma quantidade de memória que serve
// exclusivamente para o desenho
int set_frame_buffers(uint16_t mode) {
  if (set_frame_buffer(mode, &main_frame_buffer))
    return 1;
  frame_buffer_size = mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8);
  if (DOUBLE_BUFFER) {
    secondary_frame_buffer = (uint8_t *) malloc(frame_buffer_size);
    drawing_frame_buffer = secondary_frame_buffer;
  }
  else {
    drawing_frame_buffer = main_frame_buffer;
  }
  return 0;
}

// Double buffering
// Cópia para o frame buffer principal do frame construído desde a última atualização
// Otimizaçṍes:
// A) como o swap é uma operação muito frequente, é melhor não estar  a calcular frame_buffer_size sempre.
// Assim opta-se por uma variável global, que é constante ao longo da execução e calculada 1 vez na linha 30.
// Poupa-se (frequência * (2 multiplicações + 1 soma + 1 divisão)) operações por cada segundo.
// B) só vale a pena dar display do RTC quando passa um segundo
void swap_buffers() {
  memcpy(main_frame_buffer, secondary_frame_buffer, frame_buffer_size);
}

// A construção de um novo frame é baseado:
// - no estado atual do modelo (menuState, mouse_info, mode_info, buttonX->pressed...);
// - no Algoritmo do Pintor - https://pt.wikipedia.org/wiki/Algoritmo_do_pintor
// A ideia é colocar no buffer primeiro o plano mais longe do observador (a cor do fundo) e só depois
// os objetos em cima, no caso do cursor e / ou dos botões
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
      }
      break;
    case END:
      draw_finish_menu();
      break;
  }
  draw_mouse();
}

void draw_initial_menu() {
  draw_sprite_xpm(start_screen, 0, 0);
  draw_sprite_xpm(start_button, 340, 479);
}

void draw_game_menu() {
  draw_sprite_xpm(game_screen, 0, 0);
  int x_ = 117;
  int y_ = 61;
  draw_line(117, 60, 571, 0x77bbff, drawing_frame_buffer);
  draw_rectangle(116, 60, 1, 452, 0x77bbff, drawing_frame_buffer);
  for (int y = 0; y < 15; y++) {
    for (int x = 0; x < 19; x++) {
      draw_sprite_xpm(background_cube, x_, y_);
      x_ += 30;
    }
    x_ = 117;
    y_ += 30;
  }
  draw_line(117, 511, 571, 0x77bbff, drawing_frame_buffer);
  draw_rectangle(687, 60, 1, 452, 0x77bbff, drawing_frame_buffer);
}

void update_player_starting_position1() {
  playerPosition.x = 537;
  playerPosition.y = 361;
  copy.x = 537;
  copy.y = 361;
}

void draw_game_level1() {
  memset(&ice_cubes, 0, sizeof(ice_cubes));

  if (level1_draw_counter == 0) {
    memset(&water_path, 0, sizeof(water_path));
    update_player_starting_position1();
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

  // draw player
  draw_sprite_xpm(player, playerPosition.x, playerPosition.y);

  ice_melt();

  // check if player has completed the path
  if (playerPosition.x == finish_level1.top_left_x && playerPosition.y == finish_level1.top_left_y) {
    gameLevel = LEVEL_2;
  }

  level1_draw_counter++;
  check_fell_into_water(LEVEL_1);
}

void check_fell_into_water(GameLevel gameLevel) {
  // check if player has fallen into the water
  for (int i = 0; i < 150; i++) {
    if (water_path[i].top_left_x == playerPosition.x && water_path[i].top_left_y == playerPosition.y) {
      menuState = GAME;
      level1_draw_counter = 0;
      level2_draw_counter = 0;
      level3_draw_counter = 0;
      level4_draw_counter = 0;
      level5_draw_counter = 0;
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

  for (int i = 0; i < 150; i++) {
    if (water_path[i].top_left_x > 0 && water_path[i].top_left_y < 600) {
      draw_sprite_xpm(water, water_path[i].top_left_x, water_path[i].top_left_y);
    }
  }

  copy.x = playerPosition.x;
  copy.y = playerPosition.y;
}

void update_player_starting_position2() {
  playerPosition.x = 177;
  playerPosition.y = 361;
  copy.x = 177;
  copy.y = 361;
}

void draw_game_level2() {

  memset(&ice_cubes, 0, sizeof(ice_cubes));

  if (level2_draw_counter == 0) {
    memset(&water_path, 0, sizeof(water_path));
    update_player_starting_position2();
  }

  // draw level2 tag on the top left corner
  draw_sprite_xpm(level2_tag, 135, 32);

  // draw level2 ice cubes
  int x_ = 147;
  int y_ = 331;
  int ice_cube_counter = 0;
  Box ic;
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

  x_ = 177;
  y_ = 331;

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

  x_ = 267;
  y_ = 271;

  for (int y = 0; y < 2; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ += 30;
  }

  x_ = 327;
  y_ = 331;

  for (int y = 0; y < 2; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ += 30;
  }

  x_ = 297;
  y_ = 271;

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

  x_ = 357;
  y_ = 331;

  for (int x = 0; x < 2; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }

  x_ = 387;
  y_ = 361;

  for (int y = 0; y < 2; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ += 30;
  }

  x_ = 417;
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

  x_ = 567;
  y_ = 391;

  for (int y = 0; y < 6; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ -= 30;
  }

  ic.top_left_x = 537;
  ic.top_left_y = 240;
  ic.bot_right_x = 537 + 30;
  ic.bot_right_y = 240 + 30;
  ice_cubes[ice_cube_counter] = ic;
  draw_sprite_xpm(ice_cube, 537, 240);
  ice_cube_counter++;

  x_ = 507;
  y_ = 241;

  for (int y = 0; y < 4; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ += 30;
  }

  x_ = 447;
  y_ = 301;

  for (int y = 0; y < 2; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ += 30;
  }

  ic.top_left_x = 477;
  ic.top_left_y = 331;
  ic.bot_right_x = 477 + 30;
  ic.bot_right_y = 331 + 30;
  ice_cubes[ice_cube_counter] = ic;
  draw_sprite_xpm(ice_cube, 477, 331);
  ice_cube_counter++;

  // draw level2 path cubes
  x_ = 177;
  y_ = 361;
  for (int x = 0; x < 5; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    x_ += 30;
  }

  draw_sprite_xpm(path_cube, 297, 331);

  x_ = 297;
  y_ = 301;
  for (int x = 0; x < 5; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    x_ += 30;
  }

  draw_sprite_xpm(path_cube, 417, 331);

  x_ = 417;
  y_ = 361;
  for (int x = 0; x < 5; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    x_ += 30;
  }

  x_ = 537;
  y_ = 331;
  for (int y = 0; y < 3; y++) {
    draw_sprite_xpm(path_cube, x_, y_);
    y_ -= 30;
  }

  // draw red cube
  x_ = 537;
  y_ = 271;
  finish_level2.top_left_x = 537;
  finish_level2.top_left_y = 271;
  finish_level2.bot_right_x = 537 + 30;
  finish_level2.bot_right_y = 271 + 30;
  draw_sprite_xpm(red_cube, x_, y_);

  // draw player
  draw_sprite_xpm(player, playerPosition.x, playerPosition.y);

  ice_melt();

  // check if player has completed the path
  if (playerPosition.x == finish_level2.top_left_x && playerPosition.y == finish_level2.top_left_y) {
    gameLevel = LEVEL_3;
  }

  level2_draw_counter++;
  check_fell_into_water(LEVEL_2);
}

void update_player_starting_position3() {
  playerPosition.x = 537;
  playerPosition.y = 271;
  copy.x = 537;
  copy.y = 271;
}

void draw_game_level3() {

  memset(&ice_cubes, 0, sizeof(ice_cubes));

  if (level3_draw_counter == 0) {
    memset(&water_path, 0, sizeof(water_path));
    update_player_starting_position3();
  }

  // draw level3 ice cubes
  int x_ = 177;
  int y_ = 271;
  int ice_cube_counter = 0;
  Box ic;
  for (int y = 0; y < 5; y++) {
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
  y_ = 421;
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

  x_ = 267;
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

  x_ = 357;
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

  x_ = 447;
  y_ = 391;
  for (int x = 0; x < 2; x++) {
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
  for (int y = 0; y < 6; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ += 30;
  }

  x_ = 567;
  y_ = 241;
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
  y_ = 271;
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

  x_ = 477;
  y_ = 331;
  for (int x = 0; x < 5; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ -= 30;
  }

  x_ = 357;
  y_ = 301;
  for (int x = 0; x < 5; x++) {
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
  y_ = 271;
  ic.top_left_x = x_;
  ic.top_left_y = y_;
  ic.bot_right_x = x_ + 30;
  ic.bot_right_y = y_ + 30;
  ice_cubes[ice_cube_counter] = ic;
  draw_sprite_xpm(ice_cube, x_, y_);
  ice_cube_counter++;

  x_ = 237;
  y_ = 241;
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

  x_ = 267;
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

  // draw level3 tag on the top left corner
  draw_sprite_xpm(level3_tag, 135, 32);

  // draw level3 path cubes
  x_ = 537;
  y_ = 271;
  for (int y = 0; y < 5; y++) {
    draw_sprite_xpm(path_cube, x_, y_);
    y_ += 30;
  }

  x_ = 507;
  y_ = 361;
  for (int y = 0; y < 2; y++) {
    draw_sprite_xpm(path_cube, x_, y_);
    y_ += 30;
  }

  x_ = 447;
  y_ = 361;
  for (int x = 0; x < 2; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    x_ += 30;
  }

  x_ = 417;
  y_ = 361;
  for (int y = 0; y < 2; y++) {
    draw_sprite_xpm(path_cube, x_, y_);
    y_ += 30;
  }

  x_ = 387;
  y_ = 361;
  for (int y = 0; y < 2; y++) {
    draw_sprite_xpm(path_cube, x_, y_);
    y_ += 30;
  }

  x_ = 237;
  y_ = 361;
  for (int y = 0; y < 2; y++) {
    draw_sprite_xpm(path_cube, x_, y_);
    y_ += 30;
  }

  x_ = 207;
  y_ = 301;
  for (int y = 0; y < 4; y++) {
    draw_sprite_xpm(path_cube, x_, y_);
    y_ += 30;
  }

  x_ = 297;
  y_ = 331;
  for (int y = 0; y < 2; y++) {
    draw_sprite_xpm(path_cube, x_, y_);
    y_ += 30;
  }

  x_ = 327;
  y_ = 331;
  for (int y = 0; y < 2; y++) {
    draw_sprite_xpm(path_cube, x_, y_);
    y_ += 30;
  }

  x_ = 267;
  y_ = 361;
  draw_sprite_xpm(path_cube, x_, y_);

  x_ = 357;
  y_ = 361;
  draw_sprite_xpm(path_cube, x_, y_);

  // draw red cube
  x_ = 207;
  y_ = 271;
  finish_level3.top_left_x = 207;
  finish_level3.top_left_y = 271;
  finish_level3.bot_right_x = 207 + 30;
  finish_level3.bot_right_y = 271 + 30;
  draw_sprite_xpm(red_cube, x_, y_);

  // draw player
  draw_sprite_xpm(player, playerPosition.x, playerPosition.y);

  ice_melt();

  // check if player has completed the path
  if (playerPosition.x == finish_level3.top_left_x && playerPosition.y == finish_level3.top_left_y) {
    gameLevel = LEVEL_4;
  }

  level3_draw_counter++;
  check_fell_into_water(LEVEL_3);
}

void update_player_starting_position4() {
  playerPosition.x = 207;
  playerPosition.y = 271;
  copy.x = 207;
  copy.y = 271;
}

void draw_game_level4() {
  memset(&ice_cubes, 0, sizeof(ice_cubes));

  if (level4_draw_counter == 0) {
    memset(&water_path, 0, sizeof(water_path));
    update_player_starting_position4();
  }

  int x_;
  int y_;

  // draw level4 tag
  // draw_sprite_xpm(level3_tag, 135, 32);

  // ice cubes
  x_ = 177;
  y_ = 301;
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

  x_ = 177;
  y_ = 271;
  for (int y = 0; y < 3; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ -= 30;
  }

  x_ = 147;
  y_ = 211;
  for (int y = 0; y < 5; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ -= 30;
  }

  x_ = 177;
  y_ = 91;
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

  x_ = 267;
  y_ = 121;
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

  x_ = 267;
  y_ = 151;
  for (int x = 0; x < 2; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }

  x_ = 447;
  y_ = 151;
  for (int x = 0; x < 2; x++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    x_ += 30;
  }

  x_ = 477;
  y_ = 91;
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

  x_ = 597;
  y_ = 121;
  for (int y = 0; y < 4; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ += 30;
  }

  x_ = 567;
  y_ = 211;
  for (int y = 0; y < 4; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ += 30;
  }

  x_ = 507;
  y_ = 211;
  for (int y = 0; y < 4; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ += 30;
  }

  x_ = 477;
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

  x_ = 447;
  y_ = 241;
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

  x_ = 417;
  y_ = 301;
  for (int x = 0; x < 5; x++) {
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
  y_ = 271;
  for (int y = 0; y < 2; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ -= 30;
  }

  x_ = 297;
  y_ = 271;
  for (int y = 0; y < 2; y++) {
    ic.top_left_x = x_;
    ic.top_left_y = y_;
    ic.bot_right_x = x_ + 30;
    ic.bot_right_y = y_ + 30;
    ice_cubes[ice_cube_counter] = ic;
    draw_sprite_xpm(ice_cube, x_, y_);
    ice_cube_counter++;
    y_ -= 30;
  }

  x_ = 237;
  y_ = 211;
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

  ic.top_left_x = 537;
  ic.top_left_y = 301;
  ic.bot_right_x = 537 + 30;
  ic.bot_right_y = 301 + 30;
  ice_cubes[ice_cube_counter] = ic;
  draw_sprite_xpm(ice_cube, 537, 301);
  ice_cube_counter++;

  ic.top_left_x = 537;
  ic.top_left_y = 151;
  ic.bot_right_x = 537 + 30;
  ic.bot_right_y = 151 + 30;
  ice_cubes[ice_cube_counter] = ic;
  draw_sprite_xpm(ice_cube, 537, 151);
  ice_cube_counter++;

  ic.top_left_x = 207;
  ic.top_left_y = 151;
  ic.bot_right_x = 207 + 30;
  ic.bot_right_y = 151 + 30;
  ice_cubes[ice_cube_counter] = ic;
  draw_sprite_xpm(ice_cube, 207, 151);
  ice_cube_counter++;

  // PATH CUBES
  // playerPosition.x = 207;
  // playerPosition.y = 271;
  x_ = 207;
  y_ = 271;
  for (int y = 0; y < 3; y++) {
    draw_sprite_xpm(path_cube, x_, y_);
    y_ -= 30;
  }
  x_ = 177;
  y_ = 181;
  for (int x = 0; x < 14; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    x_ += 30;
  }
  x_ = 177;
  y_ = 121;
  for (int x = 0; x < 3; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    x_ += 30;
  }
  x_ = 507;
  y_ = 121;
  for (int x = 0; x < 3; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    x_ += 30;
  }
  draw_sprite_xpm(path_cube, 177, 151);
  draw_sprite_xpm(path_cube, 507, 151);
  draw_sprite_xpm(path_cube, 237, 151);
  draw_sprite_xpm(path_cube, 567, 151);
  x_ = 327;
  y_ = 151;
  for (int x = 0; x < 4; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    x_ += 30;
  }
  draw_sprite_xpm(path_cube, 357, 211);
  draw_sprite_xpm(path_cube, 387, 211);
  x_ = 327;
  y_ = 271;
  for (int x = 0; x < 4; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    draw_sprite_xpm(path_cube, x_, y_ - 30);
    x_ += 30;
  }
  draw_sprite_xpm(path_cube, 537, 241);
  draw_sprite_xpm(path_cube, 537, 211);
  // cubo vermelho

  x_ = 537;
  y_ = 271;
  finish_level4.top_left_x = 537;
  finish_level4.top_left_y = 271;
  finish_level4.bot_right_x = 537 + 30;
  finish_level4.bot_right_y = 271 + 30;
  draw_sprite_xpm(red_cube, x_, y_);

  // player
  draw_sprite_xpm(player, playerPosition.x, playerPosition.y);

  ice_melt();

  // check if player has completed the path
  if (playerPosition.x == finish_level4.top_left_x && playerPosition.y == finish_level4.top_left_y) {
    gameLevel = LEVEL_5;
  }

  level4_draw_counter++;
  check_fell_into_water(LEVEL_4);
}

void update_player_starting_position5() {
  playerPosition.x = 537;
  playerPosition.y = 271;
  copy.x = 537;
  copy.y = 271;
}

void draw_game_level5() {
  memset(&ice_cubes, 0, sizeof(ice_cubes));

  if (level5_draw_counter == 0) {
    memset(&water_path, 0, sizeof(water_path));
    update_player_starting_position5();
  }

  draw_sprite_xpm(level2_tag, 135, 32);

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
    x_ += 30;
  }

  x_ = 267;
  y_ = 391;
  for (int x = 0; x < 12; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    x_ += 30;
  }

  x_ = 237;
  y_ = 331;
  for (int x = 0; x < 13; x++) {
    draw_sprite_xpm(path_cube, x_, y_);
    x_ += 30;
  }

  x_ = 537;
  y_ = 271;
  draw_sprite_xpm(path_cube, x_, y_);

  x_ = 537;
  y_ = 301;
  draw_sprite_xpm(path_cube, x_, y_);

  // draw red cube
  x_ = 177;
  y_ = 361;
  finish_level5.top_left_x = 177;
  finish_level5.top_left_y = 361;
  finish_level5.bot_right_x = 177 + 30;
  finish_level5.bot_right_y = 361 + 30;
  draw_sprite_xpm(red_cube, x_, y_);

  // draw player
  draw_sprite_xpm(player, playerPosition.x, playerPosition.y);

  ice_melt();

  // check if player has completed the path
  if (playerPosition.x == finish_level5.top_left_x && playerPosition.y == finish_level5.top_left_y) {
    gameLevel = LEVEL_6;
  }

  level5_draw_counter++;
  check_fell_into_water(LEVEL_5);
}

void update_player_starting_position6() {
  playerPosition.x = 537;
  playerPosition.y = 271;
  copy.x = 537;
  copy.y = 271;
}

void draw_game_level6() {

  memset(&ice_cubes, 0, sizeof(ice_cubes));

  if (level6_draw_counter == 0) {
    memset(&water_path, 0, sizeof(water_path));
    update_player_starting_position6();
  }

  int x_;
  int y_;

  // draw level6 tag
  //  draw_sprite_xpm(level6_tag, 135, 32);

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

  x_ = 447;
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

  // draw red cube

  x_ = 297;
  y_ = 211;
  finish_level6.top_left_x = 297;
  finish_level6.top_left_y = 211;
  finish_level6.bot_right_x = 297 + 30;
  finish_level6.bot_right_y = 211 + 30;
  draw_sprite_xpm(red_cube, x_, y_);

  // player
  draw_sprite_xpm(player, playerPosition.x, playerPosition.y);

  ice_melt();

  // check if player has completed the path
  if (playerPosition.x == finish_level6.top_left_x && playerPosition.y == finish_level6.top_left_y) {
    // gameLevel = LEVEL_7;
  }

  level6_draw_counter++;
  check_fell_into_water(LEVEL_6);
}

void draw_finish_menu() {
  draw_sprite_xpm(end_screen, 0, 0);
  draw_sprite_xpm(finish_button, 340, 467);
}

// O cursor mode ter dois estados:
// - "normal", quando está no menu de início ou de fim
void draw_mouse() {
  switch (menuState) {
    case START:
    case END:
      draw_sprite_xpm(mouse, mouse_info.x, mouse_info.y);
      break;
    case GAME:
      break;
  }
}

// A função recebe um objeto Sprite proveniente de um XPM e mostra-o nas coordenadas (x, y)
// Usa as cores dinamicamente alocadas na altura da construção
// A função ignora a cor transparente do XPM para não modificar o fundo quando não é preciso
int draw_sprite_xpm(Sprite *sprite, int x, int y) {
  uint16_t height = sprite->height;
  uint16_t width = sprite->width;
  uint32_t current_color;
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      current_color = sprite->colors[w + h * width];
      if (current_color == TRANSPARENT)
        continue;
      if (draw_pixel(x + w, y + h, current_color, drawing_frame_buffer) != 0)
        return 1;
    }
  }
  return 0;
}
