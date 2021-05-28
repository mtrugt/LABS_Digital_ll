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


#define park1 GPIO_PIN_6
#define park2 GPIO_PIN_4
#define park3 GPIO_PIN_3
#define park4 GPIO_PIN_2

#define RED GPIO_PIN_1
#define GREEN GPIO_PIN_3
#define BLUE GPIO_PIN_2

//variables
uint8_t ctr=0;
void DatosUart(char *Dat);
int main(void)
{
    //configuracion inicial
    SysCtlClockSet ( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL  | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //reloj sistema
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOB ); //habilitar reloj puerto B
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOA ); //habilitar reloj puerto A
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOF ); //habilitar reloj puerto F
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}

    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, BLUE | RED | GREEN); //salidas para leds

    GPIOPadConfigSet(GPIO_PORTB_BASE, park1, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPD); //pines, sensores, pulldown
    GPIOPadConfigSet(GPIO_PORTA_BASE, park2|park3|park4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPD);

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

while(1){
    if(GPIOPinRead(GPIO_PORTB_BASE, park1)){ //prueba de entradas
        DatosUart("a");
        GPIOPinWrite(GPIO_PORTF_BASE, RED, 0xff);
        }
    }
}
void DatosUart(char *Dat){
    while(UARTBusy(UART1_BASE));
    while(*Dat != '\0')
    {
        UARTCharPut(UART1_BASE, *Dat++);
    }
}
