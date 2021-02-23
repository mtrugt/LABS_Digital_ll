
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LAB3lib_H
#define	LAB3lib_H

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f887.h>

void LCD_ini(void);
void LCD_cmd(uint8_t cmd);
void LCD_clear(void);
void LCD_cursor(uint8_t x, uint8_t y);
void LCD_Wchar(char c);
void LCD_Wstring(char *v);



#endif	/* XC_HEADER_TEMPLATE_H */

