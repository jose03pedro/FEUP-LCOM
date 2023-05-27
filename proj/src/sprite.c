#include "sprite.h"

Sprite_t *sprite_create(xpm_map_t sprite) {
  Sprite_t *sp = (Sprite_t *) malloc(sizeof(sprite));

  xpm_image_t img;
  sp->colors = (uint32_t *) xpm_load(sprite, XPM_8_8_8_8, &img);
  sp->width = img.width;
  sp->height = img.height;
  return sp;
}