/*
Description:c This Code is used for communication with LCD 16x2 with 4 bit interface to Display Characters and OUTPUT for ARM Cortex M3 Controller
Target: Stellaris ARM CORTEX M3 LM3S328 Microcontroller
Firmware Version : 1
Author: Shivaprakash Pasupathibalan
@ 08 April 2020
*/ 
#define RCGC2            (*((volatile unsigned long *)0x400FE108U))      //ClockGating Control Register For Run Mode GPIO ADDRESS
#define PORTB_DIR        (*((volatile unsigned long *)0x40005400U))      //PORTB Direction Control Register ADDRESS
#define PORTB_DATA_EN    (*((volatile unsigned int *)0x4000551CU))       //PORTB Data Enable Register
#define PORTB_DATA       (*((volatile unsigned long *)0x400053fcU))      //PORTB Data Control Register ADDRESS
#define PORTC_DIR        (*((volatile unsigned long *)0x40006400U))      //PORTC Direction Control Register ADDRESS
#define PORTC_DATA_EN    (*((volatile unsigned int *)0x4000651CU))       //PORTC Data Enable Register
#define PORTC_DATA       (*((volatile unsigned long *)0x400063fcU))      //PORTC Data Control Register ADDRESS
#define DLY_SET 200                                                      //Delay Value set for wait function
#define RS  (1 << 0)
#define EN  (1 << 1)
/* LCD CMD Definitions */
#define LCD_CMD_4BIT 0x02
#define LCD_CMD_DISPON_CUR_OFF 0x0C
#define LCD_CMD_4BIT_INIT 0x28
#define LCD_CMD_CUR_FLINE 0x80
#define LCD_CMD_CUR_SLINE 0xC0
void wait(unsigned int DLY);                                 //Function for delay
void LCD_CMD(unsigned char cmd);                             //Function for sending cmd in four bit mode
void LCD_DATA(unsigned char data);                           //Function for sending data in four bit mode
void LCD_INIT();                                             //LCD 16x2 Initializaion
void LCD_PRINT(int line,char *s);                                   //LCD PRINT Function
void main()
{
  RCGC2 |= (1 << 1);                             //Setting Bitfield 1 for PORTB Enable
  RCGC2 |= (1 << 2);                             //Setting Bitfield 1 for PORTC Enable
  PORTB_DIR |= ( RS | EN);                              //Setting Direction Bit for PORTB
  PORTB_DATA_EN |= (RS | EN);                          //Setting Data Enable for PORTB
  PORTB_DATA = 0x00;
  PORTC_DIR = 0xF0;                              //Setting Direction Bit for PORTC
  PORTC_DATA_EN = 0xF0;                          //Setting Data Enable for PORTC
  PORTC_DATA = 0x00;
  LCD_INIT();
  LCD_PRINT(1,"4BIT LCD");
  LCD_PRINT(2,"ARM M3 CORTEX");
  while(1)                                      
{
  LCD_PRINT(1,"4BIT LCD");
  LCD_PRINT(2,"ARM M3 CORTEX");
}
}
void wait(unsigned int DLY)        //Delay Function
{
  unsigned int i;
  for(;DLY > 0;DLY--)
  {
     for(i=DLY_SET;i>0;i--);
  }
}
void LCD_CMD(unsigned char cmd)      //4Bit CMD Write function
{
  PORTC_DATA = (PORTC_DATA & 0x0F) | (cmd & 0xF0);
  PORTB_DATA = 0x00;
  PORTB_DATA = EN;
  wait(2);
  PORTB_DATA = 0x00;
  wait(2);
  PORTC_DATA = (PORTC_DATA & 0x0F) | (cmd << 4);
  PORTB_DATA = EN;
  wait(2);
  PORTB_DATA = 0x00;
  wait(2);
  PORTB_DATA = 0x00; PORTC_DATA = 0x00; 
}
void LCD_DATA(unsigned char data)      //4Bit Data Write function
{           
  PORTC_DATA = (PORTC_DATA & 0x0F) | (data & 0xF0);
  PORTB_DATA = RS;
  PORTB_DATA |= EN;
  wait(2);
  PORTB_DATA = 0x01;
  wait(2);
  PORTC_DATA = (PORTC_DATA & 0x0F) | (data << 4);
  PORTB_DATA |= EN;
  wait(2);
  PORTB_DATA = 0x01;
  wait(2);
  PORTB_DATA = 0x00; PORTC_DATA = 0x00; 
}
void LCD_INIT()                        //LCD Initialization
{
LCD_CMD(LCD_CMD_4BIT);
LCD_CMD(LCD_CMD_4BIT_INIT);
LCD_CMD(LCD_CMD_DISPON_CUR_OFF);
}
void LCD_PRINT(int line,char *s)
{
   if(line == 1) LCD_CMD(LCD_CMD_CUR_FLINE);
   else if(line == 2) LCD_CMD(LCD_CMD_CUR_SLINE);
   else LCD_CMD(LCD_CMD_CUR_FLINE);
   while(*s)
   {
       LCD_DATA(*s++);
   }
}
