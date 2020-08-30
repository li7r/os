#include "cursor.cpp"
#include "term.cpp"
#include "idt.cpp"
#include "gui.cpp"
extern "C" void kmain(){
asm("cli");
//enable_cursor(0,15);
clear();
init_idt();
if(false){
write_regs(g_320x200x256);
for(uint32_t y = 0; y < 200; y++)
        for(uint32_t x = 0; x < 320; x++)
            PutPixel(x, y,0x01);
}
while(1);
}
