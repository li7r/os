extern _idt
idt_desc:
	dw 4095
	dq _idt
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
extern isr1_handler
isr1:
	PUSHALL
	call isr1_handler
	POPALL
	iretq
	GLOBAL isr1
load_idt:
	lidt[idt_desc]
	sti
	ret
	GLOBAL load_idt
