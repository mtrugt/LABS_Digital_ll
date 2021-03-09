
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __BMP280_H
#define	__BMP280_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>


void BMP280_Write8(uint8_t reg_addr, uint8_t _data);
uint8_t BMP280_Read8(uint8_t reg_addr);
uint16_t BMP280_Read16(uint8_t reg_addr);

void BMP280_Configure(BMP280_mode mode, BMP280_sampling T_sampling,
                      BMP280_sampling P_sampling, BMP280_filter filter, standby_time standby);

uint8_t BMP280_begin(BMP280_mode mode,
                  BMP280_sampling T_sampling,
                  BMP280_sampling P_sampling,
                  BMP280_filter filter,
                  standby_time  standby);

uint8_t BMP280_ForcedMeasurement();
void BMP280_Update();
uint8_t BMP280_readTemperature(int32_t *temp);
uint8_t BMP280_readPressure(uint32_t *pres);
