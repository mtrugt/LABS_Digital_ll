#include <xc.h>
#include <stdint.h>


#define RS PORTCbits.RC0
#define E PORTCbits.RC1
#define _XTAL_FREQ 4000000

void LCD_ini(void){
    
    __delay_ms(16);
    
    RS = 0;
    PORTD = 0b00110000; //Modo 8bits
    
    __delay_ms(6); //
    
    PORTD = 0b00110000; //modo 8bits
    
    __delay_ms(1);
    
    PORTD = 0b00110000; //modo 8bits
    
    __delay_ms(2);
    
    PORTD = 0b00111000;
    __delay_ms(2);
    
    PORTD = 0b00001000; //apagado
    __delay_ms(2);
    
    PORTD = 0b00000001; //borrado
    __delay_ms(2);
    
    PORTD = 0b00000111; //incremento y desplazamiento
            
}