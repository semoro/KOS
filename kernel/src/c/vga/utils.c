#include "vga_textmode.h"
#include "utils.h"
#include "inttypes.h"

static inline int powi(int a, int power) {
    int res = 1;
    for (int i = 0; i < power; i++) {
        res *= a;
    }
    return res;
}

void vga_textmode_print_int(int x, uint8_t attr, int pos) {
    for (int i = 1; i <= 10; i++) {
        uint8_t s = (x / powi(10, 10 - i)) % 10;
        if (s > 0 || i == 10)
            vga_textmode_write('0' + s, 0x7, pos++);
    }
} 

void vga_textmode_print_float(float f, uint8_t attr, int pos) {
    int x = (int)f;
    for (int i = 1; i <= 10; i++) {
        uint8_t s = (x / powi(10, 10 - i)) % 10;
        if (s > 0 || i == 10)
            vga_textmode_write('0' + s, 0x7, pos++);
    }
    vga_textmode_write('.', 0x7, pos++);
    x = (int)((f - x) * 100);
    for (int i = 1; i <= 10; i++) {
        uint8_t s = (x / powi(10, 10 - i)) % 10;
        if (s > 0 || i == 10)
            vga_textmode_write('0' + s, 0x7, pos++);
    }
} 

void vga_textmode_print_ptr(uint64_t x, uint8_t attr, int pos) {
    
    vga_textmode_print("0x", attr, pos);
    for (int i = 1; i <= 16; i++) {
        uint8_t s = (x >> (64 - i * 4)) & 0xF;
        if (s >= 0xA) 
            vga_textmode_write('A' + (s - 0xA), attr, pos + 1 + i);
        else 
            vga_textmode_write('0' + s, attr, pos + 1 + i);
    }
} 


void vga_textmode_memdump(void* s, void* e, int pos) {
    int c = 0;
    for (char* p = s; p < e; ++p) {
        vga_textmode_print_int(*p, 0x7, (c++ * 4) + pos);
    }
}

void vga_textmode_print(const char* message, uint8_t attr, int pos) {
    int i = 0;
    while (*(message + i) != 0) {
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

