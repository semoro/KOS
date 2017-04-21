vm-gdb: prepare-disk-for-run null_call_breakpoints manual_breakpoints
	qemu-system-x86_64 -drive format=raw,file=build/disk.img -m 512M -s -monitor telnet:127.0.0.1:1235,server,nowait & \
	bash -c 'konsole -e gdb -x gdbinit'
	

vm-db: prepare-disk-for-run
	qemu-system-x86_64 -drive format=raw,file=build/disk.img -m 512M -s -S
	
vm: prepare-disk-for-run
	qemu-system-x86_64 -drive format=raw,file=build/disk.img -m 512M

prepare-disk-for-run: install-kernel install-grub-config umount
umount: umount-disk-img lodel-disk-img 
umount-disk-img:
	sudo umount /tmp/mnt/disk_img || /bin/true \
	&& sync

install-grub: format-disk-img mount-disk-img
	sudo grub-install --root-directory=/tmp/mnt/disk_img --no-floppy --modules="normal part_msdos ext2 multiboot" /dev/loop0

mount-disk-img: losetup-disk-img
	mkdir -p /tmp/mnt/disk_img \
	&& sudo mount /dev/loop1 /tmp/mnt/disk_img || /bin/true \
	&& sudo chown -R 1000:1000 /tmp/mnt/disk_img

format-disk-img: part-disk-img losetup-disk-img
	sudo mke2fs /dev/loop1 \
	&& sync

losetup-disk-img:
	sudo losetup /dev/loop0 build/disk.img \
	&& sudo losetup /dev/loop1 build/disk.img -o 1048576

lodel-disk-img: 
	sudo losetup -d /dev/loop0 || /bin/true \
	&& sudo losetup -d /dev/loop1 || /bin/true

part-disk-img: create-disk-img
	parted -s build/disk.img \
	mklabel msdos \
	mkpart primary 2048s 100% \
	set 1 boot on \
	print list

create-disk-img: 
	dd if=/dev/zero of=build/disk.img bs=512 count=131072

install-grub-config: grub/grub.cfg
	cp grub /tmp/mnt/disk_img/boot -r 
verify-kernel:
	grub-file --is-x86-multiboot build/kernel.bin
install-kernel: kernel.bin verify-kernel mount-disk-img 
	cp build/kernel.bin /tmp/mnt/disk_img/boot/ktkernel.bin \
	&& sync
.PHONY: vm-gdb vm prepare-disk-for-run umount umount-disk-img install-grub mount-disk-img format-disk-img losetup-disk-img lodel-disk-img part-disk-img create-disk-img install-grub-config verify-kernel install-kernel kernel/build/kernel.bin

VPATH = build

kernel.lst: kernel.bin
	nm build/kernel.bin > build/kernel.lst
	
null_call_breakpoints: kernel.bin
	objdump -d kernel/build/kernel.bin | grep "callq  0" | awk "{print \$$1}" | sed -e "s/\([a-f0-9]*\):/hbreak *0x\1/g" > build/$@
	
manual_breakpoints: kernel.lst
	python setBreakpoints.py > build/$@

kernel.bin: kernel/build/kernel.bin
	cp kernel/build/kernel.bin build/

kernel/build/kernel.bin:
	$(MAKE) -C kernel clean all

#kernel.bin: loader.o main.bc.o xpc.bc.o
# 	ld -m elf_i386 -T linker.ld -o build/$@ build/loader.o build/main.bc.o build/xpc.bc.o 
# 
# loader.o: 
# 	as --32 -o build/loader.o loader/loader.s
# 
# main.bc:
# 	konanc kernel/main.kt -nolink -o build/main.bc 
# main.bc.o: main.bc
# 	llc build/main.bc -o build/main.bc.o -filetype=obj -march=x86 -code-model=kernel
# xpc.bc: 
# 	clang -S -emit-llvm kernel/c/vga_out.c -o build/xpc.bc
# xpc.bc.o: xpc.bc
# 	llc build/$^ -o build/$@ -filetype=obj -march=x86 -code-model=kernel
# runtime.bc.o: 
# 	llc /fastspace/kotlin-native/dist/lib/host/runtime.bc -o build/$@ -filetype=obj -march=x86 -code-model=kernel
