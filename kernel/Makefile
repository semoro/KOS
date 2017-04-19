VPATH = build:src/c:src/kotlin:src/asm

KOTLIN_RUNTIME_SOURCES = $(wildcard src/kotlin/runtime/*.kt) $(wildcard src/kotlin/runtime/kotlin/*.kt) $(wildcard src/kotlin/runtime/konan/*.kt) $(wildcard src/kotlin/runtime/konan/internal/*.kt)
KOTLIN_SOURCES = main.kt

ASM_SOURCES = loader.s
C_SOURCES = vga/vga_textmode.c vga/utils.c runtime/static_alloc.c
OBJECTS = $(C_SOURCES:.c=.bc.o) $(ASM_SOURCES:.s=.s.o) $(KOTLIN_SOURCES:.kt=.kt.bc.o)

LLC_FLAGS = -filetype=obj -march=x86 -code-model=kernel
CLANG_FLAGS = -S -emit-llvm 

KONANC_FLAGS = -nolink

GCC_PREFIX = /usr/lib/gcc/x86_64-linux-gnu/4.8
#GCC_OBJ = crtbegin.o crtend.o libatomic.a libgcc.a libgcc_eh.a libstdc++.a 
GCC_LIBS = $(addprefix ${GCC_PREFIX}/,${GCC_OBJ}) 

LD_IGNORE_UNRESOLVED = 
LD_FLAGS = -melf_i386 --unresolved-symbols=ignore-all -T linker.ld --defsym=_Z19RuntimeAssertFailedPKcS0_=AssertionFailedPX

.PHONY: all clean
all: kernel.bin

clean: 
	rm build -rf
# runtime.bc.o stdlib.kt.bc.o 
kernel.bin: $(OBJECTS) 
	ld $(LD_FLAGS) -o build/kernel.bin ${GCC_LIBS} $(addprefix build/,$^)
	

%.bc: %.c
	mkdir -p build/$(dir $@) && clang $< -o build/$@ $(CLANG_FLAGS)
%.kt.bc: %.kt
	mkdir -p build/$(dir $@) && konanc $< -o build/$@ $(KONANC_FLAGS)
%.bc.o: %.bc
	mkdir -p build/$(dir $@) && llc build/$< -o build/$@ $(LLC_FLAGS)
%.s.o: %.s
	as --32 $< -o build/$@

