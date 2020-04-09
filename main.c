/*
Description: This Code is used for communication with LCD 16x2 with 4 bit interface to Display Characters and OUTPUT for ARM Cortex M3 Controller
Target: Stellaris ARM CORTEX M3 LM3S328 Microcontroller
Firmware Version : 1
Author: Shivaprakash Pasupathibalan
@ 08 April 2020
*/ 
#define RCGC2            (*((volatile unsigned long *)0x400FE108U))      //ClockGating Control Register For Run Mode GPIO ADDRESS
#define PORTB_DIR        (*((volatile unsigned long *)0x40005400U))      //PORTB Direction Control Register ADDRESS
#define PORTB_DATA_EN    (*((volatile unsigned int *)0x4000551CU))       //PORTB Data Enable Register
#define PORTB_DATA       (*((volatile unsigned long *)0x400053fcU))      //PORTB Data Control Register ADDRESS
#define RS  (1 << 0)
#define EN  (1 << 1)
#define DATA_DIR (0x0F << 2)                                                   //Data Lines For LCD 16x2
/* LCD CMD Definitions */
#define LCD_CMD_4BIT 0x28
#define LCD_CMD_DISPON_CUR_OFF 0x0C
#define LCD_CMD_CLR_RAM 0x01
#define LCD_CMD_CUR_FLINE 0x80
#define LCD_CMD_CUR_SLINE 0xC0
void wait(unsigned int DLY);                                 //Function for delay
void LCD_CMD(unsigned char cmd);                             //Function for sending cmd in four bit mode
void LCD_DATA(unsigned char data);                           //Function for sending data in four bit mode
void LCD_INIT();                                             //LCD 16x2 Initializaion
void LCD_PRINT(char *s);                                     //LCD PRINT Function
void main()
{
  RCGC2 |= (1 << 1);                             //Setting Bitfield 1 for PORTB Enable
  PORTB_DIR |= (DATA_DIR | RS | EN);                              //Setting Direction Bit for PORTB
  PORTB_DATA_EN |= (DATA_DIR | RS | EN);                          //Setting Data Enable for PORTB
  PORTB_DATA = 0x00;
  LCD_INIT();
  LCD_PRINT("hello");
  while(1)                                      
{
}
}
void wait(unsigned int DLY)        //Delay Function
{
  unsigned int i;
  for(;DLY > 0;DLY--)
  {
     for(i=11998;i>0;i--);
  }
}
void LCD_CMD(unsigned char cmd)      //4Bit CMD Mode function
{
    PORTB_DATA &= (~RS & 0x03);                       //RS PIN LOW
    PORTB_DATA |= ((cmd & 0xF0) >> 2);        //MSB bit send to LCD 
    PORTB_DATA |= EN  ;                      //EN PIN HIGH
    wait(1);
    PORTB_DATA &= ((~EN) & 0x03);             //EN PIN LOW
    PORTB_DATA |= ((((cmd<<4) & 0xF0) >> 2));        //LSB bit send to LCD 
    PORTB_DATA |= EN   ;              //EN PIN HIGH
    wait(1);
    PORTB_DATA &= 0xFC;             //EN PIN LOW
    PORTB_DATA = 0x00;               //Clear all bits
}
void LCD_DATA(unsigned char data)      //4Bit Data Mode function
{           
    PORTB_DATA |= RS;                //RS PIN HIGH
    PORTB_DATA |= ((data & 0xF0) >> 2);        //MSB bit send to LCD 
    PORTB_DATA |= EN  ;               //EN PIN HIGH
    wait(1);
    PORTB_DATA &= ((~EN) & 0x03);             //EN PIN LOW
    PORTB_DATA |= ((((data<<4) & 0xF0) >> 2));        //LSB bit send to LCD 
    PORTB_DATA |= EN   ;              //EN PIN HIGH
    wait(1);
    PORTB_DATA &= 0xFD;             //EN PIN LOW
    PORTB_DATA = 0x00;               //Clear all bits
}
void LCD_INIT()                        //LCD Initialization
{
LCD_CMD(0x20);
LCD_CMD(LCD_CMD_4BIT);
LCD_CMD(LCD_CMD_DISPON_CUR_OFF);
LCD_CMD(LCD_CMD_CLR_RAM);
LCD_CMD(LCD_CMD_CUR_FLINE);
}
void LCD_PRINT(char *s)
{
   while(*s)
   {
       LCD_DATA(*s++);
   }
}
