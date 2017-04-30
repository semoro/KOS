#include "../vga/utils.h"

#include "inttypes.h"

void* static_alloc(void* position) {
    return position;
}

void* free_space_start;

uint64_t allocPtr = 0;

void initialize_memory_allocation() {
    allocPtr = &free_space_start;
}

uint64_t allocated = 0;
uint64_t allocations = 0;


void printUsedMemory() {
    vga_textmode_print("Used mem: ", 0x7, 80 * 20);
    double mem = allocated;
    int level = 0;
    while (mem > 1024) {
        mem /= 1024.0;
        level++;
    }
    vga_textmode_print_float(mem, 0x7, 80 * 20 + 10);
    switch (level) {
        case 0: 
            vga_textmode_print("B", 0x7, 80 * 20 + 18);
            break;
        case 1: 
            vga_textmode_print("KiB", 0x7, 80 * 20 + 18);
            break;
        case 2: 
            vga_textmode_print("MiB", 0x7, 80 * 20 + 18);
            break;
        case 3:
            vga_textmode_print("GiB", 0x7, 80 * 20 + 18);
            break;
        case 4:
            vga_textmode_print("TiB", 0x7, 80 * 20 + 18);
            break;
    }
    
}

uint64_t malloc(uint64_t size) {
    uint64_t tmp = allocPtr;
    allocated += size;
    allocations++;
    
    printUsedMemory();
    vga_textmode_print("Allocations: ", 0x7, 80 * 20 + 30);
    vga_textmode_print_int(allocations, 0x7, 80 * 20 + 30 + 13);
    
    vga_textmode_print("Alloc ", 0x7, 80 * 21);
    vga_textmode_print_ptr(tmp, 0x7, 80 * 21 + 6);
    
    allocPtr += size;
    return tmp;
}

uint64_t calloc(uint64_t size, uint64_t number) {
    char* ptr = malloc(size * number);
    for(uint64_t i = 0; i < size * number; i ++)
        *(ptr+i) = 0;
    return ptr;
}

void free(void* ptr) {
    vga_textmode_print("Free ", 0x7, 80 * 20);
    vga_textmode_print_ptr(ptr, 0x7, 80 * 20 + 5);
}

void * memset(void *ptr, int value, uint64_t num) {
    uint8_t fill = value;
    void* end = ptr + num;
    for(uint8_t *tptr = ptr; tptr != end; tptr++) {
        *tptr = value;
    }
    return ptr;
}
/*
typedef unsigned long uint64_t;

uint64_t page_dir_ptr_tab[4] __attribute__((aligned(0x20)));
uint64_t page_dir[512] __attribute__((aligned(0x1000)));  // must be aligned to page boundary
uint64_t page_tab[1024] __attribute__((aligned(0x1000)));


void setupPAE() {
    page_dir_ptr_tab[0] = (uint64_t)&page_dir | 1; // set the page directory into the PDPT and mark it present
    page_dir[0] = (uint64_t)&page_tab | 3; //set the page table into the PD and mark it present/writable
    page_dir[1] = (uint64_t)(&page_tab + 512) | 3; //set the page table into the PD and mark it present/writable
    
    unsigned int i, address = 0;
    for(i = 0; i < 1024; i++)
    {
        page_tab[i] = address | 3; // map address and mark it present/writable
        address = address + 0x1000;
    }
    	 
    asm volatile ("movq %%rax, %%cr3" :: "a" (&page_dir_ptr_tab)); // load PDPT into CR3
}

*/

char* setlocale (int category, const char* locale) {
    return 0x1;
}
