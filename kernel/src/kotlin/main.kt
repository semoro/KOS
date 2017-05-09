import konan.SymbolName
import kotlinx.cinterop.*


fun kernelMain() {
    
    setupIDT();
    initializeMemoryAllocation();
    
    val runtimeState = initRuntime();
    if(runtimeState == nativeNullPtr)
        abort()
        
    setupPAE()
    prepareFont()
    
    print("Hello, world!", 0x7, 0)
    
    for(i in 0..10)
        print("Meow!", 0x7, 0)
        
    fillScreenRect(0, 0, 1024, 768, 0xFFFFFF)
    drawImage(getResourcePointerById(1), 1024 - 100, 0, 100, 100)
    
    drawText("Hello, world!", 10, 10, 0x0)
    

    hangPlayinWithNumbers()
    
}

fun fillScreenRect(xRange: IntRange, yRange: IntRange, r: Byte, g: Byte, b: Byte) {
    for(x in xRange)
        for(y in yRange)
            screenWrite(x.toShort(), y.toShort(), r, g, b)
}

val fbAddr = 0x400000L
val fbWidth = 1024

fun fillScreenRect(sx: Int, sy: Int, w: Int, h: Int, rgb: Int) {
    for(y in sy until (sy + h))
        memset(fbAddr + sx * 3 + y * fbWidth * 3, rgb, (w * 3).toLong())
}

fun drawImage(dataPtr: NativePtr, x: Int, y: Int, width: Int, height: Int) {
    val dataAddr = dataPtr.toLong()
    for(iy in 0 until height) {
        memcpy(fbAddr + x * 3 + (y + iy) * fbWidth * 3, dataAddr + iy * width * 3, width * 3L)
    }
}

fun setupPAE() {
    val pml4tPtr = interpretCPointer<PAEEntry>(alignedAlloc(PAEEntry.size, 0x1000))!!.apply { pointed.clear() }
    val pdptPtr = interpretCPointer<PAEEntry>(alignedAlloc(PAEEntry.size, 0x1000))!!.apply { pointed.clear() }
    val pdtPtr = interpretCPointer<PAEEntry>(alignedAlloc(PAEEntry.size, 0x1000))!!.apply { pointed.clear() }
    
    
    
    fun createPT(base: Long): CPointer<PAEEntry> {
        val ptPtr = interpretCPointer<PAEEntry>(alignedAlloc(PAEEntry.size, 0x1000))!!.apply { pointed.clear() }
        var i = 0
        while (i < 512) {
            ptPtr.pointed[i] = base + (i * 0x1000) + 3
            i++
        }
        return ptPtr
    }
    
    
    val pt1Ptr = createPT(0x1000 * 0)
    val pt2Ptr = createPT(0x1000 * 512)
    
   
    
    
    pml4tPtr.pointed[0] = pdptPtr.rawValue.toLong() + 1
    pdptPtr.pointed[0] = pdtPtr.rawValue.toLong()   + 1
    pdtPtr.pointed[0] = pt1Ptr.rawValue.toLong()    + 3
    pdtPtr.pointed[1] = pt2Ptr.rawValue.toLong()    + 3
    
    val ptSPtr = createPT(0xfd000000)
    val ptS1Ptr = createPT(0xfd000000 + 0x1000 * 512)
    
    pdtPtr.pointed[2] = ptSPtr.rawValue.toLong()    + 3
    pdtPtr.pointed[3] = ptS1Ptr.rawValue.toLong()    + 3
    
   /* 
    val pdpt3Ptr = interpretCPointer<PAEEntry>(alignedAlloc(PAEEntry.size, 0x1000))!!.apply { pointed.clear() }
    val pdt3_488Ptr = interpretCPointer<PAEEntry>(alignedAlloc(PAEEntry.size, 0x1000))!!.apply { pointed.clear() }
    val ptSPtr = createPT(0xfd000000)
    val ptS1Ptr = createPT(0xfd000000 + 0x1000 * 512)
    
    
    for(i in 1..511) {
        pml4tPtr.pointed[i] = pdpt3Ptr.rawValue.toLong() + 1
    }
    
    for(i in 0..511) {
        pdpt3Ptr.pointed[i] = pdt3_488Ptr.rawValue.toLong() + 1
         pdt3_488Ptr.pointed[i] = ptSPtr.rawValue.toLong() + 3
    }
    
    pdt3_488Ptr.pointed[0] = ptSPtr.rawValue.toLong() + 3
    pdt3_488Ptr.pointed[1] = ptS1Ptr.rawValue.toLong() + 3*/
    
    setPaeTableAddress(pml4tPtr.rawValue)
}

