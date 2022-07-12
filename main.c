#include "tm4c123gh6pm.h"
#include "GPIO_Driver.h"
#include <stdint.h>
#include <stdio.h>
#include "GPTM_Driver.h"
#include "PWM_Driver.h"
#include "Clock_Driver.h"
#include "UART_Driver.h"

void PWM_Intialization_1(void);
void PWM_Intialization_2(void);
void PortA_Intialization(void);
void UART_Intialization(void);
void GPTM_Number_1_Intialization(void);
void GPTM_Number_3_Intialization(void);

void Send_Data_UART(char Data[10]);
void Servo_Horizontal(void);
void Servo_Vertical();
void Micro_Clock(int period);
void New_Line_Message(void);
float counter = 0;
char mesg[12];
int j;
int i=0;
int main()
{
  Debug_Intialization();
  Set_Clock_MHz(16,80);

  PWM_Intialization_1();  

  PortA_Intialization();
  UART_Intialization();
  GPTM_Number_1_Intialization();
  GPTM_Number_3_Intialization();
  Servo_Vertical();

      while(1)
      {       
        char input;
      input = Receive_UART_Module(4);
      if(input == 'F')
      {
        Debug_Led("Red",1);                                                           //RED led ON
        Debug_Led("Blue",0);                                                          //BLUE led OFF
        Debug_Led("Green",0);                                                         //GREEN led OFF
        PIN_WRITE_DIGITAL('A',2,"Low");
        PIN_WRITE_DIGITAL('A',3,"Low");
        PWM_Set_Duty_Cycle(0,0,'B',50);
        GPTM_Delay_Unit(1,20000,"Millisecond");
        PWM_Set_Duty_Cycle(0,0,'B',1);
      }
      if(input == 'B')
      {
        Debug_Led("Red",0);                                                           //RED led OFF
        Debug_Led("Blue",1);                                                          //BLUE led OFF
        Debug_Led("Green",0);                                                         //GREEN led ON
        PIN_WRITE_DIGITAL('A',2,"HIGH");
        PIN_WRITE_DIGITAL('A',3,"HIGH");
        PWM_Set_Duty_Cycle(0,0,'B',50);
        GPTM_Delay_Unit(1,20000,"Millisecond");
        PWM_Set_Duty_Cycle(0,0,'B',1);
      }
       if(input == 'R')
      {
        Debug_Led("Red",0);                                                           //RED led OFF
        Debug_Led("Blue",0);                                                          //BLUE led ON
        Debug_Led("Green",1);                                                         //GREEN led OFF
        PIN_WRITE_DIGITAL('A',2,"LOW");
        PIN_WRITE_DIGITAL('A',3,"HIGH");
        PWM_Set_Duty_Cycle(0,0,'B',50);
        GPTM_Delay_Unit(1,20000,"Millisecond");
        PWM_Set_Duty_Cycle(0,0,'B',1);

      }
       if(input == 'L')
      {
        Debug_Led("Red",0);                                                           //RED led OFF
        Debug_Led("Blue",0);                                                          //BLUE led ON
        Debug_Led("Green",1);                                                         //GREEN led OFF
        PIN_WRITE_DIGITAL('A',2,"HIGH");
        PIN_WRITE_DIGITAL('A',3,"LOW");
        PWM_Set_Duty_Cycle(0,0,'B',50);
        GPTM_Delay_Unit(1,20000,"Millisecond");
        PWM_Set_Duty_Cycle(0,0,'B',1);

      }
      if(input == 'Z')
      {
       Servo_Horizontal();
      }
      if(input == 'X')
      {
       Servo_Vertical();
      }
      }
    /*while(1)
    {
     for(i=1;i<100;i++)
     {  
       PWM_Set_Duty_Cycle(0,0,'B',i);
          for(j=1;j<5;j++)
          {
            
              Enable_Timer_Number(3,"Enable");
              GPTM_Delay_Unit(1,20,"Millisecond");
              counter = Timer_Number_Counts_Capture(3)*3;
              char text[10];
              sprintf(text,"%0.3f,%d", counter,i);
              Send_Data_UART(text);
              New_Line_Message();                                
              Enable_Timer_Number(3,"Disable");
              Timer_Number_Reset_Counts(3);
          }       

     
     }

        //sprintf(mesg, "\r\nRPM = %d RPM", counter);
        //printf("%s",mesg);
    }*/
}

void PWM_Intialization_1(void)
{
  CLK_PWM_Enable(0);
  CLK_Enable('B');
  PIN_FUNCTION_SELECT('B',7,"Alternative");

  PIN_CONFIGURE('B',7,"PWM");

  PIN_ANALOG_DIGITAL('B',7,"Digital");

  Use_PWM_Divisor(80,40);
  
  PWM_Generator_Enable(0,0,"Disable");

  PWM_Action_For_Load(0,0,'B',"LOW");

  PWM_Action_Comparator_Down(0,0,'B',"HIGH");
  
  PWM_Set_Frequency(0,0,10000,40);

  PWM_Set_Duty_Cycle(0,0,'B',1);

  PWM_Generator_Enable(0,0,"Enable");

  PWM_Module_Start(0);
}

