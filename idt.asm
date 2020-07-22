extern _idt
idt_desc:
	dw 4095
	dq _idt
%macro PUSHALL 0
push dx
push ax
push cx
push di
push si
push r11
push r10
push r9
push r8 
%endmacro
%macro POPALL 0
pop r8
pop r9
pop r10
pop r11
pop si
pop di
pop cx
pop ax
pop dx
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
