#include <xc.h>
#include <stdint.h>


#define RS PORTCbits.RC0 //command or write
#define LCDPORT PORTD   //Cambiar "PORTD" si se quiere utilizar otro puerto
#define E PORTCbits.RC1 //Display
#define _XTAL_FREQ 4000000

//Para cambiar el puerto se 

void LCD_cmd(uint8_t cmd){
    
    RS = 0;             // Modo recepcion de comando
	LCDPORT = cmd;
	E  = 1;             // Indicar que se esta transmitiendo un comando
        __delay_ms(4);
        E  = 0;             
    
}

void LCD_ini(void){
    TRISD = 0; //Asegurarse de que sea el TRIS correspondiente a LCDPORT
    LCDPORT = 0; 
    
    TRISCbits.TRISC0 = 0; // RS pin as output
    TRISCbits.TRISC1 = 0; // E pin as output
    
    __delay_ms(20);
    
    RS = 0;
    LCD_cmd(0b00110000); //Modo 8bits
    
    __delay_ms(6); //
    
    LCD_cmd(0b00110000); //modo 8bits
    
    __delay_ms(11);
    
    LCD_cmd(0b00110000); //modo 8bits
    
    __delay_ms(2);
    
    LCD_cmd(0b00111000);
    __delay_ms(2);
    
    LCD_cmd(0b00001100); //Encendido
    __delay_ms(2);
    
    LCD_cmd(0b00000001); //borrado
    __delay_ms(2);
    
    LCD_cmd(0b00000110); //incremento y desplazamiento del cursor
            
}

void LCD_clear(void){
    //LCD_cmd(0);
    LCD_cmd(1); //Mandar 0b00000001 en modo comando
}

void LCD_cursor(uint8_t x, uint8_t y){
    uint8_t a;
	if(y == 1)
	{
	  a = 0x80 + x - 1;
		LCD_cmd(a);
	}
	else if(y == 2)
	{
		a = 0xC0 + x - 1;
		LCD_cmd(a);
	}
}

void LCD_wchar(char c){
   RS = 1; // Modo recepcion de datos
   LCDPORT = c; //Imprimir caracter en puerto D
   
   E = 1; // indicar que se esta transmitiendo un dato
   __delay_us(40);
   E = 0;    
}

void LCD_Wstring(char *v){
    int i; //imprimir uno a uno de los caracteres en una cadena de texto
	for(i=0;v[i]!='\0';i++)
	   LCD_wchar(v[i]);
}

