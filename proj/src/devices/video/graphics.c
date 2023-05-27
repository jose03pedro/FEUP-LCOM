#include "graphics.h"
#include <lcom/lcf.h>
#include <math.h>

int(set_graphic_mode)(uint16_t submode) {
  reg86_t reg86;
  memset(&reg86, 0, sizeof(reg86));
  reg86.intno = 0x10;
  reg86.ax = 0x4F02;
  reg86.bx = submode | BIT(14);
  return sys_int86(&reg86);
}

int(set_frame_buffer)(uint16_t mode, uint8_t **frame_buffer) {
  memset(&mode_info, 0, sizeof(mode_info));
  vbe_get_mode_info(mode, &mode_info);
  unsigned int frame_size = (mode_info.XResolution * mode_info.YResolution * mode_info.BitsPerPixel) / 8;
  struct minix_mem_range physic_addresses;
  physic_addresses.mr_base = mode_info.PhysBasePtr;
  physic_addresses.mr_limit = physic_addresses.mr_base + frame_size;
  sys_privctl(SELF, SYS_PRIV_ADD_MEM, &physic_addresses);
  *frame_buffer = vm_map_phys(SELF, (void *) physic_addresses.mr_base, frame_size);
  if (frame_buffer == NULL)
    return 1;
  return 0;
}

int(draw_pixel)(uint16_t x, uint16_t y, uint32_t color, uint8_t *frame_buffer) {
  if (x >= mode_info.XResolution || y >= mode_info.YResolution)
    return 1;
  unsigned BytesPerPixel = (mode_info.BitsPerPixel + 7) / 8;
  unsigned int index = (mode_info.XResolution * y + x) * BytesPerPixel;
  memcpy(&frame_buffer[index], &color, BytesPerPixel);
  return 0;
}

int(draw_line)(uint16_t x, uint16_t y, uint16_t len, uint32_t color, uint8_t *frame_buffer) {
  for (unsigned i = 0; i < len; i++) draw_pixel(x + i, y, color, frame_buffer);
  return 0;
}

int(draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color, uint8_t *frame_buffer) {
  for (unsigned i = 0; i < height; i++) draw_line(x, y + i, width, color, frame_buffer);
  return 0;
}
