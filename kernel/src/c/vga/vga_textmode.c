#include "vga_textmode.h"

void vga_textmode_write(char c, char attr, int i) {
    if(i > 80 * 25) return;
    char* addr = 0xB8000 + i * 2;
    *(addr) = c;
    *(addr + 1) = attr;
}

