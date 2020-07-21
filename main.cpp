#include "cursor.cpp"
#include "term.cpp"
//#include "idt.cpp"
extern "C" void kmain(){
asm("cli");
enable_cursor(0,15);
clear();
//idt_init();
put("a");
while(1);
}
