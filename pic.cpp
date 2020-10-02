#include "io.cpp"
#include "term.cpp"
#define PIC_MASTER_CMD 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD 0xA0
#define PIC_SLAVE_DATA 0xA1
#define PIC1_CMD                    0x20
#define PIC1_DATA                   0x21
#define PIC2_CMD                    0xA0
#define PIC2_DATA                   0xA1
#define PIC_READ_IRR                0x0a    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR                0x0b    /* OCW3 irq service next CMD read */
#define PIC_CMD_EOI 0x20
#define PIC1_REG_COMMAND 0x20
#define PIC1_REG_STATUS 0x20
#define PIC1_REG_DATA 0x21
#define PIC1_REG_IMR 0x21

// PIC 2 register port addresses
#define PIC2_REG_COMMAND 0xA0
#define PIC2_REG_STATUS 0xA0
#define PIC2_REG_DATA 0xA1
#define PIC2_REG_IMR 0xA1

//-----------------------------------------------
// Initialization Command Bit Masks
//-----------------------------------------------

// Initialization Control Word 1 bit masks
#define PIC_ICW1_MASK_IC4 0x1 //00000001
#define PIC_ICW1_MASK_SNGL 0x2 //00000010
#define PIC_ICW1_MASK_ADI 0x4 //00000100
#define PIC_ICW1_MASK_LTIM 0x8 //00001000
#define PIC_ICW1_MASK_INIT 0x10 //00010000

// Initialization Control Words 2 and 3 do not require bit masks

// Initialization Control Word 4 bit masks
#define PIC_ICW4_MASK_UPM 0x1 //00000001
#define PIC_ICW4_MASK_AEOI 0x2 //00000010
#define PIC_ICW4_MASK_MS 0x4 //00000100
#define PIC_ICW4_MASK_BUF 0x8 //00001000
#define PIC_ICW4_MASK_SFNM 0x10 //00010000

//-----------------------------------------------
// Initialization Command 1 control bits
//-----------------------------------------------

#define PIC_ICW1_IC4_EXPECT 1 //1
#define PIC_ICW1_IC4_NO 0 //0
#define PIC_ICW1_SNGL_YES 2 //10
#define PIC_ICW1_SNGL_NO 0 //00
#define PIC_ICW1_ADI_CALLINTERVAL4 4 //100
#define PIC_ICW1_ADI_CALLINTERVAL8 0 //000
#define PIC_ICW1_LTIM_LEVELTRIGGERED 8 //1000
#define PIC_ICW1_LTIM_EDGETRIGGERED 0 //0000
#define PIC_ICW1_INIT_YES 0x10 //10000
#define PIC_ICW1_INIT_NO 0 //00000

//-----------------------------------------------
// Initialization Command 4 control bits
//-----------------------------------------------

#define PIC_ICW4_UPM_86MODE 1 //1
#define PIC_ICW4_UPM_MCSMODE 0 //0
#define PIC_ICW4_AEOI_AUTOEOI 2 //10
#define PIC_ICW4_AEOI_NOAUTOEOI 0 //0
#define PIC_ICW4_MS_BUFFERMASTER 4 //100
#define PIC_ICW4_MS_BUFFERSLAVE 0 //0
#define PIC_ICW4_BUF_MODEYES 8 //1000
#define PIC_ICW4_BUF_MODENO 0 //0
#define PIC_ICW4_SFNM_NESTEDMODE 0x10 //10000
#define PIC_ICW4_SFNM_NOTNESTED 0 //a binary 2
void pic_init()
{
	

	/* First step is to save current masks, set by BIOS */
	put("Beginning initialization\n");
	/* set up cascading mode */
	outb(PIC_MASTER_CMD, 0x10 + 0x01);
	outb(PIC_SLAVE_CMD,  0x10 + 0x01);
	/* Setup master's vector offset */
	outb(PIC_MASTER_DATA, 0x20);
	/* Tell the slave its vector offset */
	outb(PIC_SLAVE_DATA, 0x28);
	/* Tell the master that he has a slave */
	outb(PIC_MASTER_DATA, 4);
	outb(PIC_SLAVE_DATA, 2);
	/* Enabled 8086 mode */
	outb(PIC_MASTER_DATA, 0x01);
	outb(PIC_SLAVE_DATA, 0x01);

	put("Resetting masks\n");
	outb(PIC_MASTER_DATA, 0);
	outb(PIC_SLAVE_DATA, 0);
	put("Init done.\n");
}

void pic_send_eoi(uint8_t irq)
{
	if(irq >= 8)
		outb(PIC_SLAVE_CMD, PIC_CMD_EOI);
	outb(PIC_MASTER_CMD, PIC_CMD_EOI);
}

 
/* Helper func */
static uint16_t __pic_get_irq_reg(int ocw3)
{
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outb(PIC1_CMD, ocw3);
    outb(PIC2_CMD, ocw3);
    return (inb(PIC2_CMD) << 8) | inb(PIC1_CMD);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
uint16_t pic_get_irr(void)
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
uint16_t pic_get_isr(void)
{
    return __pic_get_irq_reg(PIC_READ_ISR);
}
