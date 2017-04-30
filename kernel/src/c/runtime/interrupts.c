#include "interrupts.h"
#include "vga/utils.h"

__attribute__ ((interrupt)) void handle_ex_0(struct interrupt_frame *frame){ vga_textmode_print("Exception 0", 0x7, 80 * 2); abort(); }
__attribute__ ((interrupt)) void handle_ex_1(struct interrupt_frame *frame){ vga_textmode_print("Exception 1", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_2(struct interrupt_frame *frame){ vga_textmode_print("Exception 2", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_3(struct interrupt_frame *frame){ vga_textmode_print("Exception 3", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_4(struct interrupt_frame *frame){ vga_textmode_print("Exception 4", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_5(struct interrupt_frame *frame){ vga_textmode_print("Exception 5", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_6(struct interrupt_frame *frame){ vga_textmode_print("Exception 6", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_7(struct interrupt_frame *frame){ vga_textmode_print("Exception 7", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_8(struct interrupt_frame *frame){ vga_textmode_print("Exception 8", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_9(struct interrupt_frame *frame){ vga_textmode_print("Exception 9", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_10(struct interrupt_frame *frame){ vga_textmode_print("Exception 10", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_11(struct interrupt_frame *frame){ vga_textmode_print("Exception 11", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_12(struct interrupt_frame *frame){ vga_textmode_print("Exception 12", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_13(struct interrupt_frame *frame){ vga_textmode_print("Exception 13", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_14(struct interrupt_frame *frame){ vga_textmode_print("Exception 14", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_15(struct interrupt_frame *frame){ vga_textmode_print("Exception 15", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_16(struct interrupt_frame *frame){ vga_textmode_print("Exception 16", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_17(struct interrupt_frame *frame){ vga_textmode_print("Exception 17", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_18(struct interrupt_frame *frame){ vga_textmode_print("Exception 18", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_19(struct interrupt_frame *frame){ vga_textmode_print("Exception 19", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_20(struct interrupt_frame *frame){ vga_textmode_print("Exception 20", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_21(struct interrupt_frame *frame){ vga_textmode_print("Exception 21", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_22(struct interrupt_frame *frame){ vga_textmode_print("Exception 22", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_23(struct interrupt_frame *frame){ vga_textmode_print("Exception 23", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_24(struct interrupt_frame *frame){ vga_textmode_print("Exception 24", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_25(struct interrupt_frame *frame){ vga_textmode_print("Exception 25", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_26(struct interrupt_frame *frame){ vga_textmode_print("Exception 26", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_27(struct interrupt_frame *frame){ vga_textmode_print("Exception 27", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_28(struct interrupt_frame *frame){ vga_textmode_print("Exception 28", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_29(struct interrupt_frame *frame){ vga_textmode_print("Exception 29", 0x7, 80 * 2); abort(); } 
__attribute__ ((interrupt)) void handle_ex_30(struct interrupt_frame *frame){ vga_textmode_print("Exception 30", 0x7, 80 * 2); abort(); }
__attribute__ ((interrupt)) void handle_ex_31(struct interrupt_frame *frame){ vga_textmode_print("Exception 31", 0x7, 80 * 2); abort(); } 

