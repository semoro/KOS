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

const char* clear_line = "                                                                                ";

void printUsedMemory() {
    
    vga_textmode_print(clear_line, 0x7, 80 * 20);
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
    
    
    vga_textmode_print("Allocations: ", 0x7, 80 * 20 + 30);
    vga_textmode_print_int(allocations, 0x7, 80 * 20 + 30 + 13);
    
    vga_textmode_print("Alloc ", 0x7, 80 * 21);
    vga_textmode_print_ptr(allocPtr, 0x7, 80 * 21 + 6);
    
}

uint64_t aligned_alloc(uint64_t size, uint64_t align) {
    uint64_t addr = ((allocPtr / align) + 1) * align;
   
    allocated += addr - allocPtr + size;
    allocations++;
    allocPtr = addr + size;
    printUsedMemory();
    
    return addr;
}

uint64_t malloc(uint64_t size) {
    return aligned_alloc(size, 64);
}

uint64_t calloc(uint64_t size, uint64_t number) {
    char* ptr = malloc(size * number);
    return memset(ptr, 0, size * number);
}


void free(void* ptr) {
    vga_textmode_print("Free ", 0x7, 80 * 22);
    vga_textmode_print_ptr(ptr, 0x7, 80 * 22 + 5);
}

void set_pae_table_address(uint32_t addr) {
    asm volatile ("movq %%rax, %%cr3" :: "a" (addr)); 
}

uint32_t get_int_at_addr(void* addr) {
    return *((uint32_t*)addr);
}

char* setlocale (int category, const char* locale) {
    return 0x1;
}
