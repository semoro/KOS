 /*fun print(s: CharArray, p: Byte) {
     var i = 0
     for(c in s){
        xpc(c.toByte(), 0x7, (p + i++).toByte())
     }
 }
 */
 
 fun kernelMain() {
     var i = 0;
     xpc('H'.toByte(), 0x7, i++)
     xpc('e'.toByte(), 0x7, i++)
     xpc('l'.toByte(), 0x7, i++)
     xpc('l'.toByte(), 0x7, i++)
     xpc('o'.toByte(), 0x7, i++)
     xpc(' '.toByte(), 0x7, i++)
     xpc('W'.toByte(), 0x7, i++)
     xpc('o'.toByte(), 0x7, i++)
     xpc('r'.toByte(), 0x7, i++)
     xpc('l'.toByte(), 0x7, i++)
     xpc('d'.toByte(), 0x7, i++)
     xpc('!'.toByte(), 0x7, i++)
     while(true){}
 }
 
 @SymbolName("xpc")
 external fun xpc(c: Byte, attr: Byte, pos: Int)
