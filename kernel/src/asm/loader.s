.code32
.text
.global loader
# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map

.set MULTIBOOT_VIDEO_MODE,  0x00000004


.set FLAGS,    ALIGN | MEMINFO | MULTIBOOT_VIDEO_MODE  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a multiboot header that marks the program as a kernel. These are magic
# values that are documented in the multiboot standard. The bootloader will
# search for this signature in the first 8 KiB of the kernel file, aligned at a
# 32-bit boundary. The signature is in its own section so the header can be
# forced to be within the first 8 KiB of the kernel file.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.skip 20
.long 0
.long 1024
.long 768
.long 24

# The multiboot standard does not define the value of the stack pointer register
# (esp) and it is up to the kernel to provide a stack. This allocates room for a
# small stack by creating a symbol at the bottom of it, then allocating 16384
# bytes for it, and finally creating a symbol at the top. The stack grows
# downwards on x86. The stack is in its own section so it can be marked nobits,
# which means the kernel file is smaller because it does not contain an
# uninitialized stack. The stack on x86 must be 16-byte aligned according to the
# System V ABI standard and de-facto extensions. The compiler will assume the
# stack is properly aligned and failure to align the stack will result in
# undefined behavior.
.section .bss

.global idt_first_entry
.type idt_first_entry, @common

multiboot_info_ptr:
.skip 4

idt_first_entry:
.skip 16 * 256



.align 16
stack_bottom:
.skip 65536 # 64 KiB
stack_top:

free_space_start:

.global free_space_start
# The linker script specifies _start as the entry point to the kernel and the
# bootloader will jump to this position once the kernel has been loaded. It
# doesn't make sense to return from this function as the bootloader is gone.

.section .rodata
.align 16
GDT64:                           # Global Descriptor Table (64-bit).
#.equ Null, $ - $GDT64         # The null descriptor.
    .short 0                         # Limit (low).
    .short 0                         # Base (low).
    .byte 0                         # Base (middle)
    .byte 0                         # Access.
    .byte 0                         # Granularity.
    .byte 0                         # Base (high).
#.equ Code, $ - $GDT64         # The code descriptor.
    .short 0xFFFF                       # Limit (low).
    .short 0                         # Base (low).
    .byte 0                         # Base (middle)
    .byte 0b10011010                 # Access (exec/read).
    .byte 0b10101111                 # Granularity.
    .byte 0                         # Base (high).
#.equ Data, $ - $GDT64         # The data descriptor.
    .short 0                         # Limit (low).
    .short 0                         # Base (low).
    .byte 0                         # Base (middle)
    .byte 0b10010010                 # Access (read/write).
    .byte 0b00000000                 # Granularity.
    .byte 0                         # Base (high).
GDTPointer:                    # The GDT-pointer.
    .short (GDTPointer - GDT64 - 1)             # Limit.
    .quad GDT64                     # Base.


.section .text
.global abort
.type abort, @function

.global _start
.type _start, @function


CheckIsLongModeSupported:
.code32
        mov  $0x80000000, %eax    
        cpuid                  
        cmp $0x80000001, %eax    
        jb NoLongMode     
        
        mov  $0x80000001, %eax  
        cpuid                 
        testl $(1 << 29), %edx 
        jz NoLongMode
        ret

NoLongMode: 
        cli
1:	hlt
	jmp 1b
	
	
.text

