vm-gdb: install-kernel umount
	qemu-system-x86_64 -drive format=raw,file=build/disk.img -s -S

vm: install-kernel umount
	qemu-system-x86_64 -drive format=raw,file=build/disk.img

umount: lodel-disk-img
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

lodel-disk-img: umount-disk-img
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

verify-kernel:
	grub-file --is-x86-multiboot build/kernel.bin
install-kernel: kernel.bin verify-kernel mount-disk-img 
	cp grub /tmp/mnt/disk_img/boot -r \
	&& cp build/kernel.bin /tmp/mnt/disk_img/boot/ktkernel.bin \
	&& sync
	
kernel.bin: loader.o main.bc.o xpc.bc.o
	ld -m elf_i386 -T linker.ld -o build/$@ build/loader.o build/main.bc.o build/xpc.bc.o 

loader.o: 
	as --32 -o build/loader.o loader/loader.s

main.bc:
	konanc kernel/main.kt -nolink -o build/main.bc 
main.bc.o: main.bc
	llc build/main.bc -o build/main.bc.o -filetype=obj -march=x86 -code-model=kernel
xpc.bc: 
	clang -S -emit-llvm kernel/c/vga_out.c -o build/xpc.bc
xpc.bc.o: xpc.bc
	llc build/$^ -o build/$@ -filetype=obj -march=x86 -code-model=kernel
runtime.bc.o: 
	llc /fastspace/kotlin-native/dist/lib/host/runtime.bc -o build/$@ -filetype=obj -march=x86 -code-model=kernel
