/*
Description:c This Header Library file used for communication with LCD 16x2 with 4 bit interface to Display Characters and OUTPUT for ARM Cortex M3 Controller
Target: Stellaris ARM CORTEX M3 LM3S328 Microcontroller
Firmware Version : V1
Author: Shivaprakash Pasupathibalan
@ 09 April 2020
PIN Definitions:
LCD --- LM3S328 -- Source
RS  ---   PB0
EN  ---   PB1
D7  ---   PC7
D6  ---   PC6
D5  ---   PC5
D4  ---   PC4
RW  ---  NULL    -- GND
D1,D2,D3,D4      -- GND
*/ 
#ifndef LM3S328_LCD_H
#define LM3S328_LCD_H

//************************************************************************************************************************************************
//Memory map of LM3S328 to pointers to acccess PORT B and PORT C GPIO's can also use the standard Library of Registers in Target Microcontroller
#define RCGC2            (*((volatile unsigned long *)0x400FE108U))      //ClockGating Control Register For Run Mode GPIO ADDRESS
#define PORTB_DIR        (*((volatile unsigned long *)0x40005400U))      //PORTB Direction Control Register ADDRESS
#define PORTB_DATA_EN    (*((volatile unsigned int *)0x4000551CU))       //PORTB Data Enable Register
#define PORTB_DATA       (*((volatile unsigned long *)0x400053fcU))      //PORTB Data Control Register ADDRESS
#define PORTC_DIR        (*((volatile unsigned long *)0x40006400U))      //PORTC Direction Control Register ADDRESS
#define PORTC_DATA_EN    (*((volatile unsigned int *)0x4000651CU))       //PORTC Data Enable Register
#define PORTC_DATA       (*((volatile unsigned long *)0x400063fcU))      //PORTC Data Control Register ADDRESS
//************************************************************************************************************************************************
//Macro Definitions for 16x2 LCD INTERFACE and COMMAND CODES
#define DLY_SET 200                                                      //Delay Value set for wait function
#define RS  (1 << 0)                                                     //RS PIN set Macro
#define EN  (1 << 1)                                                     //EN PIN set Macro
/* LCD CMD Definitions */
#define LCD_CMD_4BIT 0x02                                              //4bit mode select command
#define LCD_CMD_DISPON_CUR_OFF 0x0C                                    //Disp_on and cursor_off command
#define LCD_CMD_4BIT_INIT 0x28                                         //Initilization of 4bit communication
#define LCD_CMD_CUR_FLINE 0x80                                         //cursor position in first row command
#define LCD_CMD_CUR_SLINE 0xC0                                         //cursor position in second row command
#define LCD_CMD_CLR 0x01                                               //clears the DISPLAY
//***********************************************************************************************************************************************
//Function Definitions used in the header Library
void wait(unsigned int DLY);                                 //Function for delay which is controlled by DLY_SET Macro(change according to Real time Scenario)
void LCD_CMD(unsigned char cmd);                             //Function for sending cmd in four bit mode
void LCD_DATA(unsigned char data);                           //Function for sending data in four bit mode
void LCD_INIT();                                             //LCD 16x2 Initializaion and PORT Initialization
void LCD_PRINT(int line,char *s);                            //LCD PRINT Function
void LCD_CLEAR();                                            //LCD Clear Function
//***********************************************************************************************************************************************
void LCD_INIT()                        //LCD Initialization Function
{
RCGC2 |= (1 << 1);                             //Setting Bitfield 1 for PORTB Enable in Runmode Clock Gating
RCGC2 |= (1 << 2);                             //Setting Bitfield 1 for PORTC Enable in Runmode Clock Gating
PORTB_DIR |= ( RS | EN);                       //Setting Direction Bit for PORTB
PORTB_DATA_EN |= (RS | EN);                    //Setting Data Enable for PORTB
PORTB_DATA = 0x00;                              //Clear Port Data
PORTC_DIR = 0xF0;                              //Setting Direction Bit for PORTC
PORTC_DATA_EN = 0xF0;                          //Setting Data Enable for PORTC
PORTC_DATA = 0x00;
LCD_CMD(LCD_CMD_4BIT);                        ////Default Initilization for LCD
LCD_CMD(LCD_CMD_4BIT_INIT);
LCD_CMD(LCD_CMD_DISPON_CUR_OFF);
}
//***********************************************************************************************************************************************
void LCD_PRINT(int line,char *s)           //LCD_PRINT function prints the string to LCD
{
   if(line == 1) LCD_CMD(LCD_CMD_CUR_FLINE);                //checks the given line and sends position cmd to LCD
   else if(line == 2) LCD_CMD(LCD_CMD_CUR_SLINE);
   else LCD_CMD(LCD_CMD_CUR_FLINE);
   while(*s)                 
   {
       LCD_DATA(*s++);                                      //Sends Data to the LCD  
   }
}
//***********************************************************************************************************************************************
void wait(unsigned int DLY)        //Delay Function
{
  unsigned int i;
  for(;DLY > 0;DLY--)
  {
     for(i=DLY_SET;i>0;i--);
  }
}
//***********************************************************************************************************************************************
void LCD_CMD(unsigned char cmd)      //4Bit CMD Write function
{
  PORTC_DATA = (PORTC_DATA & 0x0F) | (cmd & 0xF0);      //sends upper nibble of CMD to port register
  PORTB_DATA = 0x00;                                    //sets RS LOW
  PORTB_DATA = EN;                                      //gives EN pulse
  wait(2);
  PORTB_DATA = 0x00;
  wait(2);
  PORTC_DATA = (PORTC_DATA & 0x0F) | (cmd << 4);       //sends lower nibbleof cmd to port register
  PORTB_DATA = EN;
  wait(2);
  PORTB_DATA = 0x00;
  wait(2);
  PORTB_DATA = 0x00; PORTC_DATA = 0x00;                //Clears the registers
}
//***********************************************************************************************************************************************
void LCD_DATA(unsigned char data)      //4Bit Data Write function
{           
  PORTC_DATA = (PORTC_DATA & 0x0F) | (data & 0xF0);      //sends upper nibble of data to port register
  PORTB_DATA = RS;                                       //sets RS HIGH
  PORTB_DATA |= EN;                                      //gives EN pulse
  wait(2);
  PORTB_DATA = 0x01;
  wait(2);
  PORTC_DATA = (PORTC_DATA & 0x0F) | (data << 4);        //sends lower nibbleof data to port register
  PORTB_DATA |= EN;
  wait(2);
  PORTB_DATA = 0x01;
  wait(2);
  PORTB_DATA = 0x00; PORTC_DATA = 0x00;                  //Clears the registers
}
//***********************************************************************************************************************************************
void LCD_CLEAR()    //Clears the Display function
{
  LCD_CMD(LCD_CMD_CLR);
}
//***********************************************************************************************************************************************
#endif  //LM3S328_LCD_H