.code32
_start:
	# The bootloader has loaded us into 32-bit protected mode on a x86
	# machine. Interrupts are disabled. Paging is disabled. The processor
	# state is as defined in the multiboot standard. The kernel has full
	# control of the CPU. The kernel can only make use of hardware features
	# and any code it provides as part of itself. There's no printf
	# function, unless the kernel provides its own <stdio.h> header and a
	# printf implementation. There are no security restrictions, no
	# safeguards, no debugging mechanisms, only what the kernel provides
	# itself. It has absolute and complete power over the
	# machine.
	mov %ebx, (multiboot_info_ptr)

	# To set up a stack, we set the esp register to point to the top of our
	# stack (as it grows downwards on x86 systems). This is necessarily done
	# in assembly as languages such as C cannot function without a stack.
	mov $stack_top, %esp

	# This is a good place to initialize crucial processor state before the
	# high-level kernel is entered. It's best to minimize the early
	# environment where crucial features are offline. Note that the
	# processor is not fully initialized yet: Features such as floating
	# point instructions and instruction set extensions are not initialized
	# yet. The GDT should be loaded here. Paging should be enabled here.
	# C++ features such as global constructors and exceptions will require
	# runtime support to work as well.

	# Enter the high-level kernel. The ABI requires the stack is 16-byte
	# aligned at the time of the call instruction (which afterwards pushes
	# the return pointer of size 4 bytes). The stack was originally 16-byte
	# aligned above and we've since pushed a multiple of 16 bytes to the
	# stack since (pushed 0 bytes so far) and the alignment is thus
	# preserved and the call is well defined.
        call CheckIsLongModeSupported
	
	mov %cr0, %eax                                   
        and $0b01111111111111111111111111111111, %eax   
        mov %eax, %cr0 
	
        mov $0x1000, %edi     # Set the destination index to 0x1000.
        mov  %edi, %cr3       # Set control register 3 to the destination index.
        xor %eax, %eax       # Nullify the A-register.
        mov $4096, %ecx       # Set the C-register to 4096.
        rep stos %eax,%es:(%edi)          # Clear the memory.
        mov %cr3, %edi        # Set the destination index to control register 3.
	movl   $0x2003,(%edi)
	
	add    $0x1000,%edi
	
        movl   $0x3003,(%edi)
        add    $0x1000,%edi
        
        movl   $0x4003,(%edi)
        movl   $0x5003,8(%edi)
        add    $0x1000,%edi
        
       
        mov    $0x3,%ebx
        mov    $0x400,%ecx


SetEntry:
        mov    %ebx,(%edi)
        add    $0x1000,%ebx
        add    $0x8,%edi
        loop   SetEntry

        
        
        mov    %cr4,%eax
        or     $0x20,%eax
        mov    %eax,%cr4

        mov    $0xC0000080,%ecx
        rdmsr  
        or     $(1 << 8),%eax
        wrmsr 

        mov    %cr0,%eax
        or     $(1 << 31),%eax
        mov    %eax,%cr0


Pre64:
        lgdt  GDTPointer
        ljmp  $0x0008, $Realm64


Realm64:
        .code64
        cli    
        mov    $0x10,%ax
        mov    %eax,%ds
        mov    %eax,%es
        mov    %eax,%fs
        mov    %eax,%gs
        mov    %eax,%ss
	call EnableSSE
	
	call "kfun:kernelMain()"

	# If the system has nothing more to do, put the computer into an
	# infinite loop. To do that:
	# 1) Disable interrupts with cli (clear interrupt enable in eflags).
	#    They are already disabled by the bootloader, so this is not needed.
	#    Mind that you might later enable interrupts and return from
	#    kernel_main (which is sort of nonsensical to do).
	# 2) Wait for the next interrupt to arrive with hlt (halt instruction).
	#    Since they are disabled, this will lock up the computer.
	# 3) Jump to the hlt instruction if it ever wakes up due to a
	#    non-maskable interrupt occurring or due to system management mode.
	
EnableSSE: 
.code32
                                #now enable SSE and the like
        movl %cr0, %eax 
        and $0xFFFB, %ax		#clear coprocessor emulation CR0.EM
        or $0x2, %ax	        #set coprocessor monitoring  CR0.MP
        movl %eax, %cr0
        movl %cr4, %eax
        or $(3 << 9), %ax		#set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
        movl %eax, %cr4
        ret
abort:
	cli
1:	hlt
	jmp 1b

# Set the size of the _start symbol to the current location '.' minus its start.
# This is useful when debugging or when you implement call tracing.
.size _start, . - _start
