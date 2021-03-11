
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
//#ifndef __BMP_H
#define	__BMP_H

#if !defined BMP280_I2C1  &&  !defined BMP280_I2C2
#define  BMP280_I2C1
#endif

#if defined BMP280_I2C1  &&  defined BMP280_I2C2
#undef  BMP280_I2C2
#endif

#ifdef  BMP280_I2C1
#define BMP280_Start    I2C1_Start
#define BMP280_Write    I2C1_Wr
#define BMP280_Read     I2C1_Rd
#define BMP280_Stop     I2C1_Stop
#endif

#ifdef  BMP280_I2C2
#define BMP280_Start    I2C2_Start
#define BMP280_Write    I2C2_Wr
#define BMP280_Read     I2C2_Rd
#define BMP280_Stop     I2C2_Stop
#endif

#ifndef BMP280_I2C_ADDRESS
  #define BMP280_I2C_ADDRESS  0xEE
#endif

#define BMP280_CHIP_ID        0x58

#define BMP280_REG_DIG_T1     0x88
#define BMP280_REG_DIG_T2     0x8A
#define BMP280_REG_DIG_T3     0x8C

#define BMP280_REG_DIG_P1     0x8E
#define BMP280_REG_DIG_P2     0x90
#define BMP280_REG_DIG_P3     0x92
#define BMP280_REG_DIG_P4     0x94
#define BMP280_REG_DIG_P5     0x96
#define BMP280_REG_DIG_P6     0x98
#define BMP280_REG_DIG_P7     0x9A
#define BMP280_REG_DIG_P8     0x9C
#define BMP280_REG_DIG_P9     0x9E

#define BMP280_REG_CHIPID     0xD0
#define BMP280_REG_SOFTRESET  0xE0

#define BMP280_REG_STATUS     0xF3
#define BMP280_REG_CONTROL    0xF4
#define BMP280_REG_CONFIG     0xF5
#define BMP280_REG_PRESS_MSB  0xF7



typedef enum
{
  MODE_SLEEP  = 0x00,  // sleep mode
  MODE_FORCED = 0x01,  // forced mode
  MODE_NORMAL = 0x03   // normal mode
} BMP280_mode;

// oversampling setting. osrs_t[2:0], osrs_p[2:0]
typedef enum
{
  SAMPLING_SKIPPED = 0x00,  //skipped, output set to 0x80000
  SAMPLING_X1      = 0x01,  // oversampling x1
  SAMPLING_X2      = 0x02,  // oversampling x2
  SAMPLING_X4      = 0x03,  // oversampling x4
  SAMPLING_X8      = 0x04,  // oversampling x8
  SAMPLING_X16     = 0x05   // oversampling x16
} BMP280_sampling;

// filter setting filter[2:0]
typedef enum
{
  FILTER_OFF = 0x00,  // filter off
  FILTER_2   = 0x01,  // filter coefficient = 2
  FILTER_4   = 0x02,  // filter coefficient = 4
  FILTER_8   = 0x03,  // filter coefficient = 8
  FILTER_16  = 0x04   // filter coefficient = 16
} BMP280_filter;

// standby (inactive) time in ms (used in normal mode), t_sb[2:0]
typedef enum
{
  STANDBY_0_5   =  0x00,  // standby time = 0.5 ms
  STANDBY_62_5  =  0x01,  // standby time = 62.5 ms
  STANDBY_125   =  0x02,  // standby time = 125 ms
  STANDBY_250   =  0x03,  // standby time = 250 ms
  STANDBY_500   =  0x04,  // standby time = 500 ms
  STANDBY_1000  =  0x05,  // standby time = 1000 ms
  STANDBY_2000  =  0x06,  // standby time = 2000 ms
  STANDBY_4000  =  0x07   // standby time = 4000 ms
} standby_time;

struct
{
  uint16_t dig_T1;
  int16_t  dig_T2;
  int16_t  dig_T3;

  uint16_t dig_P1;
  int16_t  dig_P2;
  int16_t  dig_P3;
  int16_t  dig_P4;
  int16_t  dig_P5;
  int16_t  dig_P6;
  int16_t  dig_P7;
  int16_t  dig_P8;
  int16_t  dig_P9;
} BMP280_calib;






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
