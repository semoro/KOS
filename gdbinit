 set arch i386:x86-64
 target remote :1234
 set pagination off
 dir $cwd/kernel
 dir /fastspace/kotlin-native/runtime/
 dir /fastspace/gcc-4.8.5/
 
 symbol-file build/kernel.bin
 source build/manual_breakpoints
 source build/null_call_breakpoints
 source named_breakpoints
 set pagination on
 source /fastspace/gdb-gui/gdb-gui.py
 gui source
 set substitute-path '../../../../../../src/libstdc++-v3' '/fastspace/gcc-4.8.5/libstdc++-v3/'
 set substitute-path '/src/libstdc++-v3' '/fastspace/gcc-4.8.5/libstdc++-v3/'
