#ifndef __LPS22_driver__H
#define __LPS22_driver__H


#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 
#include "i2c.h" 
#include "consoleIo.h" 
#include "console.h" 

/*Bit positioning*/ 
#define LPS22HB_BIT(x) ((uint8_t)x)


#define LPS22HB_I2C_ADDRESS             (uint8_t)0xBA
#define LPS22HB_WHO_AM_I_REG            (uint8_t)0x0F
#define LPS22HB_WHO_AM_I_VAL            (uint8_t)0xB1
#define LPS22HB_CTRL_REG1               (uint8_t)0x10
#define LPS22HB_ODR_MASK                (uint8_t)0x70
#define LPS22HB_LPFP_MASK               (uint8_t)0x08
#define LPS22HB_LPFP_CUTOFF_MASK        (uint8_t)0x04
#define LPS22HB_BDU_MASK                (uint8_t)0x02
#define LPS22HB_SIM_MASK                (uint8_t)0x01
#define LPS22HB_FIFO_EN_MASK            (uint8_t)0x40
#define LPS22HB_WTM_EN_MASK             (uint8_t)0x20
#define LPS22HB_ADD_INC_MASK            (uint8_t)0x10
#define LPS22HB_I2C_MASK                (uint8_t)0x08
#define LPS22HB_ONE_SHOT_MASK           (uint8_t)0x01
#define LPS22HB_RES_CONF_REG            (uint8_t)0x1A  /*Presure and temp resolution mode */ 
#define LPS22HB_PRESS_OUT_XL_REG        (uint8_t)0x28
#define LPS22HB_PRESS_OUT_L_REG         (uint8_t)0x29
#define LPS22HB_PRESS_OUT_H_REG         (uint8_t)0x2A
#define LPS22HB_TEMP_OUT_L_REG          (uint8_t)0x2B


#define LPS22HB_STATUS_REG            (uint8_t)0x27


void SPI_Read(uint16_t Reg); 
void SPI_Write(uint16_t Reg, uint16_t Val); 
float LPS22_ReadPressure(void); 

#endif