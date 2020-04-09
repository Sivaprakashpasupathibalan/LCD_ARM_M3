/*
Description:c This Code is used for communication with LCD 16x2 with 4 bit interface to Display Characters and OUTPUT for ARM Cortex M3 Controller using the header 
Library with certain functions
Target: Stellaris ARM CORTEX M3 LM3S328 Microcontroller
Firmware Version : V1
Author: Shivaprakash Pasupathibalan
@ 08 April 2020
*/ 
#include "LM3S328_LCD.h"                     //LCD Header Declaration
void main()
{
  LCD_INIT();
  while(1)                                      
{
  LCD_PRINT(1,"4BIT 16x2 LCD");     //print function to LCD with line number and string
  LCD_PRINT(2,"INTERFACE");
  wait(150);
  LCD_CLEAR();                //LCD clear function
  LCD_PRINT(1,"ARM CORTEX M4");
  LCD_PRINT(2,"LM3S328");
  wait(150);
  LCD_CLEAR();
}
}
