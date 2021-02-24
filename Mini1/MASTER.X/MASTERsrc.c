//*****************************************************************************
/*
 * File:   LAB1src.c
 * Author: Marco Trujillo
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
#include "LCD.h"
#include "uart.h"

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

#define _XTAL_FREQ 8000000
#define slave1 PORTEbits.RE0
#define slave2 PORTEbits.RE1
#define slave3 PORTEbits.RE2


//*****************************************************************************
//Variables
//*****************************************************************************
uint8_t check0;
uint8_t check1;
uint8_t ADC;
uint8_t ADCresult;
uint8_t data1;
uint8_t data2;
uint8_t data3;



//*****************************************************************************
//Creacion de funciones
//*****************************************************************************
void setup(void);
void transformADC(char k);
void transformtemp(char j);
void transformcounter(char p);

//*****************************************************************************
//Interrupciones
//*****************************************************************************
void __interrupt() ISR(void){
 
}


//*****************************************************************************
//Ciclo principal
//*****************************************************************************

void main(void) {
    
    setup(); //realizar la configuracion
    LCD_clear();
    LCD_cursor(1,1); //posicionarse en (1,1)
    LCD_Wstring("S1:"); //escribir un caracter
    __delay_ms(1);
    LCD_cursor(6,1); //posicionarse en (6,1)
    LCD_Wstring("S2:");
    __delay_ms(1);
    LCD_cursor(12,1); //posicionarse en (14,1)
    LCD_Wstring("S3:");
    
    while(1){
        
        if (check0 == 1){   //STEMP
            slave1 = 0; //select slave1
            __delay_ms(1);
            spiWrite(1);  //confirmation
            __delay_ms(2);
            data1 = spiRead();
            __delay_ms(2);
            slave1 = 1;  //slave1 off
    
            check0 = 2;
            //Ecribir informacion stemp
            transformtemp(data1);
            UART_Write(data1);
            __delay_ms(1);
            
            
        }
        
        if (check0 == 2){   //ADC
            slave2 = 0; //select slave1
            __delay_ms(1);
            spiWrite(1);  //confirmation
            __delay_ms(2);
            data2 = spiRead();
            __delay_ms(2);
            slave2 = 1;  //slave2 off
    
            check0 = 3;
            //escribir informacion ADC
            transformADC(data2);
            UART_Write(data2);
            __delay_ms(1);
        }
        
        if (check0 == 3){  //COUNTER
            slave3 = 0; //select slave1
            __delay_ms(1);
            spiWrite(1);  //confirmation
            __delay_ms(2);
            data3 = spiRead();
            __delay_ms(2);
            slave3 = 1;  //slave3 off
    
            check0 = 1;
            transformcounter(data3);
            UART_Write(data3);
            __delay_ms(1);
        }
        
        
        
        
             
        
    }

}


//*****************************************************************************
//FUNCIONES
//*****************************************************************************

void setup(void) {
    ANSEL = 0;
    ANSELH = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    PORTCbits.RC2 = 1;
    PORTCbits.RC1 = 1;

    nRBPU = 0;
    UART_Init(9600);
    
    TRISE = 0;
    PORTE = 0;
    check0 = 1;
    
    slave1 = 1;
    slave2 = 1;
    slave3 = 1;

    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
    LCD_ini(); //inicializar LCD


}

void transformADC(char k){
    
    if (k<51){              //ADC < 1V
        LCD_cursor(1,2);
        LCD_Wstring("0.");
        __delay_ms(1);
    }
    
    else if (51<=k && k<=102){  //ADC 1V-2V
        LCD_cursor(1,2);
        LCD_Wstring("1.");
        __delay_ms(1);
        k = k - 51;
    }
    
    else if (102<k && k<=153){  //ADC 2V-3V
        LCD_cursor(1,2);
        LCD_Wstring("2.");
        __delay_ms(1);
        k = k - 102;
        
    }
    
    else if (153<k && k<=204){  //ADC 3V-4V
        LCD_cursor(1,2);
        LCD_Wstring("3.");
        __delay_ms(1);
        k = k - 153;
        
    }
    
    else if (204<k && k<=255){  //ADC 4V-5V
        LCD_cursor(1,2);
        LCD_Wstring("4.");
        __delay_ms(1);
        k = k - 204;
        
    }
    
    //Escribir decimal
    if(k ==	1	){LCD_cursor(3,2); LCD_Wstring("2");}
    else if(k ==	2	){LCD_cursor(3,2); LCD_Wstring("4");}
    else if(k ==	3	){LCD_cursor(3,2); LCD_Wstring("6");}
    else if(k ==	4	){LCD_cursor(3,2); LCD_Wstring("8");}
    else if(k ==	5	){LCD_cursor(3,2); LCD_Wstring("10");}
    else if(k ==	6	){LCD_cursor(3,2); LCD_Wstring("12");}
    else if(k ==	7	){LCD_cursor(3,2); LCD_Wstring("14");}
    else if(k ==	8	){LCD_cursor(3,2); LCD_Wstring("16");}
    else if(k ==	9	){LCD_cursor(3,2); LCD_Wstring("18");}
    else if(k ==	10	){LCD_cursor(3,2); LCD_Wstring("20");}
    else if(k ==	11	){LCD_cursor(3,2); LCD_Wstring("22");}
    else if(k ==	12	){LCD_cursor(3,2); LCD_Wstring("24");}
    else if(k ==	13	){LCD_cursor(3,2); LCD_Wstring("26");}
    else if(k ==	14	){LCD_cursor(3,2); LCD_Wstring("28");}
    else if(k ==	15	){LCD_cursor(3,2); LCD_Wstring("30");}
    else if(k ==	16	){LCD_cursor(3,2); LCD_Wstring("32");}
    else if(k ==	17	){LCD_cursor(3,2); LCD_Wstring("34");}
    else if(k ==	18	){LCD_cursor(3,2); LCD_Wstring("36");}
    else if(k ==	19	){LCD_cursor(3,2); LCD_Wstring("38");}
    else if(k ==	20	){LCD_cursor(3,2); LCD_Wstring("40");}
    else if(k ==	21	){LCD_cursor(3,2); LCD_Wstring("42");}
    else if(k ==	22	){LCD_cursor(3,2); LCD_Wstring("44");}
    else if(k ==	23	){LCD_cursor(3,2); LCD_Wstring("46");}
    else if(k ==	24	){LCD_cursor(3,2); LCD_Wstring("48");}
    else if(k ==	25	){LCD_cursor(3,2); LCD_Wstring("50");}
    else if(k ==	26	){LCD_cursor(3,2); LCD_Wstring("52");}
    else if(k ==	27	){LCD_cursor(3,2); LCD_Wstring("54");}
    else if(k ==	28	){LCD_cursor(3,2); LCD_Wstring("56");}
    else if(k ==	29	){LCD_cursor(3,2); LCD_Wstring("58");}
    else if(k ==	30	){LCD_cursor(3,2); LCD_Wstring("60");}
    else if(k ==	31	){LCD_cursor(3,2); LCD_Wstring("62");}
    else if(k ==	32	){LCD_cursor(3,2); LCD_Wstring("64");}
    else if(k ==	33	){LCD_cursor(3,2); LCD_Wstring("66");}
    else if(k ==	34	){LCD_cursor(3,2); LCD_Wstring("68");}
    else if(k ==	35	){LCD_cursor(3,2); LCD_Wstring("70");}
    else if(k ==	36	){LCD_cursor(3,2); LCD_Wstring("72");}
    else if(k ==	37	){LCD_cursor(3,2); LCD_Wstring("74");}
    else if(k ==	38	){LCD_cursor(3,2); LCD_Wstring("76");}
    else if(k ==	39	){LCD_cursor(3,2); LCD_Wstring("78");}
    else if(k ==	40	){LCD_cursor(3,2); LCD_Wstring("80");}
    else if(k ==	41	){LCD_cursor(3,2); LCD_Wstring("82");}
    else if(k ==	42	){LCD_cursor(3,2); LCD_Wstring("84");}
    else if(k ==	43	){LCD_cursor(3,2); LCD_Wstring("86");}
    else if(k ==	44	){LCD_cursor(3,2); LCD_Wstring("88");}
    else if(k ==	45	){LCD_cursor(3,2); LCD_Wstring("90");}
    else if(k ==	46	){LCD_cursor(3,2); LCD_Wstring("92");}
    else if(k ==	47	){LCD_cursor(3,2); LCD_Wstring("94");}
    else if(k ==	48	){LCD_cursor(3,2); LCD_Wstring("96");}
    else if(k ==	49	){LCD_cursor(3,2); LCD_Wstring("98");}
    else if(k ==	50	){LCD_cursor(3,2); LCD_Wstring("99");}
    

}

void transformtemp(char j){
    if (j == 1){
        LCD_cursor(7,2);
        LCD_Wstring("LOW");
        
    }
    
    else if (j == 2){
        LCD_cursor(7,2);
        LCD_Wstring("OK ");
        
    }
    
    else if (j == 3){
        LCD_cursor(7,2);
        LCD_Wstring("HOT");
        
    }
    
    
}

void transformcounter(char p){  //counter 0-100
    if (p<100){
        LCD_cursor(14,2);
        LCD_Wstring("0");
        
    }
    
    else if (p>=100 && p<200){  //counter 100-200
        LCD_cursor(14,2);
        LCD_Wstring("1");
        p = p-100;
    }

    else if (p>=200 && p<=255){  //counter 100-200
        LCD_cursor(14,2);
        LCD_Wstring("2");
        p = p-200;
    }
    
    if(p ==	0	){LCD_cursor(15,2);LCD_Wstring("00");}
    if(p ==	1	){LCD_cursor(15,2);LCD_Wstring("01");}
    else if(p ==	2	){LCD_cursor(15,2);LCD_Wstring("02");}
    else if(p ==	3	){LCD_cursor(15,2);LCD_Wstring("03");}
    else if(p ==	4	){LCD_cursor(15,2);LCD_Wstring("04");}
    else if(p ==	5	){LCD_cursor(15,2);LCD_Wstring("05");}
    else if(p ==	6	){LCD_cursor(15,2);LCD_Wstring("06");}
    else if(p ==	7	){LCD_cursor(15,2);LCD_Wstring("07");}
    else if(p ==	8	){LCD_cursor(15,2);LCD_Wstring("08");}
    else if(p ==	9	){LCD_cursor(15,2);LCD_Wstring("09");}
    else if(p ==	10	){LCD_cursor(15,2);LCD_Wstring("10");}
    else if(p ==	11	){LCD_cursor(15,2);LCD_Wstring("11");}
    else if(p ==	12	){LCD_cursor(15,2);LCD_Wstring("12");}
    else if(p ==	13	){LCD_cursor(15,2);LCD_Wstring("13");}
    else if(p ==	14	){LCD_cursor(15,2);LCD_Wstring("14");}
    else if(p ==	15	){LCD_cursor(15,2);LCD_Wstring("15");}
    else if(p ==	16	){LCD_cursor(15,2);LCD_Wstring("16");}
    else if(p ==	17	){LCD_cursor(15,2);LCD_Wstring("17");}
    else if(p ==	18	){LCD_cursor(15,2);LCD_Wstring("18");}
    else if(p ==	19	){LCD_cursor(15,2);LCD_Wstring("19");}
    else if(p ==	20	){LCD_cursor(15,2);LCD_Wstring("20");}
    else if(p ==	21	){LCD_cursor(15,2);LCD_Wstring("21");}
    else if(p ==	22	){LCD_cursor(15,2);LCD_Wstring("22");}
    else if(p ==	23	){LCD_cursor(15,2);LCD_Wstring("23");}
    else if(p ==	24	){LCD_cursor(15,2);LCD_Wstring("24");}
    else if(p ==	25	){LCD_cursor(15,2);LCD_Wstring("25");}
    else if(p ==	26	){LCD_cursor(15,2);LCD_Wstring("26");}
    else if(p ==	27	){LCD_cursor(15,2);LCD_Wstring("27");}
    else if(p ==	28	){LCD_cursor(15,2);LCD_Wstring("28");}
    else if(p ==	29	){LCD_cursor(15,2);LCD_Wstring("29");}
    else if(p ==	30	){LCD_cursor(15,2);LCD_Wstring("30");}
    else if(p ==	31	){LCD_cursor(15,2);LCD_Wstring("31");}
    else if(p ==	32	){LCD_cursor(15,2);LCD_Wstring("32");}
    else if(p ==	33	){LCD_cursor(15,2);LCD_Wstring("33");}
    else if(p ==	34	){LCD_cursor(15,2);LCD_Wstring("34");}
    else if(p ==	35	){LCD_cursor(15,2);LCD_Wstring("35");}
    else if(p ==	36	){LCD_cursor(15,2);LCD_Wstring("36");}
    else if(p ==	37	){LCD_cursor(15,2);LCD_Wstring("37");}
    else if(p ==	38	){LCD_cursor(15,2);LCD_Wstring("38");}
    else if(p ==	39	){LCD_cursor(15,2);LCD_Wstring("39");}
    else if(p ==	40	){LCD_cursor(15,2);LCD_Wstring("40");}
    else if(p ==	41	){LCD_cursor(15,2);LCD_Wstring("41");}
    else if(p ==	42	){LCD_cursor(15,2);LCD_Wstring("42");}
    else if(p ==	43	){LCD_cursor(15,2);LCD_Wstring("43");}
    else if(p ==	44	){LCD_cursor(15,2);LCD_Wstring("44");}
    else if(p ==	45	){LCD_cursor(15,2);LCD_Wstring("45");}
    else if(p ==	46	){LCD_cursor(15,2);LCD_Wstring("46");}
    else if(p ==	47	){LCD_cursor(15,2);LCD_Wstring("47");}
    else if(p ==	48	){LCD_cursor(15,2);LCD_Wstring("48");}
    else if(p ==	49	){LCD_cursor(15,2);LCD_Wstring("49");}
    else if(p ==	50	){LCD_cursor(15,2);LCD_Wstring("50");}
    else if(p ==	51	){LCD_cursor(15,2);LCD_Wstring("51");}
    else if(p ==	52	){LCD_cursor(15,2);LCD_Wstring("52");}
    else if(p ==	53	){LCD_cursor(15,2);LCD_Wstring("53");}
    else if(p ==	54	){LCD_cursor(15,2);LCD_Wstring("54");}
    else if(p ==	55	){LCD_cursor(15,2);LCD_Wstring("55");}
    else if(p ==	56	){LCD_cursor(15,2);LCD_Wstring("56");}
    else if(p ==	57	){LCD_cursor(15,2);LCD_Wstring("57");}
    else if(p ==	58	){LCD_cursor(15,2);LCD_Wstring("58");}
    else if(p ==	59	){LCD_cursor(15,2);LCD_Wstring("59");}
    else if(p ==	60	){LCD_cursor(15,2);LCD_Wstring("60");}
    else if(p ==	61	){LCD_cursor(15,2);LCD_Wstring("61");}
    else if(p ==	62	){LCD_cursor(15,2);LCD_Wstring("62");}
    else if(p ==	63	){LCD_cursor(15,2);LCD_Wstring("63");}
    else if(p ==	64	){LCD_cursor(15,2);LCD_Wstring("64");}
    else if(p ==	65	){LCD_cursor(15,2);LCD_Wstring("65");}
    else if(p ==	66	){LCD_cursor(15,2);LCD_Wstring("66");}
    else if(p ==	67	){LCD_cursor(15,2);LCD_Wstring("67");}
    else if(p ==	68	){LCD_cursor(15,2);LCD_Wstring("68");}
    else if(p ==	69	){LCD_cursor(15,2);LCD_Wstring("69");}
    else if(p ==	70	){LCD_cursor(15,2);LCD_Wstring("70");}
    else if(p ==	71	){LCD_cursor(15,2);LCD_Wstring("71");}
    else if(p ==	72	){LCD_cursor(15,2);LCD_Wstring("72");}
    else if(p ==	73	){LCD_cursor(15,2);LCD_Wstring("73");}
    else if(p ==	74	){LCD_cursor(15,2);LCD_Wstring("74");}
    else if(p ==	75	){LCD_cursor(15,2);LCD_Wstring("75");}
    else if(p ==	76	){LCD_cursor(15,2);LCD_Wstring("76");}
    else if(p ==	77	){LCD_cursor(15,2);LCD_Wstring("77");}
    else if(p ==	78	){LCD_cursor(15,2);LCD_Wstring("78");}
    else if(p ==	79	){LCD_cursor(15,2);LCD_Wstring("79");}
    else if(p ==	80	){LCD_cursor(15,2);LCD_Wstring("80");}
    else if(p ==	81	){LCD_cursor(15,2);LCD_Wstring("81");}
    else if(p ==	82	){LCD_cursor(15,2);LCD_Wstring("82");}
    else if(p ==	83	){LCD_cursor(15,2);LCD_Wstring("83");}
    else if(p ==	84	){LCD_cursor(15,2);LCD_Wstring("84");}
    else if(p ==	85	){LCD_cursor(15,2);LCD_Wstring("85");}
    else if(p ==	86	){LCD_cursor(15,2);LCD_Wstring("86");}
    else if(p ==	87	){LCD_cursor(15,2);LCD_Wstring("87");}
    else if(p ==	88	){LCD_cursor(15,2);LCD_Wstring("88");}
    else if(p ==	89	){LCD_cursor(15,2);LCD_Wstring("89");}
    else if(p ==	90	){LCD_cursor(15,2);LCD_Wstring("90");}
    else if(p ==	91	){LCD_cursor(15,2);LCD_Wstring("91");}
    else if(p ==	92	){LCD_cursor(15,2);LCD_Wstring("92");}
    else if(p ==	93	){LCD_cursor(15,2);LCD_Wstring("93");}
    else if(p ==	94	){LCD_cursor(15,2);LCD_Wstring("94");}
    else if(p ==	95	){LCD_cursor(15,2);LCD_Wstring("95");}
    else if(p ==	96	){LCD_cursor(15,2);LCD_Wstring("96");}
    else if(p ==	97	){LCD_cursor(15,2);LCD_Wstring("97");}
    else if(p ==	98	){LCD_cursor(15,2);LCD_Wstring("98");}
    else if(p ==	99	){LCD_cursor(15,2);LCD_Wstring("99");}
    
    
    
    
}