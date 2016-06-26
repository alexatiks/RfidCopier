#include <avr/io.h>

#define RESET_1 PORTA |= _BV(PA1)
#define RESET_0 PORTA &= ~_BV(PA1)
#define CS_1 PORTA |= _BV(PA5)
#define CS_0 PORTA &= ~_BV(PA5)
#define RS_1 PORTA |= _BV(PA4)
#define RS_0 PORTA &= ~_BV(PA4)
#define WR_1 PORTA |= _BV(PA3)
#define WR_0 PORTA &= ~_BV(PA3)
#define RD_1 PORTA |= _BV(PA2)
#define RD_0 PORTA &= ~_BV(PA2)
#define LED_ON PORTA |= _BV(PA6)
#define LED_OFF PORTA &= ~_BV(PA6)


typedef unsigned char uchar;
typedef unsigned int uint;
#define WR_DATA_L PORTB
#define WR_DATA_H PORTC

uchar Verdana_font_11[] = {
	0,   // format
	11,   // fontHeight
	9,   // ascent
	33,   // from
	95,   // count
	59,   // totalWidth/8
	0x00,0x01,0x00,0x04,0x00,0x0B,0x00,0x10,0x00,0x1A,0x00,0x21,0x00,0x22,0x00,0x25,0x00,0x28,0x00,0x2D,0x00,0x34,0x00,0x36,0x00,0x39,0x00,0x3A,0x00,0x3F,0x00,0x44,0x00,0x49,0x00,0x4E,0x00,0x53,0x00,0x59,0x00,0x5E,0x00,0x63,0x00,0x68,0x00,0x6D,0x00,0x72,0x00,0x73,0x00,0x75,0x00,0x7B,0x00,0x82,0x00,0x88,0x00,0x8C,0x00,0x94,0x00,0x9A,0x00,0xA0,0x00,0xA7,0x00,0xAE,0x00,0xB3,0x00,0xB8,0x00,0xBF,0x00,0xC5,0x00,0xC8,0x00,0xCC,0x00,0xD2,0x00,0xD7,0x00,0xDE,0x00,0xE4,0x00,0xEB,0x00,0xF0,0x00,0xF7,0x00,0xFD,0x01,0x03,0x01,0x0A,0x01,0x10,0x01,0x16,0x01,0x1F,0x01,0x25,0x01,0x2C,0x01,0x32,0x01,0x35,0x01,0x3A,0x01,0x3D,0x01,0x44,0x01,0x4B,0x01,0x4D,0x01,0x52,0x01,0x57,0x01,0x5C,0x01,0x61,0x01,0x66,0x01,0x6A,0x01,0x6F,0x01,0x74,0x01,0x75,0x01,0x78,0x01,0x7D,0x01,0x7E,0x01,0x87,0x01,0x8C,0x01,0x91,0x01,0x96,0x01,0x9B,0x01,0x9F,0x01,0xA3,0x01,0xA7,0x01,0xAC,0x01,0xB1,0x01,0xB8,0x01,0xBD,0x01,0xC2,0x01,0xC6,0x01,0xCB,0x01,0xCC,0x01,0xD1,0x01,0xD8,0x01,0xD8,    // Col ends
	0x50,0x04,0x00,0x00,0x4C,0x20,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x38,0x00,0x10,0x20,0x00,0x80,0xC1,0x09,0x84,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x00,    // Line 0
	0xD1,0x44,0x62,0x18,0x52,0xA8,0x00,0x02,0xE2,0x39,0xC1,0x7C,0xDF,0x73,0x80,0x00,0x00,0xE3,0xE3,0x3C,0x3D,0xF3,0xFF,0x3D,0x0F,0x78,0x61,0x8F,0x13,0x9E,0x39,0xE3,0xDF,0xE1,0x86,0x23,0x0C,0x1F,0xE4,0x08,0x80,0x08,0x20,0x00,0x81,0x01,0x00,0x84,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x92,0x00,    // Line 1
	0xD1,0x4F,0x92,0x24,0x52,0x70,0x80,0x05,0x1E,0x46,0x23,0x41,0x01,0x8C,0x40,0x00,0x00,0x14,0x13,0x22,0x43,0x0A,0x10,0x43,0x0A,0x18,0xA1,0x8F,0x14,0x51,0x45,0x14,0x22,0x21,0x86,0x23,0x0A,0x20,0x62,0x09,0x40,0x00,0x20,0x00,0x81,0x01,0x00,0x84,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x92,0x00,    // Line 2
	0x87,0xF4,0x94,0x24,0x21,0xA8,0x80,0x05,0x12,0x04,0x25,0x42,0x02,0x8C,0x68,0x60,0x30,0x19,0xD4,0xA2,0x81,0x06,0x10,0x81,0x0A,0x19,0x21,0x56,0x98,0x31,0x83,0x14,0x02,0x21,0x85,0x54,0x91,0x40,0xA2,0x0A,0x20,0x03,0xBC,0xE7,0xBB,0xDF,0xEB,0x8F,0xDD,0xE7,0x79,0xF6,0xFF,0x18,0xC9,0x8C,0x7C,0x92,0x00,    // Line 3
	0x82,0x94,0x64,0x19,0x21,0x20,0x80,0x09,0x12,0x08,0xC9,0x7B,0xC2,0x74,0x69,0x9F,0xCC,0x2A,0x54,0xBE,0x81,0x07,0xFE,0x81,0xFA,0x1A,0x21,0x56,0x98,0x31,0x83,0x13,0x02,0x21,0x49,0x54,0x60,0x81,0x21,0x0C,0x10,0x00,0x63,0x18,0xC5,0x23,0x19,0x96,0x23,0x18,0xC6,0x39,0x09,0x18,0xC9,0x52,0x84,0x92,0x31,    // Line 4
	0x82,0x8E,0x09,0xA5,0x21,0x07,0xF3,0x89,0x12,0x10,0x31,0x06,0x24,0x8B,0xC6,0x00,0x03,0x4A,0x54,0xA1,0x81,0x06,0x10,0x8F,0x0A,0x1E,0x21,0x26,0x58,0x3E,0x83,0xE0,0xC2,0x21,0x49,0x54,0x60,0x82,0x21,0x08,0x00,0x03,0xE3,0x08,0xFD,0x23,0x19,0xA6,0x23,0x18,0xC6,0x31,0x89,0x15,0x55,0x22,0x8B,0x11,0xC9,    // Line 5
	0x8F,0xC5,0x0A,0x62,0x21,0x00,0x80,0x11,0x12,0x20,0x3F,0x86,0x24,0x88,0x41,0x9F,0xCC,0x4A,0x5F,0xE1,0x81,0x06,0x10,0x83,0x0A,0x19,0x21,0x26,0x58,0x30,0x83,0x20,0x22,0x21,0x49,0x54,0x90,0x84,0x20,0x88,0x00,0x04,0x63,0x08,0xC1,0x23,0x19,0xE6,0x23,0x18,0xC6,0x30,0x69,0x15,0x55,0x22,0x90,0x92,0x46,    // Line 6
	0x05,0x05,0x12,0x63,0x21,0x00,0x84,0x51,0x12,0x42,0x21,0x46,0x28,0x88,0xA8,0x60,0x30,0x09,0xA8,0x61,0x43,0x0A,0x10,0x43,0x0A,0x18,0xA1,0x06,0x34,0x50,0x45,0x14,0x22,0x21,0x30,0x89,0x08,0x88,0x20,0x88,0x00,0x04,0x63,0x18,0xC5,0x23,0x19,0x96,0x23,0x18,0xC6,0x30,0x29,0x12,0x22,0x51,0x20,0x92,0x00,    // Line 7
	0x85,0x1E,0x11,0x9C,0x92,0x00,0x84,0x60,0xEF,0xFD,0xC1,0x39,0xC8,0x73,0x28,0x00,0x00,0x44,0x08,0x7E,0x3D,0xF3,0xF0,0x3D,0x0F,0xE8,0x7F,0x06,0x33,0x90,0x39,0x0B,0xC2,0x1E,0x30,0x89,0x08,0x8F,0xE0,0x48,0x00,0x03,0xFC,0xE7,0xB9,0x1F,0x19,0x8E,0x23,0x17,0x79,0xF1,0xC6,0xF2,0x22,0x89,0x3C,0x92,0x00,    // Line 8
	0x00,0x04,0x00,0x00,0x12,0x00,0x04,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x03,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x48,0x00,0x00,0x00,0x00,0x00,0x02,0x01,0x00,0x00,0x00,0x40,0x20,0x00,0x00,0x00,0x01,0x00,0x92,0x00,    // Line 9
	0x00,0x04,0x00,0x00,0x0C,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x38,0x0F,0xE0,0x00,0x00,0x00,0x1C,0x06,0x00,0x00,0x00,0x40,0x20,0x00,0x00,0x00,0x02,0x00,0x7C,0x00,    // Line 10
};

