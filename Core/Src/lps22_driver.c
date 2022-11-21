/**
 ******************************************************************************
 * @file    lps22_driver.c
 * @author  Colleen Staeger 
 * @brief   This file contains functions to initialization
 *          and read LPS22 Pressure Sensor using SPI Interface 
 *      
 ******************************************************************************
 */ 

#include "lps22_driver.h" 

/**
  * @brief I2C Read Function  
  * 
  */ 
static uint8_t LPS22_I2C_Read(uint16_t Reg)
{
  uint8_t readVal = 0x00; 
  
  HAL_I2C_Mem_Read(&hi2c2, LPS22HB_I2C_ADDRESS, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&readVal, 1, 1000);
  
  return readVal; 

}


/**
  * @brief I2C Write Function 
  * 
  */
static void LPS22_I2C_Write(uint16_t Reg, uint8_t Value, uint16_t Length)
{ 
  
  HAL_I2C_Mem_Write(&hi2c2, LPS22HB_I2C_ADDRESS, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&Value, Length, 1000);
  
}


/**
  * @brief  Set LPS22HB Initialization.
  * @param  DeviceAddr: I2C device address
  * @retval None
  */
void LPS22HB_Init(void)
{
  uint8_t tmp;

  /* Set Power mode */
  tmp = LPS22_I2C_Read(LPS22HB_RES_CONF_REG);

  /*Set to low current mode */ 
  tmp &= ~(uint8_t)0x01;
  tmp |= (uint8_t)0x01;

  LPS22_I2C_Write(LPS22HB_RES_CONF_REG, tmp, 1);

  /* Read CTRL_REG1 */
  tmp = LPS22_I2C_Read(LPS22HB_CTRL_REG1);

  /* Set ODR to 25 Hz */
  tmp &= ~LPS22HB_ODR_MASK;
  tmp |= (uint8_t)0x30; 

  /* Enable BDU */
  tmp &= ~LPS22HB_BDU_MASK;
  tmp |= ((uint8_t)0x02);

  /* Apply settings to CTRL_REG1 */
  LPS22_I2C_Write(LPS22HB_CTRL_REG1, tmp, 1);
}  


/**
  * @brief  Read LPS22HB ID.
  * @retval ID 
  */
uint8_t LPS22_GetID(void)
{  
  uint8_t id = 0x00;
  
  /* Read Who am I value */
  id = LPS22_I2C_Read(LPS22HB_WHO_AM_I_REG);
  
  /*For debug*/ 
  if(id != LPS22HB_WHO_AM_I_VAL)
  { 
      ConsoleIoSendString("ID Error"); 
  } 
  else 
  { 
      ConsoleIoSendString("ID Success"); 
  }
  
  return id;
}

/**
  * @brief  Read pressure value of LPS22HB
  * @retval pressure value in mmHg 
  */
float LPS22_ReadPressure(void)
{
  uint8_t buffer[3];
  uint32_t tmp = 0;
  uint8_t i;
  int32_t pressure;
  char buf[100]; 
  float pressure_f; 
  float inHg = 0.03937; 

  /*Read the four pressure data registers*/ 
  for(i = 0; i < 3; i++)
  {
    buffer[i] = LPS22_I2C_Read(LPS22HB_PRESS_OUT_XL_REG + i);
  }

  /* Collect Data */
  for(i = 0; i < 3; i++)
    tmp |= (((uint32_t)buffer[i]) << (8 * i));

  /* convert the 2's complement 24 bit to 2's complement 32 bit */
  if(tmp & 0x00800000)
    tmp |= 0xFF000000;

  pressure = ((int32_t)tmp);

  pressure = (pressure * 100) / 4096;
  
  pressure_f = ((float)pressure / 100.0f) * inHg;
  
  sprintf(buf, "%f", pressure_f); 
  ConsoleIoSendString("Current Pressure is: "); 
  ConsoleIoSendString(buf); 
  ConsoleIoSendString(" inHg"); 
  ConsoleIoSendString("\r\n");

  return pressure_f; 
}

                

