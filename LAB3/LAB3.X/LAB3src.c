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
#include <stdio.h>
#include <stdlib.h>
//#include <pic16f887.h>
#include "LAB3lib.h"

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
#define RS PORTCbits.RC0 //command or write
#define LCDPORT PORTD   //Cambiar "PORTD" si se quiere utilizar otro puerto
#define E PORTCbits.RC1 //Display


//*****************************************************************************
//Variables
//*****************************************************************************
char check1;
char check2;
char LCDstring[4];
char texto[4];

//*****************************************************************************
//Creacion de funciones
//*****************************************************************************
void setup(void);
void LCD_Wchar(char c){
   RS = 1; // Modo recepcion de datos
   LCDPORT = c; //Imprimir caracter en puerto D
   
   E = 1; // indicar que se esta transmitiendo un dato
   __delay_us(40);
   E = 0;    
}

//*****************************************************************************
//Ciclo principal
//*****************************************************************************

void main(void) {
    setup(); //realizar la configuracion
    LCD_clear();
    LCD_cursor(1,1); //posicionarse en (1,1)
    LCD_Wstring("a"); //escribir un caracter
    __delay_ms(1500);
    LCD_clear();    //limpiar LCD
    LCD_cursor(1,2);
    LCD_Wstring("HOLA baby"); //escribir una cadena de texto
    __delay_ms(1500);
    LCD_clear(); 
    
    texto = "10";
 
    
    LCD_cursor(1,2);
    LCD_Wstring(LCDstring);
    __delay_ms(500);
//    LCD_clear();
//    LCD_cursor(1,2);
//    LCD_wchar(10);
//    __delay_ms(1000);
    
    
    while(1){
        
    }

}


//*****************************************************************************
//FUNCIONES
//*****************************************************************************
void setup(void) {
    TRISD = 0;
    LCD_ini(); //inicializar LCD

}
