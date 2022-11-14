/**
 ******************************************************************************
 * @file    hts221_driver.c
 * @author  Colleen Staeger 
 * @brief   This file contains functions to initialization
 *          and read LPS22 Pressure Sensor using SPI Interface 
 *      
 ******************************************************************************
 */ 

#include "lps22_driver.h" 
#include <stdint.h> 
#include <spi.c> 

/**
  * @brief  SPI Read Function 
  * @retval result 
  */
void SPI_Read(uint16_t Reg)
{
   HAL_SPI_Receive(&hspi3, (uint8_t *)&Reg, 1, HAL_MAX_DELAY); 
} 

/**
  * @brief  SPI Write Function - reads 1 byte starting at a given address 
  * @retval read Value  
  */
void SPI_Write(uint16_t Reg, uint16_t Val)
{
  /*
    uint8_t readVal = 0x00; 
    
    HAL_SPI_Transmit(&hspi3, (uint8_t *)&addr, 1, 
    HAL_SPI_Transmit(&hspi3, (uint8_t *)&Readval, 1, HAL_MAX_DELAY); 
    
    return readVal; 
   */ 
} 


