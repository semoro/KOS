 
#ifndef FONT_DEFS_H
#define FONT_DEFS_H

#include <inttypes.h>

typedef struct {
    uint16_t symbol;
    uint16_t x, y;
    uint8_t w, h;
    int8_t ox, oy;
    uint8_t advence;
    
} font_glyph_data_t;

typedef struct {
    uint8_t w, h;
    uint32_t glyph_count;
    font_glyph_data_t* glyphs;
} font_data_t;

#endif
