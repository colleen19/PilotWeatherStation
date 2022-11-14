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

/**
  * @brief  SPI Read Function 
  * @retval result 
  */
void SPI_Read(void)
{   
} 

/**
  * @brief  SPI Write Function 
  * @retval result 
  */
void SPI_Write(uint16_t )
{   
} 
   
   
/**
  * @brief  Set LPS22HB Initialization.
  * @retval None
  */
void LPS22_Init(void)
{
  uint8_t temp;

  /* Set Power mode */
  temp = SENSOR_IO_Read(LPS22HB_RES_CONF_REG);

  temp &= ~LPS22HB_LCEN_MASK;
  temp |= (uint8_t)0x01; /* Set low current mode */

  SENSOR_IO_Write(LPS22HB_RES_CONF_REG, temp);

  /* Read CTRL_REG1 */
  temp = SENSOR_IO_Read(LPS22HB_CTRL_REG1);

  /* Set default ODR */
  temp &= ~LPS22HB_ODR_MASK;
  temp |= (uint8_t)0x30; /* Set ODR to 25Hz */

  /* Enable BDU */
  temp &= ~LPS22HB_BDU_MASK;
  temp |= ((uint8_t)0x02);

  /* Apply settings to CTRL_REG1 */
  SENSOR_IO_Write(LPS22HB_CTRL_REG1, temp);
}  