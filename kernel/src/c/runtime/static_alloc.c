#include "../vga/utils.h"

void* static_alloc(void* position) {
    return position;
}
 
int allocPtr = 0x02000000 + 268435456;

int allocInfo = 0;

int malloc(int size) {
    int tmp = allocPtr;
    vga_textmode_print("Alloc ", 0x7, 80 * 21 + 17 * (allocInfo % 5));
    vga_textmode_print_int(tmp, 80 * 21 + 16 + 17 * (allocInfo++ % 5));
    //AssertionFailedPx("", "Alloc has been done");
    allocPtr += size;
    return tmp;
}

int calloc(int size, int number) {
    char* ptr = malloc(size * number);
    for(int i = 0; i < size * number; i ++)
        *(ptr+i) = 0;
    return ptr;
}

void free(void* ptr) {
    vga_textmode_print("Free ", 0x7, 80 * 20);
    vga_textmode_print_int(ptr, 80 * 20 + 16);
}

