global irq0 
global load_idt 
global irq0_handler 
extern irq0_handler
%macro PUSHALL 0
push rax
push rcx
push rdx
push r8
push r9
push r10
push r11
%endmacro
%macro POPALL 0
push r11
push r10
push r9
push r8
push rdx
push rcx
push rax
%endmacro
irq0:
  PUSHALL
  call irq0_handler
  POPALL
  iretq
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret
