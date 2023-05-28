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

/**
 * @brief Define os limites de uma caixa, utilizado nos blocos que têm uma função no jogo.
 * 
 */
typedef struct {
  int top_left_x;
  int top_left_y;
  int bot_right_x;
  int bot_right_y;
} Box;

/**
 * @brief Aloca memória ao buffer. No caso de double buffer, o buffer secundário tem a mesma dimensão de memória.
 * 
 * @param mode 
 * @return int 
 */
int set_frame_buffers(uint16_t mode);
/**
 * @brief Verifica que nível / menu deve ser desenhado consoante gameState e menuState e chama as funções necess+arias para o desenhar.
 * 
 */
void draw_new_frame();
/**
 * @brief Desenha o menu inicial e os botões relevantes.
 * 
 */
void draw_initial_menu();
/**
 * @brief Desenha a interface do jogo, a "consola" e o background.
 * 
 */
void draw_game_menu();
/**
 * @brief Verifica se o player caiu na água e reinicia o nível se for o caso.
 * 
 */
void check_fell_into_water();
/**
 * @brief Verifica se o player se moveu e transforma a posição anterior em água.
 * 
 */
void ice_melt();
/**
 * @brief Compara os counters, verificando se o player derreteu todo o gelo para poder passar de nível.
 * 
 * @return true 
 * @return false 
 */
bool check_all_ice_melted();
/**
 * @brief Põe os valores de todos os draw_counters a 0.
 * 
 */
void reset_all_draw_counters();
/**
 * @brief Desenha o menu final.
 * 
 */
void draw_finish_menu();
/**
 * @brief Desenha o cursor do rato onde necessário.
 * 
 */
void draw_mouse();
/**
 * @brief Copia info do secondary buffer para o main buffer-
 * 
 */
void swap_buffers();
/**
 * @brief Desenha uma determinada sprite nas coordenadas (x, y).
 * 
 * @param sprite
 * @param x
 * @param y
 * @return int
 */
int draw_sprite(Sprite_t *sprite, int x, int y);

#endif
