/**
 ******************************************************************************
 * @file    forecast.c
 * @author  Colleen Staeger 
 * @brief   This file contains the main algorithm for forecasting 
 ******************************************************************************
 */ 


#include "forecast_algo.h" 
#include "consoleIo.h" 
#include <stdio.h> 

   

/**
  * @brief Caculates the dewpoint spread based on incoming Temp and Relative Humidity 
  *        if there is <5 degree C difference between temp and dewpoint that is a indication that
  *        foggy conditions and low clouds are present/ on the way 
  * @param temperature, humidity 
  * @retval 
  *
  */ 
float Calc_DPSpread(WeatherData *wd)
{ 
     
     float DPSpread; 
     float Td; 
     
     /*Calculate dewpoint from humidity*/ 
     Td = ((wd->temperature) - (100.0 - (wd ->humidity)))/ 5.0; 
     
     /*Calculate the difference between dewpoint and temp*/ 
     DPSpread = fabs(Td - (wd->temperature)); 
     
     return DPSpread; 
     
} 
                         
 
/**
  * @brief  Calculates the Cloud Height Based on incoming Temp and Relative Humidity
  * @param current temperature, current humidity, and current elevation 
  * @retval Cloud Base - lowest altitude of visible portion of the cloud 
  */ 
float Calc_CloudBase(WeatherData *wd) 
{ 
    float Cb; 
    float Td; 
    uint16_t currentElevation = 830; 
    
    /*Convert from Relative Humidity to Dewpoint*/
    Td = ((wd->temperature) - (100.0 - (wd->humidity)))/ 5.0; 
    
    /*Calculate Cloud Base*/ 
    Cb = ((((wd->temperature) - Td) / 2.5) * 1000) + currentElevation; 
    
    return Cb; 

}  
  
/**
  * @brief  Calculates current rainy conditions using the change in pressure
  *          and the dewpoint spread 
  *          Quickly Rising -> Very Unstable Weather  
  *          Slowly Rising -> Good Weather 
  *          Quickly Falling -> 
  * @retval Array of Pressure Change Values 
  *
  */ 
float Calc_PressureChange(WeatherData *wd) 
{ 
      
}
                         
                         
/**
  * @brief  Calculates the final forecast using all the functions above 
  *          
  * @retval 
  *
  */  
void ForecastConditions(WeatherData *wd)
{

  float cb = Calc_CloudBase(wd); 
  float DPSpread = Calc_DPSpread(wd); 
  float PressureChange = Calc_PressureChange(wd); 
  
  /*Low Clouds are surface to 6,500*/ 
  if(cb <= 6500.0) 
  { 
      ConsoleIoSendString("low clouds, pose icing and visibility risk"); 
  } 
  else if(6500.0 < cb < 20000.0)
  { 
    ConsoleIoSendString("mid level clouds"); 
  } 
  else if(cb > 20000.0)
  { 
    ConsoleIoSendString("high level clouds"); 
  } 
  
  /*DPSpread */ 
  if(DPSpread < 5)
  { 
      ConsoleIoSendString("foggy conditions"); 
  } 
    
  
} 

/**
  * @brief  Outputs data to the console, in the future will output over BLE
  *          
  * @retval 
  *
  */  
void OutputData(void)
{ 
  
  
} 
  