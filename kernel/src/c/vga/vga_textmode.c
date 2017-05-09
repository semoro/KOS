#include "vga_textmode.h"
#include "../../res/resource_data.h"
#include "../../res/font/font_data.h"
#include <stdbool.h>


void vga_textmode_write(char c, char attr, int i) {
    if(i > 80 * 25) return;
    char* addr = 0xB8000 + i * 2;
    *(addr) = c;
    *(addr + 1) = attr;
}

void screen_write(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t *addr = 0x400000 + (x * 3) + (y * 1024 * 3);
    *(addr)     = r;
    *(addr + 1) = g;
    *(addr + 2) = b;
}

void screen_write_rgb(uint16_t x, uint16_t y, uint32_t rgb) {
    void *addr = 0x400000 + (x * 3) + (y * 1024 * 3);
    *((uint8_t*)addr)         = (uint8_t)(rgb >> 16);
    *((uint8_t*)addr + 1)     = (uint8_t)(rgb >> 8);
    *((uint8_t*)addr + 2)     = (uint8_t)(rgb >> 0);
}

uint32_t screen_get_rgb(uint16_t x, uint16_t y) {
    void *addr = 0x400000 + (x * 3) + (y * 1024 * 3);
    return *((uint32_t*)addr) >> 8;
}


font_glyph_data_t font_data_remaped[256];
bool font_ready = false;

void prepare_font() {
    font_data_t data = get_font_data();
    for(int i = 0; i < data.glyph_count; i++) 
        font_data_remaped[data.glyphs[i].symbol] = data.glyphs[i];
    font_ready = true;
}

font_glyph_data_t * get_glyph_by_char (char c) {
    return &font_data_remaped[c];
}

void draw_font_symbol (font_glyph_data_t * data, uint16_t x, uint16_t y, uint32_t color) {
    uint8_t *img = get_resource_ptr_by_id(FONT_ID);
    
    for(int ix = 0; ix < data->w; ix++) {
        for(int iy = 0; iy < data->h; iy++) {
            uint16_t scx, scy;
            scx = x + ix + data->ox;
            scy = y + iy + data->oy;
            uint32_t p = screen_get_rgb(scx, scy);
            uint8_t d = img[data->x + ix + (data->y + iy) * FONT_IMG_WIDTH];
            
            uint64_t mix = (color * d + p * (0xFF - d)) / 0xFF;
            
            screen_write_rgb(scx, scy, mix);
        }
    }
}

void draw_text (const char * s, uint16_t x, uint16_t y, uint32_t color) {
    uint16_t xadv = 0;
    while(*s != 0) {
        font_glyph_data_t data = font_data_remaped[*s];
        draw_font_symbol(&data, x + xadv, y, color);
        xadv += data.advence;
        s++;
    }
}

