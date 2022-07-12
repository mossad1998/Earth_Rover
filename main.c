#include "tm4c123gh6pm.h"
#include "GPIO_Driver.h"
#include "UART_Driver.h"
#include "Clock_Driver.h"
#include "PWM_Driver.h"
#include "Debug_Driver.h"
#include <stdint.h>
#include "stdio.h"
void New_Line_Message(void);
void Message_1(void);
void Message_2(void);
void Message_3(void);
void LED(char type[],int mode);
int main()
{

  
  //Set_Clock_MHz(16,80);
  CLK_PWM_Enable(0);
  CLK_Enable('B');
  PIN_FUNCTION_SELECT('B',7,"Alternative");
  PIN_CONFIGURE('B',7,"PWM");
  PIN_ANALOG_DIGITAL('B',7,"Digital");
  Use_PWM_Divisor(80,40);
  PWM_Generator_Enable(0,0,"Disable");
  PWM_Action_For_Load(0,0,'B',"LOW");
  PWM_Action_Comparator_Down(0,0,'B',"HIGH");
  PWM_Set_Frequency(0,0,10000,16);
  PWM_Set_Duty_Cycle(0,0,'B',50);
  PWM_Generator_Enable(0,0,"Enable");
  PWM_Module_Start(0);
  
  
      CLK_Enable('C');                                                          //Enable Clock for Port A
      CLK_Enable_UART_Module(4);                                                //Enable Clock for UART0
      CLK_Enable('F');                                                          //Enable Clock for Port F
      GPIO_PORT_LOCK('F');                                                      //Unlock for port F

      Enable_UART_Module(4,"Disable");                                          //Disable UART0  
      Baud_Rate_UART_Module(4,9600);                                            //Specify 9600 Baud rate
      Word_Length_UART_Module(4,8);                                             //Specify 8Bits word length
      Enable_UART_Module(4,"Enable");                                           //Enable UART0

      PIN_ANALOG_DIGITAL('C',4,"Digital");                                      //Enable Digital For Pin A0
      PIN_ANALOG_DIGITAL('C',5,"Digital");                                      //Enable Digital For Pin A1
      PIN_FUNCTION_SELECT('C',4,"Alternative");                                 //Select Alternative Function for pin A0
      PIN_FUNCTION_SELECT('C',5,"Alternative");                                 //Select Alternative Function for pin A1
      PIN_CONFIGURE('C',4,"UART");                                              //Configure A0 as UART
      PIN_CONFIGURE('C',5,"UART");                                              //Configure A1 as UART
      
      PIN_INPUT_OUTPUT('F',1,"Output");                                         //To specifiy pin F1 as Output
      PIN_INPUT_OUTPUT('F',2,"Output");                                         //To specifiy pin F2 as Output
      PIN_INPUT_OUTPUT('F',3,"Output");                                         //To specifiy pin F3 as Output
      PIN_ANALOG_DIGITAL('F',1,"Digital");                                      //Enable Digital For Pin F1
      PIN_ANALOG_DIGITAL('F',2,"Digital");                                      //Enable Digital For Pin F2
      PIN_ANALOG_DIGITAL('F',3,"Digital");                                      //Enable Digital For Pin F3
      
      Message_1();                                                              //Print message for interface
      New_Line_Message();                                                       //Print New Line
      Message_2();                                                              //Print message for interface
      New_Line_Message();                                                       //Print New Line
      Message_3();                                                              //Print message for interface
      New_Line_Message();                                                       //Print New Line


  while(1)
  {
      char input;
      input = Receive_UART_Module(4);
      if(input == 'R')
      {
        LED("RED",1);                                                           //RED led ON
        LED("BLUE",0);                                                          //BLUE led OFF
        LED("GREEN",0);                                                         //GREEN led OFF
      }
            if(input == 'G')
      {
        LED("RED",0);                                                           //RED led OFF
        LED("BLUE",0);                                                          //BLUE led OFF
        LED("GREEN",1);                                                         //GREEN led ON
      }
            if(input == 'B')
      {
        LED("RED",0);                                                           //RED led OFF
        LED("BLUE",1);                                                          //BLUE led ON
        LED("GREEN",0);                                                         //GREEN led OFF
      }
  } 

}
void Message_1(void)
{
          char message1[]={"To Turn Red on Press R"};
          int length = strlen(message1);
          for(int i=0;i<length;i++)
          Transmit_UART_Module(4,message1[i]);
}
void Message_2(void)
{         char message2[]={"To Turn Blue on Press B"};
          int length = strlen(message2);
          for(int i=0;i<length;i++)
          Transmit_UART_Module(4,message2[i]);
}
void Message_3(void)
{         char message3[]={"To Turn Green on Press G"};
          int length = strlen(message3);
          for(int i=0;i<length;i++)
          Transmit_UART_Module(4,message3[i]);
}
void New_Line_Message(void)
{
          Transmit_UART_Module(4,10);   
          Transmit_UART_Module(4,13); 
}
void LED(char type[],int mode)                                                  //To control led
{
 if(strcmp(type , "GREEN")==0)
      {
          if(mode==1)
             PIN_WRITE_DIGITAL('F',3,"HIGH");                                   //Turn ON Green LED
          else if (mode==0)
             PIN_WRITE_DIGITAL('F',3,"LOW");                                    //Turn OFF Green LED                                           
      }
          else if (strcmp(type , "RED")==0)
      {
          if(mode==1)
             PIN_WRITE_DIGITAL('F',1,"HIGH");                                   //Turn ON Red LED
          else if (mode==0)
             PIN_WRITE_DIGITAL('F',1,"LOW");                                    //Turn OFF Red LED
      }
          else if (strcmp(type , "BLUE")==0)
      {
          if(mode==1)
             PIN_WRITE_DIGITAL('F',2,"HIGH");                                   //Turn ON Blue LED
          else if (mode==0)
             PIN_WRITE_DIGITAL('F',2,"LOW");                                    //Turn OFF BLue LED                                                     
      }
}