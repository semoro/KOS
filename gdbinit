 set arch i386:x86-64
 target remote :1234
 set pagination off
 dir $cwd/kernel
 symbol-file build/kernel.bin
 source build/manual_breakpoints
 source build/null_call_breakpoints
 source named_breakpoints
 set pagination on
 layout split
