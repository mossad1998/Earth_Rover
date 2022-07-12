#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "Debug_Driver.h"

#ifndef GPTM_Driver_h
#define GPTM_Driver_h

extern void CLK_Enable_GPTM_Module(int timer_number);                                                                //To Eable CLK for specific port
extern void Enable_Timer_Number(int timer_number,char type[10]);           //Enable or Disable Analog and Digital
extern void Timer_Number_Option(int timer_number,char option[10]);           //Enable or Disable Analog and Digital
extern void Timer_Number_Mode(int timer_number,char mode[10]);           //Enable or Disable Analog and Digital
extern void Timer_Number_Count_limit(int timer_number,int counts);           //Enable or Disable Analog and Digital
extern void Timer_Number_Event_Mode(int timer_number,char mode[10]);           //Enable or Disable Analog and Digital
extern int  Timer_Number_Counts_Capture(int timer_number);
extern void Timer_Number_Reset_Counts(int timer_number);
extern void Timer_Number_Prescaler (int timer_number ,int System_Clock, int timer_clock);
extern void Timer_Number_Ticks(int timer_number,int ticks);           //Enable or Disable Analog and Digital
extern void GPTM_Delay_Unit(int timer_number,int Counts,char Unit[10]);





#endif
