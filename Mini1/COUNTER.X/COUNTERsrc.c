//*****************************************************************************
/*
 * File:   LAB1src.c
 * Author: maqui
 *
 * Created on 24 de enero de 2021, 12:37 PM
 */
//*****************************************************************************


//*****************************************************************************
//Librerias
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "SPI.h"

//*****************************************************************************
//Configuration bits
//*****************************************************************************
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 4000000

//*****************************************************************************
//Variables
//*****************************************************************************
uint8_t check0;
uint8_t check1;
uint8_t data;



//*****************************************************************************
//Creacion de funciones
//*****************************************************************************
void setup(void);


//*****************************************************************************
//Interrupciones
//*****************************************************************************
void __interrupt() ISR(void){
    if(SSPIF == 1){
        data = spiRead();
        spiWrite(PORTD);
        SSPIF = 0;
    }
}


//*****************************************************************************
//Ciclo principal
//*****************************************************************************

void main(void) {
    setup(); //realizar la configuracion

    while (1) {
        
        //Anti-rebotes
        if (check0 == 1 && PORTAbits.RA0 == 0){
            check0 = 0;
        }
        if (check1 == 1 && PORTAbits.RA1 == 0){
            check1 = 0;
        }
        
        if (PORTAbits.RA0 == 1 && check0 == 0){
            check0 = 1;
            PORTD = PORTD + 1;
        }
        
        if (PORTAbits.RA1 == 1 && check1 == 0){
            check1 = 1;
            PORTD = PORTD - 1;
        }
        
    }


}


//*****************************************************************************
//FUNCIONES
//*****************************************************************************

void setup(void) {
    
    TRISD = 0; //portD as output
    PORTD = 0; //portD = 0
    
    TRISA = 1; //portaA as input (counter btns)
    ANSEL = 0; //portA digital  
    
    check0 = 0;
    check1 = 0;
    
    //configurar MSSP
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
    INTCONbits.PEIE = 1; //Peripheral Interrupt Enable
    INTCONbits.GIE = 1; //Global interrups enable
   
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    

}
