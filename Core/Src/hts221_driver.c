/**
 ******************************************************************************
 * @file    hts221_driver.c
 * @author  Colleen Staeger 
 * @brief   This file contains functions to initialization and read HTS221 Temp 
 *           and Humidity 
 ******************************************************************************
 */ 

#include "hts221_driver.h" 
   
/* Variables */ 

/**
  * @brief I2C Read Function  
  * 
  */ 
static uint8_t I2C_Read(uint8_t Addr, uint16_t Reg)
{
  uint8_t readVal = 0x00; 
  
  HAL_I2C_Mem_Read(&hi2c2, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&readVal, 1, 1000);
  
  return readVal; 

}


/**
  * @brief I2C Write Function 
  * 
  */
static void I2C_Write(uint8_t Addr, uint16_t Reg, uint8_t Value, uint16_t Length)
{ 
  
  HAL_I2C_Mem_Write(&hi2c2, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&Value, Length, 1000);
  
}


/**
  * @brief Sensor Initialization 
  *
  */ 
void HTS221_Init(void) 
{ 
  uint8_t temp;
  
  /* Read CTRL_REG1 */
  I2C_Read(HTS221_I2C_ADDRESS, HTS221_CTRL_REG1); 
  
  /* Turn on  BDU */
  temp &= ~HTS221_BDU_MASK;
  temp |= (1 << HTS221_BDU_BIT);
  
  /* ODR to 1HZ (default)  */
  temp &= ~HTS221_ODR_MASK;
  temp |= (uint8_t)0x01; 
  
  /* Activate PD */
  temp |= HTS221_PD_MASK;
  
  /* Initialize CTRL_REG1 with values  */
  I2C_Write(HTS221_I2C_ADDRESS, HTS221_CTRL_REG1, temp, 1); 
 
} 

/**
  * @brief Get Device ID  
  *
  */
