#include "LAB2lib.h"

uint8_t ADCvalue;

uint8_t getADC(void){
    
    ADCvalue = ADRESH;
    return ADCvalue;
}