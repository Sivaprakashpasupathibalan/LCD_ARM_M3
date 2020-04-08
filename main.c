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
int main()
{
  RCGC2 |= (1 << 1);                             //Setting Bitfield 1 for PORTB Enable
  PORTB_DIR = 0xFF;                              //Setting Direction Bit for PORTB
  PORTB_DATA_EN = 0xFF;                          //Setting Data Enable for PORTB
  while(1)                                       //Turn ON & OFF PORTB bits at particular interval
{
  for(int i = 0; i < 400; i++);  
  PORTB_DATA = 0xFF;
  for(int i = 0; i < 400; i++);
  PORTB_DATA = 0x00;
  for(int i = 0; i < 400; i++);
}
  return 0;
}
