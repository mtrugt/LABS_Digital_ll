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
uint8_t ADC;
uint8_t ADCresult;
uint8_t sevenval;
uint8_t multiplex;
uint8_t sevenval;




//*****************************************************************************
//Creacion de funciones
//*****************************************************************************
void setup(void);



//*****************************************************************************
//Interrupciones
//*****************************************************************************
void __interrupt() ISR(void){
    if (PIR1bits.ADIF == 1){
        PIR1bits.ADIF = 0; //clear interrupt ADC flag
        ADC = 1;
    }
    
//    if (INTCONbits.T0IF == 1){
//        INTCONbits.T0IF = 0;
//        if (multiplex == 0){
//            multiplex = 1;
//        }
//        
//        else if (multiplex == 1){
//            multiplex = 0;
//        }
//    }
    
}


//*****************************************************************************
//Ciclo principal
//*****************************************************************************

void main(void) {
    setup(); //realizar la configuracion
    __delay_ms(1);
    ADCON0bits.GO_DONE = 1; //Empezar una conversion
    
    while (1) {
        
        
        if (ADC == 1){
            PORTD = ADRESH;
            ADC = 0;
            __delay_ms(1);
            ADCON0bits.GO_DONE = 1;   
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
    ADC = 0;
    multiplex = 0;
    PORTC = 0;
    
    
    //Configurar ADC
    ANSELbits.ANS2 = 1; //RA2 as analog
    PORTAbits.RA2 = 0; 
    ADCON0bits.ADCS = 0b01; //Convertion clock = Fosc/8
    ADCON1bits.VCFG0 = 0; //VDD as conversion reference
    ADCON1bits.VCFG1 = 0; //VSS as conversion reference
    ADCON0bits.CHS = 0b0010; //Convertir el pin AN2
    ADCON1bits.ADFM = 0; //Justificado a la izquierda
    ADCON0bits.ADON = 1; //Enable ADC
        //interrupcion
    PIR1bits.ADIF = 0; //Limpiar bandera interrupcion
    PIE1bits.ADIE = 1; //Habilitar interrupcion del ADC
    INTCONbits.PEIE = 1; //Peripheral Interrupt Enable
    INTCONbits.GIE = 1; //Global interrups enable
    


}
