#include "vga_out.h"


void printVal(int x, int pos){
    if(x == 0)
        return xpc((x % 10) + '0', 0x7, pos);
    int c = 0;
    char sign = ' ';
    if(x < 0){
        x = -x;
        sign = '-';
    }
    while(x != 0) {
        xpc((x % 10) + '0', 0x7, c-- + pos);
        x /= 10;
    }
    xpc(sign, 0x7, c-- + pos);
}

void memDump(void* s, void* e, int pos) {
    int c = 0;
    for(char* p = s; p < e; ++p) {
        printVal(*p, (c++ * 4) + pos);
    }
}


void xpc(char c, char attr, int i) {
    char* addr = 0xB8000 + i * 2;
    *(addr) = c;
    *(addr + 1) = attr;
}

char Kotlin_Int_toByte(int i) {
    return (char)i;
}

char Kotlin_Char_toByte(int i) {
    return (char)i;
}

int Kotlin_Int_inc(int i) {
    return i + 1;
}
