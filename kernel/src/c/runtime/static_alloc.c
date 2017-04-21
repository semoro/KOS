#include "../vga/utils.h"

void* static_alloc(void* position) {
    return position;
}

void* free_space_start;

int allocPtr = 0;

void initialize_memory_allocation() {
    allocPtr = &free_space_start;
}

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
