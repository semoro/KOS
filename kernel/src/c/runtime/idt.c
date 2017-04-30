#include "idt.h"
#include "hardware/PIC.h"
#include "hardware/io.h"
#include "vga/utils.h"
#include "interrupts.h"
#define REGISTER_EX_IRQ(i) fill_idt_entry(entries + i, &handle_ex_##i, 0x0008, 0b10001111)


__attribute__ ((interrupt))
void handle_interrupt(struct interrupt_frame *frame) {
    uint8_t irr = inb(0x20);
    vga_textmode_print("Unsupported IRQ", 0x7, 80 * 2);
    vga_textmode_print_int(irr, 0x7, 80 * 2 + 15);
    abort();
}

static inline void lidt(void* base, uint16_t size)
{   // This function works in 32 and 64bit mode
    struct {
        uint16_t length;
        uint64_t    base;
    } __attribute__((packed)) IDTR = { size, base };
 
    asm ( "lidt %0" : : "m"(IDTR) );  // let the compiler choose an addressing mode
}

static inline void enable_interrupts() {
    asm ("sti");
}

void setup_keyboard_interrupt() {
    outb(0x21,0xfd);
    outb(0xa1,0xff);
    enable_interrupts();
}

void fill_idt_entry(idt_entry_t *entry, void *handler, uint8_t selector, uint8_t type_attr) {
    entry->selector = selector;
    entry->type_attr = type_attr; // 1 exists, 00 DPL = ring 0, 0 reserved, 1111 x86 trap gate
    
    uint64_t isr_ex = handler;
    entry->offset_1 = 0xFFFF & isr_ex;
    entry->offset_2 = 0xFFFF & (isr_ex >> 16);
}

void setup_idt() {
    PIC_remap(0x20, 0x28);
    
    idt_entry_t *entries = &idt_first_entry;
    
    for(idt_entry_t *first = entries + 0x20; first != entries + 0x28 + 8; first++){
       fill_idt_entry(first, &handle_interrupt, 0x0008, 0b10001110);
    }
    
    REGISTER_EX_IRQ(0);
    REGISTER_EX_IRQ(1);
    REGISTER_EX_IRQ(2);
    REGISTER_EX_IRQ(3);
    REGISTER_EX_IRQ(4);
    REGISTER_EX_IRQ(5);
    REGISTER_EX_IRQ(6);
    REGISTER_EX_IRQ(7);
    REGISTER_EX_IRQ(8);
    REGISTER_EX_IRQ(9);
    REGISTER_EX_IRQ(10);
    REGISTER_EX_IRQ(11);
    REGISTER_EX_IRQ(12);
    REGISTER_EX_IRQ(13);
    REGISTER_EX_IRQ(14);
    REGISTER_EX_IRQ(15);
    REGISTER_EX_IRQ(16);
    REGISTER_EX_IRQ(17);
    REGISTER_EX_IRQ(18);
    REGISTER_EX_IRQ(19);
    REGISTER_EX_IRQ(20);
    REGISTER_EX_IRQ(21);
    REGISTER_EX_IRQ(22);
    REGISTER_EX_IRQ(23);
    REGISTER_EX_IRQ(24);
    REGISTER_EX_IRQ(25);
    REGISTER_EX_IRQ(26);
    REGISTER_EX_IRQ(27);
    REGISTER_EX_IRQ(28);
    REGISTER_EX_IRQ(29);
    REGISTER_EX_IRQ(30);
    REGISTER_EX_IRQ(31);
    
    
    lidt(entries, 100 * sizeof(idt_entry_t));
    
    
    outb(0x21,0xfd);
    outb(0xa1,0xff);
    enable_interrupts();

}


