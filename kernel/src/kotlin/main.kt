import konan.SymbolName
import kotlinx.cinterop.*


fun kernelMain() {
    setupIDT();
    initializeMemoryAllocation();
    print("Hello, world!", 0x7, 0)

    
    for(i in 0..10)
        print("Meow!", 0x7, 0)
    hangPlayinWithNumbers()
    
}

fun hangPlayinWithNumbers() {
    var j = 0
    while(true){
        j++;
        var k = 0
        while(k++ < 10)
            vgaTextmodeWrite(' '.toByte(), 0x7, 80 + k)
        printNumber(j, 80 + 10)
    }
}
 
fun print(s: String, attr: Byte, pos: Int) {
    var i = 0
    while(i < s.length) {
        vgaTextmodeWrite(s[i].toByte(), attr, pos + i++)
    }
}

 
@SymbolName("vga_textmode_write")
external fun vgaTextmodeWrite(c: Byte, attr: Byte, pos: Int)

@SymbolName("vga_textmode_print_int")
external fun printNumber(i: Int, pos: Int)
 
@SymbolName("malloc")
external fun malloc(s: Int): Int

@SymbolName("static_alloc")
external fun staticAlloc(addr: Int): NativePtr


@SymbolName("setup_idt")
external fun setupIDT()
@SymbolName("initialize_memory_allocation")
external fun initializeMemoryAllocation()
