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



//*****************************************************************************
//Variables
//*****************************************************************************
char check1;
char check2;


//*****************************************************************************
//Creacion de funciones
//*****************************************************************************
void setup(void);
void delay(unsigned char n);

//*****************************************************************************
//Ciclo principal
//*****************************************************************************

void main(void) {
    setup(); //realizar la configuracion
    
    while(1){
        if(PORTDbits.RD2 == 1){ //if btn Begin = 1 then...
            PORTA = 1;
            PORTB = 1;
            PORTD = 0;
            
            delay(200);
            PORTDbits.RD3 = 1;//red led ON
            delay(200);
            PORTDbits.RD4 = 1;//yellow led ON
            delay(200);
            PORTDbits.RD5 = 1;//green led ON
            
            check1 = 0;
            check2 = 0;
                    
            
            while(PORTDbits.RD6 != 1 && PORTDbits.RD7 != 1){
                
                if (check1 != 0 && PORTDbits.RD0 == 0){
                    check1 = 0;
                }
                
                if (check2 != 0 && PORTDbits.RD1 == 0){
                    check2 = 0;
                }
                
                if (check1 == 0 && PORTDbits.RD0 == 1){
                    PORTA = PORTA<<1;
                    check1 = 1; 
                    if (PORTAbits.RA7 == 1){
                        PORTDbits.RD6 = 1;
                    }
                    
                }
                
                if (check2 == 0 && PORTDbits.RD1 == 1){
                    PORTB = PORTB<<1;
                    check2 = 1;   
                    if (PORTBbits.RB7 == 1){
                        PORTDbits.RD7 = 1;
                    }
                }
                
                
            }
            
        }
        
    }


}


//*****************************************************************************
//FUNCIONES
//*****************************************************************************
void setup(void) {
    
    TRISD = 0; //portD as output
    TRISDbits.TRISD0 = 1; //player1  btn as input
    TRISDbits.TRISD1 = 1; //player2 btn as input
    TRISDbits.TRISD2 = 1; //Begin btn as input
    
    TRISA = 0; //portaA as ouput (player1 decades)
    ANSEL = 0; //portA digital
    TRISB = 0; //portB as ouput (player2 decades)
    ANSELH = 0; //portB digital
    
    PORTD = 0;
    PORTA = 0;
    PORTB = 0;
    

}

void delay(unsigned char n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 255; j++){      
        }
    }
  
}