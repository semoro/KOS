VPATH = build:src/c:src/kotlin:src/asm

KOTLIN_RUNTIME_SOURCES = $(wildcard src/kotlin/runtime/*.kt) $(wildcard src/kotlin/runtime/kotlin/*.kt) $(wildcard src/kotlin/runtime/konan/*.kt) $(wildcard src/kotlin/runtime/konan/internal/*.kt)
KOTLIN_SOURCES = main.kt

ASM_SOURCES = loader.s
C_SOURCES = vga/vga_textmode.c vga/utils.c runtime/static_alloc.c runtime/idt.c hardware/PIC.c hardware/io.c
OBJECTS = $(C_SOURCES:.c=.bc.o) $(ASM_SOURCES:.s=.s.o) $(KOTLIN_SOURCES:.kt=.kt.bc.o)
OBJECTS_LOCATION = $(addprefix build/,${OBJECTS})

LLC_FLAGS = -filetype=obj -march=x86-64 -code-model=kernel
CLANG_FLAGS = -Isrc/c -g -S -emit-llvm 

KONANC_FLAGS = -nolink

GCC_PREFIX = /usr/lib/gcc/x86_64-linux-gnu/4.8
GCC_OBJ = crtbegin.o crtend.o libatomic.a libgcc.a libgcc_eh.a libstdc++.a 
GCC_LIBS = $(addprefix ${GCC_PREFIX}/,${GCC_OBJ}) 

LD_IGNORE_UNRESOLVED = --unresolved-symbols=ignore-all
LD_FLAGS = -melf_x86_64 -g ${LD_IGNORE_UNRESOLVED} -T linker.ld --defsym=_Z19RuntimeAssertFailedPKcS0_=AssertionFailedPX -z max-page-size=0x1000

.PHONY: all clean
all: kernel.bin

clean: 
	rm build -rf
# runtime.bc.o stdlib.kt.bc.o 
kernel.bin: $(OBJECTS) 
	ld -o build/kernel.bin runtime.bc.o stdlib.kt.bc.o ${GCC_LIBS} ${OBJECTS_LOCATION} $(LD_FLAGS)
	

%.bc: %.c
	mkdir -p build/$(dir $@) && clang $< -o build/$@ $(CLANG_FLAGS)
%.kt.bc: %.kt
	mkdir -p build/$(dir $@) && konanc $< -o build/$@ $(KONANC_FLAGS)
%.bc.o: %.bc
	mkdir -p build/$(dir $@) && llc build/$< -o build/$@ $(LLC_FLAGS)
%.s.o: %.s
	as $< -o build/$@

