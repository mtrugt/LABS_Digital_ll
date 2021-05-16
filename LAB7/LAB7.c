/**
 * Marco Trujillo
 * 18069
 * Digital 2, lab 7
 */

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
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/rom.h"
#include <string.h>
#include "grlib/grlib.h"
#include "driverlib/pin_map.h"

//************************************************************************
//Creacion de variables
//************************************************************************
uint32_t onesec;
uint32_t freq;
uint32_t Estado;
char dato;
//************************************************************************
//Creacion de funciones
//************************************************************************

#define RED GPIO_PIN_1
#define GREEN GPIO_PIN_3
#define BLUE GPIO_PIN_2

//************************************************************************
//Interrupciones
//************************************************************************

void Timer0IntHandler(void){  //interrupcion timer0 a 0.5Hz
    //Limpiamos la bandera de interrupcion
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //Realizamos el toggle
    if (dato == "r"){
        GPIOPinWrite(GPIO_PORTF_BASE, RED ,0x01);
        GPIOPinWrite(GPIO_PORTF_BASE, BLUE ,0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN ,0x00);
    }

    else if (dato == "a"){
        GPIOPinWrite(GPIO_PORTF_BASE, BLUE ,0x01);
        GPIOPinWrite(GPIO_PORTF_BASE, RED ,0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN ,0x00);
    }

    else if (dato == "v"){
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN ,0x01);
            GPIOPinWrite(GPIO_PORTF_BASE, BLUE ,0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, RED ,0x00);
        }
    //reiniciar dato
    dato = "x";

}

void UARTIntHandler(void){
    // Limpiar la bandera
    UARTIntClear(UART0_BASE, Estado);

    // Leer UART
    while(UARTCharsAvail(UART0_BASE)){
        dato = UARTCharGet(UART0_BASE);
    }

}


int main(void)
{

    //Las siguientes lineas de codigo estan presentes en la lectura 10
    //Configurar el reloj
    SysCtlClockSet ( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL  | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    //Habilitar el reloj para GPIOF
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOF );
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}
    //Establecer los pines como salidas
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, BLUE | RED | GREEN);

    //Configurar el timer0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); //habilitamos el reloj
    TimerDisable(TIMER0_BASE, TIMER_A|TIMER_B); //deshabilitar timer0
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC); //configurar timer0 como periodico

    //Encontramos el valor que equivale a 1s para el timer
    onesec = SysCtlClockGet();
    //Calculamos el valor que nos dara una frecuencia de 0.5Hz
    freq = (onesec/2);
    //Subimos el valor para el timer 0
    TimerLoadSet(TIMER0_BASE, TIMER_A, freq - 1);
    //habilitamos el timer0
    TimerEnable(TIMER0_BASE, TIMER_A|TIMER_B);

    //Configurar interrupcion del timer0
    IntMasterEnable(); //Habilitar todas las interrupciones
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); //tipo de interrupcion
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler); //establecer la interrupcion
    IntEnable(INT_TIMER0A); //Habilitar interrupcion en timer0A
    TimerEnable(TIMER0_BASE, TIMER_A);

    //Configuracion UART0
    SysCtlPeripheralEnable (SYSCTL_PERIPH_UART0); //Habilitar reloj para uart0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //Habilitar reloj para puerto A
    //configurar los pines para rx y tx
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1); //Se especifican los pines para rx y tx

    //Configurar la interrupcion
    UARTDisable(UART0_BASE); //Deshabilitamos el UART
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntEnable (INT_UART0); //Habilitar interrupcion
    UARTIntEnable (UART0_BASE, UART_INT_RX | UART_INT_RT);
    UARTEnable (UART0_BASE);


    while(1){}

}


}