#ifdef pgm_read_uint
#define FNT(_x) pgm_read_uint(Verdana_font_11 + (_x))
#else
#define FNT(_x) Verdana_font_11[_x]
#endif

void init_IO(void){
	DDRC = 0XFF;
	PORTC=0x00;
	DDRB = 0XFF;
	PORTB=0x00;
	DDRA = 0XFF;
	PORTA=0xFF;
	DDRD = 0XFF;
	PORTD=0x00;
	RS_0;
	DDRA =  0xFE;
}


void LCD_reset(void){
	RESET_0;
	_delay_ms(50);
	_delay_ms(50);
	RESET_1;
	_delay_ms(50);
	_delay_ms(50);
}

void LCD_WR_CMD(uchar index,uint val){
	RS_0;
	CS_0;
	WR_DATA_L= index;
	WR_DATA_H=0;
	WR_0;
	WR_1;
	RS_1;
	WR_DATA_L = (uchar)val;
	WR_DATA_H = (uchar)(val>>8);
	WR_0;
	WR_1;
	CS_1;
}


void LCD_clear(uint col){
	uint i,j;
	LCD_WR_CMD(0x20,0);
	LCD_WR_CMD(0x21,0);
	LCD_WR_REG(0x22);
	for(i=0; i<8; i++)
		for(j=0; j<9600; j++)
			LCD_WR_DATA(col);
}

