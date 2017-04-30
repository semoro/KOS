#ifndef VGA_TEXTMODE_UTILS_H
#define VGA_TEXTMODE_UTILS_H 
#include <inttypes.h>


void vga_textmode_memdump(void* s, void* e, int pos);
void vga_textmode_print(const char* message, uint8_t attr, int pos);
void vga_textmode_print_ptr(uint64_t x, uint8_t attr, int pos);
void vga_textmode_print_int(int x, uint8_t attr, int pos);
void vga_textmode_print_float(float x, uint8_t attr, int pos);

#endif
