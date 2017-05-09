#ifndef VGA_TEXTMODE_H
#define VGA_TEXTMODE_H

#include <inttypes.h>




void vga_textmode_write(char, char, int);
void screen_write(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);


#endif
