#pragma once
#include "types.cpp"
struct IDT64 {
   uint16_t offset_1; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t ist;   
   uint8_t type_attr; // type and attributes
   uint16_t offset_2; // offset bits 16..31
   uint32_t offset_3; // offset bits 32..63
   uint32_t zero;     // reserved
};
extern IDT64 _idt[256];
extern uint64_t isr1;
extern "C" void load_idt();
void init_idt(){
	for(uint64_t t = 0;t<256;t++){
		_idt[t].zero = 0;
		_idt[t].offset_1 = (uint16_t)(((uint64_t)&isr1&0x000000000000ffff));
		_idt[t].offset_2 = (uint16_t)(((uint64_t)&isr1&0x00000000ffff0000) >> 16);
		_idt[t].offset_3 = (uint32_t)(((uint64_t)&isr1&0xffffffff00000000) >> 32);
		_idt[t].ist = 0;
		_idt[t].selector = 0x08;
		_idt[t].type_attr = 0x8e;
	}
	outb(0x21,0xfd);
	outb(0xa1,0xff);
	load_idt();

}
extern "C" void isr1_handler(){
	hex(inb(0x60));
	outb(0x20,0x20);
	outb(0xa0,0x20);
	return;
}
