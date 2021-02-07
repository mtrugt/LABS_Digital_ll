#include "LAB2lib.h"

uint8_t ADCvalue;
uint8_t sevenhex;


uint8_t getADC(void){
    
    ADCvalue = ADRESH;
    return ADCvalue;
}

uint8_t seven_seg(uint8_t sevenval){
    
    switch(sevenval){
        case 0b00000000: //0
            sevenhex = 0b00111111;
            break;
            
        case 0b00000001: //1
            sevenhex = 0b00000110;
            break;
            
        case 0b00000010: //2
            sevenhex = 0b01011011;
            break;
            
        case 0b00000011: //3
            sevenhex = 0b01001111;
            break;
            
        case 0b00000100: //4
            sevenhex = 0b01100110;
            break;
            
        case 0b00000101: //5
            sevenhex = 0b01101101;
            break;
            
        case 0b00000110: //6
            sevenhex = 0b01111101;
            break;
            
        case 0b00000111: //7
            sevenhex = 0b00000111;
            break;
            
        case 0b00001000: //8
            sevenhex = 0b01111111;
            break;
            
        case 0b00001001: //9
            sevenhex = 0b01100111;
            break;
            
        case 0b00001010: //A
            sevenhex = 0b01110111;
            break;
            
        case 0b00001011: //b
            sevenhex = 0b01111100;
            break;
            
        case 0b00001100: //C
            sevenhex = 0b00111001;
            break;
            
        case 0b00001101: //d
            sevenhex = 0b01011110;
            break;
            
        case 0b00001110: //E
            sevenhex = 0b01111001;
            break;
            
        case 0b00001111: //F
            sevenhex = 0b01110001;
            break;
    }
    
    return sevenhex;
}