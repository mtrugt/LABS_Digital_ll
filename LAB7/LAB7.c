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

//************************************************************************
//Creacion de variables
//************************************************************************
uint32_t onesec;
uint32_t freq;
uint32_t estado;

//************************************************************************
//Creacion de funciones
//************************************************************************
uint8_t flag_r = 0;
uint8_t flag_v = 0;
uint8_t flag_a = 0;

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
    GPIOPinWrite(GPIO_PORTF_BASE, RED, 0x1);
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE, 0x1);
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN, 0x1);

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


    while(1){}



}

}
