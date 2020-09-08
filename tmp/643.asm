nasm -fbin Main.asm -o LongModeDirectly         ; The main file's name should be Main.asm
    qemu-system-x86_64 -hda LongModeDirectly        ; The secondary file's name should be LongModeDirectly.asm and should be in the same directory