fun hangPlayinWithNumbers() {
    var j = 0
    while(true){
        j++;
        var k = 0
        while(k++ < 10)
            vgaTextmodeWrite(' '.toByte(), 0x7, 80 + k)
        printNumber64Hex(j.toLong(), 0x7, 80)
    }
}
 
fun print(s: String, attr: Byte, pos: Int) {
    var i = 0
    while(i < s.length) {
        vgaTextmodeWrite(s[i].toByte(), attr, pos + i++)
    }
}

 
class PAEEntry(override val rawPtr: NativePtr) : CStructVar() {
    
    companion object : Type(8 * 512, 1024)
    
    fun clear() {
        var i = 0
        while (i < 512) {
            this[i] = 0
            i++
        }
    }
        
    operator fun get(i: Int): Long {
        return memberAt<LongVar>(i * 8L).value
    }

    operator fun set(i: Int, v: Long) {
        memberAt<LongVar>(i * 8L).value = v
    }
}

class FontGlyphData(override val rawPtr: NativePtr) : CStructVar() {
    
    companion object : Type(11, 0x1)
   
    val advence: Byte
        get() = memberAt<ByteVar>(11).value
}

@SymbolName("vga_textmode_write")
external fun vgaTextmodeWrite(c: Byte, attr: Byte, pos: Int)

@SymbolName("vga_textmode_print_int")
external fun printNumber(i: Int, attr: Byte, pos: Int)

@SymbolName("vga_textmode_print_ptr")
external fun printNumber64Hex(i: Long, attr: Byte, pos: Int)
 
@SymbolName("aligned_alloc")
external fun alignedAlloc(s: Long, a: Int): NativePtr
@SymbolName("malloc")
external fun malloc(s: Long): NativePtr

@SymbolName("static_alloc")
external fun staticAlloc(addr: Int): NativePtr

@SymbolName("set_pae_table_address")
external fun setPaeTableAddress(addr: NativePtr)

@SymbolName("setup_idt")
external fun setupIDT()
@SymbolName("initialize_memory_allocation")
external fun initializeMemoryAllocation()

@SymbolName("InitRuntime")
external fun initRuntime(): NativePtr


@SymbolName("abort")
external fun abort()

@SymbolName("screen_write")
external fun screenWrite(x: Short, y: Short, r: Byte, g: Byte, b: Byte)
@SymbolName("screen_write_rgb")
external fun screenWriteRGB(x: Short, y: Short, rgb: Int)

@SymbolName("get_resource_ptr_by_id")
external fun getResourcePointerById(id: Int): NativePtr

@SymbolName("get_int_at_addr")
external fun getInt(l: Long): Int

@SymbolName("memset")
external fun memset(ptr: Long, v: Int, size: Long): Long

@SymbolName("memcpy")
external fun memcpy(dst: Long, src: Long, size: Long): Long


@SymbolName("prepare_font")
external fun prepareFont()

@SymbolName("draw_text")
external fun drawText(cstr: NativePtr, x: Short, y: Short, rgb: Int)

fun drawText(text: String, x: Short, y: Short, rgb: Int) {
    return memScoped {
            val _cstr = text.cstr.getPointer(memScope).rawValue
            drawText(_cstr, x, y, rgb)
    }
}
