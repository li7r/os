nasm -f elf64  a.asm
nasm -f elf64  b.asm
#ncopile lua here ! 
#wget https://lua.org/ftp/lua-5.4.0.tar.gz
gcc -m64 -ffreestanding -mno-red-zone -c main.cpp -o c.o 
ld --nmagic --output=kernel.bin --script=link.ld a.o b.o c.o
sudo mv kernel.bin isofiles/boot/
grub-mkrescue -o os.iso isofiles
qemu-system-x86_64 -hda os.iso
