#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include "idt.h"

__attribute__ ((interrupt)) void handle_ex_0(struct interrupt_frame *frame);
__attribute__ ((interrupt)) void handle_ex_1(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_2(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_3(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_4(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_5(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_6(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_7(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_8(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_9(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_10(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_11(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_12(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_13(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_14(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_15(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_16(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_17(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_18(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_19(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_20(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_21(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_22(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_23(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_24(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_25(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_26(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_27(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_28(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_29(struct interrupt_frame *frame); 
__attribute__ ((interrupt)) void handle_ex_30(struct interrupt_frame *frame);
__attribute__ ((interrupt)) void handle_ex_31(struct interrupt_frame *frame); 


#endif
