#include "UART_Driver.h"

int CLK_UART_Modules[]={CLK_UART0,CLK_UART1,CLK_UART2,CLK_UART3,CLK_UART4,CLK_UART5,CLK_UART6,CLK_UART7};       //Array of CLK values for each module     

volatile uint32_t* UART_CTL_R[]={&UART0_CTL_R,&UART1_CTL_R,&UART2_CTL_R,&UART3_CTL_R,&UART4_CTL_R,              //Array of CTL Registers for each module
                              &UART5_CTL_R,&UART6_CTL_R,&UART7_CTL_R};

volatile uint32_t* UART_IBRD_R[]={&UART0_IBRD_R,&UART1_IBRD_R,&UART2_IBRD_R,&UART3_IBRD_R,&UART4_IBRD_R,        //Array of IBRD Registers for each module
                              &UART5_IBRD_R,&UART6_IBRD_R,&UART7_IBRD_R};

volatile uint32_t* UART_FBRD_R[]={&UART0_FBRD_R,&UART1_FBRD_R,&UART2_FBRD_R,&UART3_FBRD_R,&UART4_FBRD_R,        //Array of FBRD Registers for each module
                              &UART5_FBRD_R,&UART6_FBRD_R,&UART7_FBRD_R};

volatile uint32_t* UART_CLK_R[]={&UART0_CC_R,&UART1_CC_R,&UART2_CC_R,&UART3_CC_R,&UART4_CC_R,                   //Array of CC Registers for each module
                              &UART5_CC_R,&UART6_CC_R,&UART7_CC_R};
 
volatile uint32_t* UART_LCRH_R[]={&UART0_LCRH_R,&UART1_LCRH_R,&UART2_LCRH_R,&UART3_LCRH_R,&UART4_LCRH_R,        //Array of LCRH Registers for each module
                              &UART5_LCRH_R,&UART6_LCRH_R,&UART7_LCRH_R};

volatile uint32_t* UART_BUFFER_R[]={&UART0_FR_R,&UART1_FR_R,&UART2_FR_R,&UART3_FR_R,&UART4_FR_R,                //Array of FR Registers for each module
                              &UART5_FR_R,&UART6_FR_R,&UART7_FR_R};

volatile uint32_t* UART_DR_R[]={&UART0_DR_R,&UART1_DR_R,&UART2_DR_R,&UART3_DR_R,&UART4_DR_R,                    //Array of DR Registers for each module
                              &UART5_DR_R,&UART6_DR_R,&UART7_DR_R};

void CLK_Enable_UART_Module(int UART_module)                                    //To Eable CLK for specific module
  {
  SYSCTL_RCGCUART_R |= CLK_UART_Modules[UART_module];
    volatile uint32_t dummy ;                                                   //To wait untill enabling the CLK
    dummy = SYSCTL_RCGCGPIO_R ;                                             
  }


void Enable_UART_Module(int UART_module,char type[10])                          //Enable or Disable specific UART module
  {
    if(strcmp(type , "Enable")==0)
      {
      *UART_CTL_R[UART_module] |= 1UL << 0;                                     //To Enable UART
      *UART_CTL_R[UART_module] |= 1UL << 8;
      *UART_CTL_R[UART_module] |= 1UL << 9;
      }
    else if (strcmp(type , "Disable")==0)
      {
      *UART_CTL_R[UART_module] &= ~(1UL << 0);                                  //To Disable UART
      }
  }


void Baud_Rate_UART_Module(int UART_module,int speed)                           //Specify Baud rate
  {
    int ibrd = 1000000 / speed;                                                 //Integer value
    int fbrd = (int)((((1000000 - ibrd*speed)/speed)*64)+.5);                   //Fraction value
    *UART_IBRD_R[UART_module] = ibrd;
    *UART_FBRD_R[UART_module] = fbrd;
    *UART_CLK_R[UART_module]= 0;
  }       

void Word_Length_UART_Module(int UART_module,int Length)                        //Specify word length
  {
    if(Length == 8)
      *UART_LCRH_R[UART_module]= 0x60;                                          //8 Bits 
    if(Length == 7)
      *UART_LCRH_R[UART_module]= 0x40;                                          //7 Bits
    if(Length == 6)
      *UART_LCRH_R[UART_module]= 0x20;                                          //6 Bits   
    if(Length == 5)
      *UART_LCRH_R[UART_module]= 0x00;                                          //5 Bits
  }


void Transmit_UART_Module(int UART_module,char data)                            //To transmit data
  {
    while ((*UART_BUFFER_R[UART_module] & 0x20) != 0);                          //Check for buffer
    *UART_DR_R[UART_module] = data;                                             //Send Data
  }

char Receive_UART_Module(int UART_module)                                       //To receive data
{
    char data;
    while ((*UART_BUFFER_R[UART_module] & 0x10) != 0);                          //Check for buffer
    data = *UART_DR_R[UART_module];                                             //Read Data
    return data;
}

char Receive_UART_Module_Interrupt(int UART_module)                             //To receive data using interrupt
{
    char data;
    data = *UART_DR_R[UART_module];                                             //Read Data
    return data;
}
