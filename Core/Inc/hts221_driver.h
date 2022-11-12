/**
 ******************************************************************************
 * @file    hts221.h
 * @author  Colleen Staeger
 * @brief   HTS221 driver header file
 ******************************************************************************
*/ 
 

#ifndef __HTS221_driver__H 
#define __HTS221_driver__H 

#include "stdint.h" 
#include <stdio.h> 
#include "i2c.h"
#include "consoleIo.h" 
#include "console.h" 

#define HTS221_BIT(x) ((uint8_t)x)

/*DEFINITIONS*/ 
#define HTS221_I2C_ADDRESS    (uint8_t)0xBE
#define HTS221_WHO_AM_I_REG   (uint8_t)0x0F 
#define HTS221_WHO_AM_I_VAL   (uint8_t)0xBC

#define HTS221_CTRL_REG1      (uint8_t)0x20 
#define HTS221_CTRL_REG2      (uint8_t)0x21 
#define HTS221_CTRL_REG3      (uint8_t)0x22
#define HTS221_STATUS_REG     (unit8_t)0x27 

#define HTS221_PD_BIT          HTS221_BIT(7)
#define HTS221_BDU_BIT         HTS221_BIT(2)
#define HTS221_ODR_BIT         HTS221_BIT(0)

#define HTS221_HUM_OUT_LOW    (uint8_t)0x28 
#define HTS221_HUM_OUT_HIGH   (uint8_t)0x29 
#define HTS221_TEMP_OUT_LOW   (unit8_t)0x2A
#define HTS221_TEMP_OUT_HIGH  (uint8_t)0x2B

#define HTS221_AV_CONF_REG     (uint8_t)0x10
#define HTS221_AVGH_MASK       (uint8_t)0x07
#define HTS221_AVGT_MASK       (uint8_t)0x38

#define HTS221_PD_MASK        (uint8_t)0x80
#define HTS221_BDU_MASK       (uint8_t)0x04
#define HTS221_ODR_MASK       (uint8_t)0x03

#define HTS221_BOOT_MASK      (uint8_t)0x80
#define HTS221_HEATHER_MASK   (uint8_t)0x02
#define HTS221_ONE_SHOT_MASK  (uint8_t)0x01

/*Status Registers*/ 
#define HTS221_HDA_MASK       (uint8_t)0x02
#define HTS221_TDA_MASK       (uint8_t)0x01



/*Calibration Registers*/ 
#define HTS221_H0_RH_X2        (uint8_t)0x30
#define HTS221_H1_RH_X2        (uint8_t)0x31
#define HTS221_T0_DEGC_X8      (uint8_t)0x32
#define HTS221_T1_DEGC_X8      (uint8_t)0x33
#define HTS221_T0_T1_DEGC_H2   (uint8_t)0x35
#define HTS221_H0_T0_OUT_L     (uint8_t)0x36
#define HTS221_H0_T0_OUT_H     (uint8_t)0x37
#define HTS221_H1_T0_OUT_L     (uint8_t)0x3A
#define HTS221_H1_T0_OUT_H     (uint8_t)0x3B
#define HTS221_T0_OUT_L        (uint8_t)0x3C
#define HTS221_T0_OUT_H        (uint8_t)0x3D
#define HTS221_T1_OUT_L        (uint8_t)0x3E
#define HTS221_T1_OUT_H        (uint8_t)0x3F




/*FUNCTIONS*/ 
static uint8_t I2C_Read(uint8_t Addr, uint16_t Reg); 

static void I2C_Write(uint8_t Addr, uint16_t Reg, uint8_t Value, uint16_t Length); 

void HTS221_Init(void); 

uint8_t HTS221_WHO_I_AM(void); 

float HTS221_ReadHumidity(void); 

uint16_t HTS221_ReadTemp(void); 


#endif 