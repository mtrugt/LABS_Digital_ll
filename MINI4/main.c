#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"


//Definiciones
#define park1 GPIO_PIN_6
#define park2 GPIO_PIN_4
#define park3 GPIO_PIN_3
#define park4 GPIO_PIN_2

#define RED GPIO_PIN_1
#define GREEN GPIO_PIN_3
#define BLUE GPIO_PIN_2

//variables
uint8_t ctr=0;
uint32_t Period=0;

//funciones
void DatosUart(char *Dat);

//LOOP
int main(void)
{
    //configuracion inicial
    SysCtlClockSet ( SYSCTL_SYSDIV_5 | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //reloj sistema
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOB ); //habilitar reloj puerto B
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOD ); //habilitar reloj puerto B
    //while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOA ); //habilitar reloj puerto A
    //while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOF ); //habilitar reloj puerto F
    //while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}

    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, BLUE | RED | GREEN); //salidas para led RGB

    GPIOPinTypeGPIOOutput (GPIO_PORTB_BASE, GPIO_PIN_5 | GPIO_PIN_3 | GPIO_PIN_2); //salidas para semaforos
    GPIOPinTypeGPIOOutput (GPIO_PORTD_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_1 | GPIO_PIN_6 | GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3); //salidas para semaforos
    GPIOPinTypeGPIOOutput (GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_6);

    GPIOPadConfigSet(GPIO_PORTB_BASE, park1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD); //pines, sensores, pulldown
    GPIOPadConfigSet(GPIO_PORTA_BASE, park2|park3|park4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

    //configurar uart
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);//UART1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);//PUERTO UART1
    GPIOPinConfigure(GPIO_PB0_U1RX);//configurar pb0 y pb1 para rx tx
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 |GPIO_PIN_1);
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);

    //Configuracion de UART1 a 115200 con 8 bits de datos y 1 de stop sin pariedad
    UARTConfigSetExpClk(UART1_BASE, 16000000, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
    UARTEnable(UART1_BASE);

    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0xFF);
    SysCtlDelay(1000);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x00);


while(1){
    if(GPIOPinRead(GPIO_PORTB_BASE, park1)){ //Si park1 ocupado -> enviar a
        DatosUart("a"); SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0xFF);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x00);

    }
    else{//de lo contrario, enviar b
        DatosUart("b"); SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0x00);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0xFF);

    }

    if(GPIOPinRead(GPIO_PORTA_BASE, park2)){
        DatosUart("c"); SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0xFF);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00);
    }
    else{
        DatosUart("d"); SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0xFF);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);
    }

    if(GPIOPinRead(GPIO_PORTA_BASE, park3)){
        DatosUart("e"); SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0xFF);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
    }
    else{
        DatosUart("f"); SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0xFF);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
    }

    if(GPIOPinRead(GPIO_PORTA_BASE, park4)){
        DatosUart("g"); SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0xFF);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0x00);
    }
    else{
        DatosUart("h"); SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0xFF);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0x00);

    }


    SysCtlDelay(10000);
  }
}


void DatosUart(char *Dat){//Mandar datos si no esta ocupado
    while(UARTBusy(UART1_BASE));
    while(*Dat != '\0')
    {
        UARTCharPut(UART1_BASE, *Dat++);
    }
}