void GPTM_Number_1_Intialization(void)
{
  CLK_Enable_GPTM_Module(1); 																												//Enable Clock For Timer A
  Enable_Timer_Number(1,"Disable");																						  		//Disable Timer A
  Timer_Number_Option(1,"16");																													//16 bit Timer
  Timer_Number_Mode(1,"periodic");																										//Periodic Timer
  Timer_Number_Ticks(1,16);																															//16 Tick
  Enable_Timer_Number(1,"Enable");																								  	//Enable Timer A
}


void GPTM_Number_3_Intialization(void)
{
  CLK_Enable('B');
  PIN_INPUT_OUTPUT('B',2,"Input");
  PIN_ANALOG_DIGITAL('B',2,"Digital");
  PIN_FUNCTION_SELECT('B',2,"Alternative");
  PIN_CONFIGURE('B',2,"Capture");

  CLK_Enable_GPTM_Module(3);
  Enable_Timer_Number(3,"Disable");
  Timer_Number_Option(3,"16");
  Timer_Number_Mode(3,"capture");           //Enable or Disable Analog and Digital
  Timer_Number_Count_limit(3,65000);
  Timer_Number_Prescaler(3,80000000,400000);
  Timer_Number_Event_Mode(3,"Positive_Edge");
}

void PortA_Intialization(void)
{
  CLK_Enable('A');
    
  PIN_ANALOG_DIGITAL('A',2,"Digital");
  PIN_ANALOG_DIGITAL('A',3,"Digital");
  PIN_ANALOG_DIGITAL('A',4,"Digital");


  
  PIN_FUNCTION_SELECT('A',2,"General I/O");
  PIN_FUNCTION_SELECT('A',3,"General I/O");
  PIN_FUNCTION_SELECT('A',4,"General I/O");


  
  PIN_INPUT_OUTPUT('A',2,"Output");
  PIN_INPUT_OUTPUT('A',3,"Output");
  PIN_INPUT_OUTPUT('A',4,"Output");



}

void UART_Intialization(void)
{
      CLK_Enable('C');                                                          //Enable Clock for Port A

	CLK_Enable_UART_Module(4);                                                //Enable Clock for UART0
	Enable_UART_Module(4,"Disable");                                          //Disable UART0 
  Baud_Rate_UART_Module(4,9600,80);                                            //Specify 9600 Baud rate
  Word_Length_UART_Module(4,8);                                             //Specify 8Bits word length
	Enable_UART_Module(4,"Enable");                                           //Enable UART0
      PIN_ANALOG_DIGITAL('C',4,"Digital");                                      //Enable Digital For Pin A0
      PIN_ANALOG_DIGITAL('C',5,"Digital");                                      //Enable Digital For Pin A1
      PIN_FUNCTION_SELECT('C',4,"Alternative");                                 //Select Alternative Function for pin A0
      PIN_FUNCTION_SELECT('C',5,"Alternative");                                 //Select Alternative Function for pin A1
      PIN_CONFIGURE('C',4,"UART");                                              //Configure A0 as UART
      PIN_CONFIGURE('C',5,"UART");                                              //Configure A1 as UART
}

void Send_Data_UART(char Data[10])
{
          //char message1[]={"To Turn Red on Press R"};
          int length = strlen(Data);
          for(int i=0;i<length;i++)
          {
            Transmit_UART_Module(0,Data[i]);
          }
          
}
void New_Line_Message(void)
{
          Transmit_UART_Module(0,10);   
          Transmit_UART_Module(0,13); 
}
void Servo_Horizontal(void)
{

   int i=0; 
	 for(i=0; i<50; i++) 
    {	
																																																			//Given 7% duty cycle trigger pulse
	  PIN_WRITE_DIGITAL('A',4,"HIGH"); 
                  GPTM_Delay_Unit(1,19400,"Millisecond");
//Make control  pin high
	  PIN_WRITE_DIGITAL('A',4,"LOW");
                  GPTM_Delay_Unit(1,600,"Millisecond");
//Make control  pin low
		}
}

void Servo_Vertical()
{
   int i=0; 
	 for(i=0; i<50; i++) 
    {	
																																																				 //Given 7% duty cycle trigger pulse
	  PIN_WRITE_DIGITAL('A',4,"HIGH");																									 //Make control  pin high
        GPTM_Delay_Unit(1,1600,"Millisecond");
	  PIN_WRITE_DIGITAL('A',4,"LOW");																									 //Make control  pin low
        GPTM_Delay_Unit(1,18400,"Millisecond");
		}
	
}
void Micro_Clock(int period)
{
	int i;
		for(i = 0; i < period; i++)
    {
        while (Timer_Number_Flag(1) == 0) ;  																		        //Wait for TimerA timeout flag
        Timer_Number_Clear(1);    																													  //Clear the TimerA timeout flag */
    }

}