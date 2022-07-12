#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <string.h>

#ifndef __UART_Driver_H__
#define __UART_Driver_H__

//define of clk of each port
#define CLK_UART0 	(0x01)
#define CLK_UART1 	(0x02)
#define CLK_UART2 	(0x04)
#define CLK_UART3 	(0x08)
#define CLK_UART4 	(0x10)
#define CLK_UART5 	(0x20)
#define CLK_UART6 	(0x40)
#define CLK_UART7 	(0x80)

extern void CLK_Enable_UART_Module(int UART_module);                            //Enable clock for different modules
extern void Enable_UART_Module(int UART_module,char type[10]);                  //Enable or Disable different modules
extern void Baud_Rate_UART_Module(int UART_module,int speed,int System_Clock);  //Specify Baud rate
extern void Word_Length_UART_Module(int UART_module,int Length);                //Specify word length
extern void Transmit_UART_Module(int UART_module,char data);                    //To transmit data
extern char Receive_UART_Module(int UART_module);                               //To receive data
extern char Receive_UART_Module_Interrupt(int UART_module);                     //To receive data using interrupt

#endif
