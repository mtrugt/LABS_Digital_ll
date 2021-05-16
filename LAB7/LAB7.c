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


//************************************************************************
//Creacion de funciones
//************************************************************************



int main(void)
{
    //Configurar el reloj (se utilizara la misma que en la lectura 10)
    SysCtlClockSet ( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL  | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);




}
