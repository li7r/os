#pragma once
void outb(unsigned short port,unsigned char val){
	asm volatile ("outb %0,%1": :"a"(val),"Nd"(port));
}
unsigned char inb(unsigned short port){
	unsigned char returnval;
	asm volatile ("inb %1, %0":"=a"(returnval):"Nd"(port));
	return returnval;
}
static inline void io_wait(void)
{
    /* TODO: This is probably fragile. */
    asm volatile ( "jmp 1f\n\t"
                   "1:jmp 2f\n\t"
                   "2:" );
}
