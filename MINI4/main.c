#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

#define park1 GPIO_PIN_6
#define park2 GPIO_PIN_4
#define park3 GPIO_PIN_3
#define park4 GPIO_PIN_2

#define RED GPIO_PIN_1
#define GREEN GPIO_PIN_3
#define BLUE GPIO_PIN_2


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

while(1){
    if(GPIOPinRead(GPIO_PORTA_BASE, park2)){ //prueba de entradas
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN ,0xFF);  // mask: 0000 1110 & xxxx 101x
        GPIOPinWrite(GPIO_PORTF_BASE, BLUE ,0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, RED ,0x00);

        SysCtlDelay (10000000);

        GPIOPinWrite(GPIO_PORTF_BASE, BLUE ,0xFF);
        GPIOPinWrite(GPIO_PORTF_BASE, RED ,0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN ,0x00);

        SysCtlDelay (10000000);


        GPIOPinWrite(GPIO_PORTF_BASE, RED ,0xFF);
        GPIOPinWrite(GPIO_PORTF_BASE, BLUE ,0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN ,0x00);

        SysCtlDelay (10000000);
        }
    }
}
