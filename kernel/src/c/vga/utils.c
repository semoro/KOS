#include "vga_textmode.h"

void vga_textmode_print_int(int x, int pos) {
    if(x == 0)
        return vga_textmode_write((x % 10) + '0', 0x7, pos);
    int c = 0;
    char sign = ' ';
    if(x < 0){
        x = -x;
        sign = '-';
    }
    while(x != 0) {
        vga_textmode_write((x % 10) + '0', 0x7, c-- + pos);
        x /= 10;
    }
    vga_textmode_write(sign, 0x7, c-- + pos);
} 


void vga_textmode_memdump(void* s, void* e, int pos) {
    int c = 0;
    for(char* p = s; p < e; ++p) {
        vga_textmode_print_int(*p, (c++ * 4) + pos);
    }
}

void vga_textmode_print(const char* message, char attr, int pos) {
    int i = 0;
    while(*(message + i) != 0){
        vga_textmode_write(*(message + i), attr, pos + i);
        i++;
    }
}



void AssertionFailedPX(const char* location, const char* message) {
    vga_textmode_print("Runtime assertion failed:", 0xc, 0);
    vga_textmode_print(location, 0xc, 80);
    vga_textmode_print(message, 0xc, 160);
    abort();
}