void LCD_init(void){
	//************* Start Initial Sequence **********
	LCD_WR_CMD ( 0x00E5, 0x8000);  // Set the internal vcore voltage
	LCD_WR_CMD(0x0000, 0x0001);    // Start internal OSC.
	LCD_WR_CMD(0x0001, 0x0100);    // set SS and SM bit
	LCD_WR_CMD(0x0002, 0x0700);    // set 1 line inversion
	LCD_WR_CMD(0x0003, 0x1030 /* 0x1030 */); // set GRAM write direction and BGR=1.
	//LCD_WR_REG(0x0003, 0x1028 /* 0x1030 */);
	//LCD_WR_REG(0x0003, 0x1038);
	//LCD_WR_CMD(0x0003, 0x10B0);
	LCD_WR_CMD(0x0004, 0x0000);    // Resize register
	LCD_WR_CMD(0x0008, 0x0202);    // set the back porch and front porch
	LCD_WR_CMD(0x0009, 0x0000);    // set non-display area refresh cycle ISC[3:0]
	LCD_WR_CMD(0x000A, 0x0000);    // FMARK function
	LCD_WR_CMD(0x000C, 0x0000);    // RGB interface setting
	LCD_WR_CMD(0x000D, 0x0000);    // Frame marker Position
	LCD_WR_CMD(0x000F, 0x0000);    // RGB interface polarity

	//*************Power On sequence ****************
	LCD_WR_CMD(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WR_CMD(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
	LCD_WR_CMD(0x0012, 0x0000); // VREG1OUT voltage
	LCD_WR_CMD(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
	_delay_ms(200);                 // Dis-charge capacitor power voltage
	LCD_WR_CMD(0x0010, 0x17B0); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WR_CMD(0x0011, 0x0147); // DC1[2:0], DC0[2:0], VC[2:0]
	_delay_ms(50);                  // Delay 50ms
	LCD_WR_CMD(0x0012, 0x013C); // VREG1OUT voltage
	_delay_ms(50); // Delay 50ms
	LCD_WR_CMD(0x0013, 0x0E00); // VDV[4:0] for VCOM amplitude
	LCD_WR_CMD(0x0029, 0x0009); // VCM[4:0] for VCOMH
	_delay_ms(50);
	LCD_WR_CMD(0x0020, 0x0000); // GRAM horizontal Address
	LCD_WR_CMD(0x0021, 0x0000); // GRAM Vertical Address

	// ----------- Adjust the Gamma Curve ----------
	LCD_WR_CMD(0x0030, 0x0207);
	LCD_WR_CMD(0x0031, 0x0505);
	LCD_WR_CMD(0x0032, 0x0102);
	LCD_WR_CMD(0x0035, 0x0006);
	LCD_WR_CMD(0x0036, 0x0606);
	LCD_WR_CMD(0x0037, 0x0707);
	LCD_WR_CMD(0x0038, 0x0506);
	LCD_WR_CMD(0x0039, 0x0407);
	LCD_WR_CMD(0x003C, 0x0106);
	LCD_WR_CMD(0x003D, 0x0601);

	//------------------ Set GRAM area ---------------
	LCD_WR_CMD(0x0050, 0x0000); // Horizontal GRAM Start Address
	LCD_WR_CMD(0x0051, 0x00EF); // Horizontal GRAM End Address
	LCD_WR_CMD(0x0052, 0x0000); // Vertical GRAM Start Address
	LCD_WR_CMD(0x0053, 0x013F); // Vertical GRAM End Address
	LCD_WR_CMD(0x0060, 0x2700); // Gate Scan Line
	LCD_WR_CMD(0x0061, 0x0001); // NDL,VLE, REV
	LCD_WR_CMD(0x006A, 0x0000); // set scrolling line

	//-------------- Partial Display Control ---------
	LCD_WR_CMD(0x0080, 0x0000);
	LCD_WR_CMD(0x0081, 0x0000);
	LCD_WR_CMD(0x0082, 0x0000);
	LCD_WR_CMD(0x0083, 0x0000);
	LCD_WR_CMD(0x0084, 0x0000);
	LCD_WR_CMD(0x0085, 0x0000);

	//-------------- Panel Control -------------------
	LCD_WR_CMD(0x0090, 0x0010);
	LCD_WR_CMD(0x0092, 0x0000);
	LCD_WR_CMD(0x0093, 0x0003);
	LCD_WR_CMD(0x0095, 0x0110);
	LCD_WR_CMD(0x0097, 0x0000);
	LCD_WR_CMD(0x0098, 0x0000);
	LCD_clear(0xffff);
	LCD_WR_CMD(0x0007, 0x0173); // 262K color and display ON 
}

void LCD_WR_DATA(uint val)
{
	RS_1;
	CS_0;
	WR_DATA_L=val;
	WR_DATA_H=(uchar)(val>>8);
	WR_0;
	WR_1;
	CS_1;
	RS_0;
}

void LCD_WR_REG(uchar index){
	RS_0;
	CS_0;
	WR_DATA_L= index;
	WR_DATA_H=0;
	WR_0;
	WR_1;
	CS_1;
}

uint color[]={0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xd343};

void LCD_test(void){
	uint i,j;
	LCD_WR_CMD(0x20,0); // X����������
	LCD_WR_CMD(0x21,0); // Y����������
	LCD_WR_REG(0x22); // GRAM ������� ������
	for(i=0; i<8; i++)
		for(j=0; j<9600; j++)
			LCD_WR_DATA(color[i]); // ������ ������ � GRAM
}

void LCD_PutPixel(uint x, unsigned int y, unsigned int color)
{
	LCD_SetCursor(x,y);
	LCD_WR_REG(0x22);
	LCD_WR_DATA(color);
}

void kelly (uint x ,uint y,uint xx,uint yy,uint color)
{
	uint j,i;
	for(j=0;j <= yy; j++)	
		for(i=0;i < xx;i++) 
			LCD_PutPixel(x+j,y+i,color);	
}
/*
void LCD_SetCursor ( unsigned int x , unsigned int y)
{
	if (x < 320 && y < 240) {      
		LCD_WR_CMD(0x20,y);       
		LCD_WR_CMD(0x21,320-x);   
	} 
}
*/
void LCD_SetCursor ( unsigned int x , unsigned int y)
{
//	if (x < 320 && y < 240) {
		LCD_WR_CMD(0x20,240-y);
		LCD_WR_CMD(0x21,x);
//	}
}

int LCD_DrawChar(uint xx, unsigned int yy, int c, unsigned int color)
{
	//uint* f = Verdana_font_11;
	if (c == 32)
	return FNT(1)>>2;  // Space is 1/4 font height (yuk);

	int i = c - FNT(3);
	if (i < 0 || i >= FNT(4)) return 0;

	int ci = 6 + i * 2;
	int width = (FNT(ci) << 8) | FNT(ci + 1);   // simplify
	int height = FNT(1);
	int src = 0;
	if (i > 0)
	{
		src = (FNT(ci - 2) << 8) | FNT(ci - 1);
		width -= src;
	}
	
	//  clip?
	src += (6 + 2 * FNT(4)) * 8;    // start of pixels (roll into cols)
	uint mask = 0x80 >> (src & 7);  // Mask at start of line
	int end = (src+width) >> 3;     // number of uints read
	src >>= 3;
	int makeup = FNT(5) - (end + 1 - src);
	for (uint y = 0; y < (uint)height; y++)
	{
		uint p = FNT(src++);
		uint m = mask;
		for (uint x = 0; x < (uint)width; x++)
		{
			if (p & m)
			LCD_PutPixel(x + xx, y + yy, color);
			m >>= 1;
			if (m == 0)
			{
				p = FNT(src++);
				if (p == 0 && (width-x) <= 8)   // early out
				break;
				m = 0x80;
			}
		}
		src += makeup;
	}
	return width;
}

void LCD_DrawString2(const char* s, int len, uchar x, unsigned int y, unsigned int color)
{
	for (int i = 0; i < len; i++){
	if(i==39){
		x=10;
		y+=20;
	}
	if(i==79){
			x=10;
			y+=20;
		}
	x += LCD_DrawChar(x,y,s[i], color) + 1;
	}
}

void LCD_DrawString(const char* s, uchar x, unsigned int y, unsigned int color)
{
	LCD_DrawString2(s,strlen(s),x,y, color);
}