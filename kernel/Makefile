VPATH = build:src/c:src/kotlin:src/asm

KOTLIN_SOURCES = main.kt
ASM_SOURCES = loader.s
C_SOURCES = vga/vga_out.c
OBJECTS = $(C_SOURCES:.c=.bc.o) $(ASM_SOURCES:.s=.s.o) $(KOTLIN_SOURCES:.kt=.kt.bc.o)

LLC_FLAGS = -filetype=obj -march=x86 -code-model=kernel
CLANG_FLAGS = -S -emit-llvm
KONANC_FLAGS = -nolink
LD_FLAGS = -m elf_i386 -T linker.ld 

.PHONY: all clean
all: kernel.bin

clean: 
	rm build -r

kernel.bin: $(OBJECTS)
	ld -o build/kernel.bin $(addprefix build/,$^) $(LD_FLAGS)

%.bc: %.c
	mkdir -p build/$(dir $@) && clang $< -o build/$@ $(CLANG_FLAGS)
%.kt.bc: %.kt
	mkdir -p build/$(dir $@) && konanc $< -o build/$@ $(KONANC_FLAGS)
%.bc.o: %.bc
	mkdir -p build/$(dir $@) && llc build/$< -o build/$@ $(LLC_FLAGS)
%.s.o: %.s
	as --32 $< -o build/$@
