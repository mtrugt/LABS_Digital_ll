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
uint8_t data;
uint8_t datatemp;
uint8_t sevenval;
uint8_t stemp;



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
    
    if(SSPIF == 1){
        data = spiRead();
        spiWrite(datatemp);
        SSPIF = 0;
    }
    
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
            stemp = ADRESH;
            ADC = 0;
            __delay_ms(1);
            ADCON0bits.GO_DONE = 1;   
        }
        
        if (stemp <= 63){
            PORTDbits.RD0 = 1;
            PORTDbits.RD1 = 0;
            PORTDbits.RD2 = 0;
            
            datatemp = 1;
            
        }
        
        else if (stemp>=63 && stemp<=69){
            PORTDbits.RD1 = 1;
            PORTDbits.RD0 = 0;
            PORTDbits.RD2 = 0;
            
            datatemp = 2;
        }
        
        else if (stemp>=69){
            PORTDbits.RD1 = 0;
            PORTDbits.RD0 = 0;
            PORTDbits.RD2 = 1;
            
            datatemp = 3;
        }
        
        else {
            datatemp = 0;
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
    
    //TRISB = 0; //portB as output
   // ANSELH = 0; //portB digital
    
    //TRISC = 0; //portC as output
    
    
    check0 = 0;
    check1 = 0;
    ADC = 0;
    PORTC = 0;
    data = 0;
    
    
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
    
    //configurar MSSP
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
   
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
    //Configurar timer0
    //OPTION_REGbits.PSA = 0; //Precaler to tmr0
    //OPTION_REGbits.T0CS = 0;
    //OPTION_REGbits.PS = 0b100; //Precaler 1:32
    //INTCONbits.T0IF = 0; //Limpiar bandera
    //INTCONbits.T0IE = 1; //tmr0 interrup enable
    //TMR0 = 0; //Limpiar tmr0 

}