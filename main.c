/*
Description: This Code is used for communication with LCD 16x2 with 4 bit interface to Display Characters and OUTPUT for ARM Cortex M3 Controller
Target: Stellaris ARM CORTEX M3 LM3S328 Microcontroller
Firmware Version : 1
Author: Shivaprakash Pasupathibalan
@ 08 April 2020
*/ 
#define RCGC2       (*((volatile unsigned long *)0x400FE108))      //ClockGating Control Register For Run Mode GPIO ADDRESS
#define PORTB_DIR   (*((volatile unsigned long *)0x40005400))      //PORTB Direction Control Register ADDRESS
#define PORTB_DATA  (*((volatile unsigned long *)0x400053fc))      //PORTB Data Control Register ADDRESS
int main()
{
  RCGC2 |= (1 << 1);                              //Setting Bitfield 1 for PORTB Enable
  PORTB_DIR = 0xFFFFFFFF;                         //Setting Direction Bit for PORTB
  while(1)                                        //Turn ON & OFF PORTB bits at particular interval
{
  for(int i = 0; i < 400; i++);  
  PORTB_DATA = 0xFFFFFFFF;
  for(int i = 0; i < 400; i++);
  PORTB_DATA = 0x00000000;
  for(int i = 0; i < 400; i++);
}
  return 0;
}
