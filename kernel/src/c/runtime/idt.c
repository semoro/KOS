#include "idt.h"
#include "hardware/PIC.h"
#include "hardware/io.h"
#include "vga/utils.h"


__attribute__ ((interrupt))
void handle_interrupt(struct interrupt_frame *frame) {
    uint8_t irr = inb(0x20);
    vga_textmode_print("Unsupported IRQ", 0x7, 80 * 2);
    vga_textmode_print_int(irr, 20 + 80 * 2);
    abort();
}

__attribute__ ((interrupt))
void handle_exception_interrupt(struct interrupt_frame *frame) {
    uint8_t irr = inb(0x20);
    vga_textmode_print("Exception interrupt", 0x7, 80 * 2);
    vga_textmode_print_int(irr, 25 + 80 * 2);
    abort();
}


__attribute__ ((interrupt))
void handle_interrupt_14(struct interrupt_frame *frame) {
    vga_textmode_print("Page fault", 0x7, 80 * 2);
    abort();
}


__attribute__ ((interrupt))
void handle_interrupt_8(struct interrupt_frame *frame) {
    vga_textmode_print("Double fault", 0x7, 80 * 2);
    abort();
}

__attribute__ ((interrupt))
void handle_interrupt_X(struct interrupt_frame *frame) {
    vga_textmode_print("X interrupt", 0x7, 80 * 2);
    
}

static inline void lidt(void* base, uint16_t size)
{   // This function works in 32 and 64bit mode
    struct {
        uint16_t length;
        uint64_t    base;
    } __attribute__((packed)) IDTR = { size, base };
 
    asm ( "lidt %0" : : "m"(IDTR) );  // let the compiler choose an addressing mode
}


void enable_interrupts() {
    asm ("sti");
}

void setup_keyboard_interrupt() {
    outb(0x21,0xfd);
    outb(0xa1,0xff);
    enable_interrupts();
}

void fill_idt_entry(idt_entry_t *entry, void *handler, uint8_t selector, uint8_t type_attr) {
    entry->selector = 0x0008;
    entry->type_attr = 0b10001111; // 1 exists, 00 DPL = ring 0, 0 reserved, 1111 x86 trap gate
    
    uint64_t isr_ex = handler;
    entry->offset_1 = 0xFFFF & isr_ex;
    entry->offset_2 = 0xFFFF & (isr_ex >> 16);
}

void setup_idt() {
    PIC_remap(0x20, 0x28);
    
    
    idt_entry_t *entries = &idt_first_entry;
    
    for(idt_entry_t *first = entries; first != entries + 0x20; first++){
       fill_idt_entry(first, &handle_exception_interrupt, 0x0008, 0b10001111);
    }
  
    
    
    for(idt_entry_t *first = entries + 0x20; first != entries + 0x28 + 8; first++){
       fill_idt_entry(first, &handle_interrupt, 0x0008, 0b10001110);
    }
    
    fill_idt_entry(entries + 13, &handle_interrupt_X, 0x0008, 0b10001111);
    
    
    fill_idt_entry(entries + 8, &handle_interrupt_8, 0x0008, 0b10001111);
    
    fill_idt_entry(entries + 14, &handle_interrupt_14, 0x0008, 0b10001111);
    
    
    lidt(entries, 100 * sizeof(idt_entry_t));
    
    
    outb(0x21,0xfd);
    outb(0xa1,0xff);
    enable_interrupts();

}