uint8_t HTS221_WHO_I_AM(void)
{ 

    uint8_t id = 0x00; 
    
    /*Read value from the who am i register */ 
    id = I2C_Read(HTS221_I2C_ADDRESS, HTS221_WHO_AM_I_REG);  
    
    if(id != HTS221_WHO_AM_I_VAL)
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
  * @brief Reads and returns the temp value 
  *
  */ 
float HTS221_ReadHumidity(void)
{
  uint16_t H0_T0_OUT, H1_T0_OUT, H0, H1, H_T_OUT;  
  uint8_t H0_RH, H1_RH, H0_T0_OUT_L, H0_T0_OUT_H, H1_T0_OUT_L, H1_T0_OUT_H, H_T_OUT_L, H_T_OUT_H; 
  float hum_f;
  char buf[100]; 
  
  /*Read from humidity calibration registers*/ 
  H0_RH = I2C_Read(HTS221_I2C_ADDRESS, (HTS221_H0_RH_X2)); 
  H1_RH = I2C_Read(HTS221_I2C_ADDRESS, (HTS221_H1_RH_X2)); 
  
  /*divide by 2 */ 
  H0 = H0_RH >> 1; 
  H1 = H1_RH >> 1; 
  
  /*Read from more calibration registers*/ 
  H0_T0_OUT_L= I2C_Read(HTS221_I2C_ADDRESS, (HTS221_H0_T0_OUT_L));
  H0_T0_OUT_H = I2C_Read(HTS221_I2C_ADDRESS,(HTS221_H0_T0_OUT_H));
  
  H0_T0_OUT = ((uint16_t)H0_T0_OUT_H << 8) + (uint16_t)H0_T0_OUT_L; 
  
  H1_T0_OUT_L = I2C_Read(HTS221_I2C_ADDRESS, (HTS221_H1_T0_OUT_L)); 
  H1_T0_OUT_H = I2C_Read(HTS221_I2C_ADDRESS, (HTS221_H1_T0_OUT_H)); 
   
  H1_T0_OUT  = ((uint16_t)H1_T0_OUT_H << 8) + (uint16_t)H1_T0_OUT_L; 
  
  /*Read from humidity output registers*/ 
  H_T_OUT_L = I2C_Read(HTS221_I2C_ADDRESS, (HTS221_HUM_OUT_LOW)); 
  H_T_OUT_H = I2C_Read(HTS221_I2C_ADDRESS, (HTS221_HUM_OUT_HIGH)); 
  
  H_T_OUT = ((uint16_t)H_T_OUT_H << 8) + (uint16_t)H_T_OUT_L; 
  
  /*Linear interpolation calculation for relative humidity*/ 
  hum_f = ((float)(H_T_OUT - H0_T0_OUT) * (float)(H1 - H0)) / ((float)(H1_T0_OUT - H0_T0_OUT) + H0); 
  
   sprintf(buf, "%f", hum_f); 
   ConsoleIoSendString("Current Humidity is: "); 
   ConsoleIoSendString(buf); 
   ConsoleIoSendString("%"); 
   ConsoleIoSendString("\r\n");

  return (hum_f);
                                                    
}

/**
  * @brief Reads and returns the humidity value  
  *
  */ 
uint16_t HTS221_ReadTemp(void)
{ 
  
   int16_t T0_out, T1_out, T_out, T0_degC_x8_u16, T1_degC_x8_u16, T0_degC, T1_degC;
   uint8_t T0_degC_tmp, T1_degC_tmp, tmp, T0_OUT_L, T0_OUT_H, T1_OUT_L, T1_OUT_H, T_out_L, T_out_H;  
   float tmp_f, tmp_f1, tmp_f2;
   char buf[100]; 

    /*Read from temp calibration registers*/ 
    T0_degC_tmp = I2C_Read(HTS221_I2C_ADDRESS, HTS221_T0_DEGC_X8); 
    T1_degC_tmp = I2C_Read(HTS221_I2C_ADDRESS, HTS221_T1_DEGC_X8); 
    tmp = I2C_Read(HTS221_I2C_ADDRESS, HTS221_T0_T1_DEGC_H2); 
    
    /*Convert the calibration values to 10 - bits*/ 
    T0_degC_x8_u16 = (((uint16_t)(tmp & 0x03)) << 8) | ((uint16_t)T0_degC_tmp);
    T1_degC_x8_u16 = (((uint16_t)(tmp & 0x0C)) << 6) | ((uint16_t)T1_degC_tmp);
    T0_degC = T0_degC_x8_u16 >> 3;
    T1_degC = T1_degC_x8_u16 >> 3;
    
    /*Read from more temp calibration registers*/ 
    T0_OUT_L = I2C_Read(HTS221_I2C_ADDRESS, (HTS221_T0_OUT_L)); 
    T0_OUT_H = I2C_Read(HTS221_I2C_ADDRESS, (HTS221_T0_OUT_H)); 
    T1_OUT_L = I2C_Read(HTS221_I2C_ADDRESS, (HTS221_T1_OUT_L)); 
    T1_OUT_H = I2C_Read(HTS221_I2C_ADDRESS, (HTS221_T1_OUT_H)); 
    
    T0_out = (((uint16_t)T0_OUT_H) << 8) | (uint16_t)T0_OUT_L;
    T1_out = (((uint16_t)T1_OUT_H) << 8) | (uint16_t)T1_OUT_L;

    /*Read from output registers*/ 
    T_out_H = I2C_Read(HTS221_I2C_ADDRESS, HTS221_TEMP_OUT_HIGH);
    T_out_L = I2C_Read(HTS221_I2C_ADDRESS, 0x2A);
    
    T_out = (((uint16_t)T_out_H) << 8) | (uint16_t)T_out_L;
    
    /*Linear Interpolation Calc*/ 
    tmp_f1 = (float)(T_out - T0_out) * (float)(T1_degC - T0_degC); 
    tmp_f2 = (float)(T1_out - T0_out); 
    
    tmp_f = ((float)tmp_f1/tmp_f2)  +  (float)T0_degC;
    
    /*Test Code*/ 
    sprintf(buf, "%f", tmp_f); 
    ConsoleIoSendString("Current Temperature is: "); 
    ConsoleIoSendString(buf); 
    ConsoleIoSendString("C"); 
    ConsoleIoSendString("\r\n"); 
    
    return tmp_f; 
} 
