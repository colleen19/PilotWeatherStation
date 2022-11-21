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
    uint16_t currentElevation = 830; /*Minneapolis*/ 
    
    /*Convert from Relative Humidity to Dewpoint*/
    Td = ((wd->temperature) - (100.0 - (wd->humidity)))/ 5.0; 
    
    /*Calculate Cloud Base*/ 
    Cb = ((((wd->temperature) - Td) / 2.5) * 1000) + currentElevation; 
    
    return Cb; 

}  
  
/**
  * @brief  Calculates current rainy conditions using the change in pressure
  *          Quickly Rising -> Improving Weather 
  *          Stable-> No change in forecast 
  *          Quickly Falling -> Storm on the way 
  * @retval numerical value indicating either increasing, decreasing or stable pressures
  *
  */ 
uint16_t Calc_PressureChange(WeatherData *wd) 
{ 
    float diff;  
    uint16_t retVal; 
    
     /*get the pressure difference from the first and last measurement  */ 
     /*TODO - make this calculation better */ 
     diff = (wd->pressure[4])  - (wd->pressure[0]);
   
       
     if(diff >= 0.001)
     { 
         retVal = 1; 
     } 
     else if(diff <= -0.01)
     { 
         retVal = 2; 
     } 
     else if(-0.001 > diff > 0.01) 
     { 
         retVal = 3;  
     } 
     
    return retVal; 
       
}
                         
                         
/**
  * @brief  Calculates the final forecast using all the functions above 
  *          
  * @retval 
  *
  */  
uint8_t ForecastConditions(WeatherData *wd)
{

  float cb = Calc_CloudBase(wd); 
  float DPSpread = Calc_DPSpread(wd); 
  uint8_t pressure = Calc_PressureChange(wd); 
  uint8_t caution_Cnt = 0; 
  
  ConsoleIoSendString("\r\n"); 
  ConsoleIoSendString("WEATHER CONDITION REPORT"); 
  ConsoleIoSendString("\r\n"); 
  ConsoleIoSendString("##########################################################");
  ConsoleIoSendString("\r\n"); 
  
  /*If pressure is decreasing and DPSpread is less than 5, it is likely raining or snowing*/ 
  if((pressure == 2) && (-5.0 <= DPSpread <= 5.0))
  { 
    if((wd->temperature) > 0)
    { 
        ConsoleIoSendString("CAUTION: Currently Raining!"); 
        caution_Cnt++; 
    } 
    else 
    { 
        ConsoleIoSendString("CAUTION: Currently Snowing!"); 
        caution_Cnt++; 
    } 
  } 
  
  
  ConsoleIoSendString("\r\n");
  /*Low Clouds are surface to 6,500 ft*/ 
  if(cb <= 6500.0) 
  { 
    ConsoleIoSendString("Low Clouds, CAUTION: pose icing and visibility risk"); 
    caution_Cnt++; 
  } 
  /* Mid Level Clouds are 6500 to 20000 ft*/ 
  else if(6500.0 < cb < 20000.0)
  { 
    ConsoleIoSendString("Mid Level clouds, CAUTION: pose slight turbulence risk"); 
  } 
  /*High Level Clouds are above 20000 ft*/ 
  else if(cb > 20000.0)
  { 
    ConsoleIoSendString("High Level Clouds, No Significant Risk"); 
  } 
  
  ConsoleIoSendString("\r\n");
  /*DPSpread */ 
  if(-5.0 <= DPSpread <= 5.0)
  { 
    ConsoleIoSendString("Foggy Conditions, CAUTION: Bad Visibility"); 
    caution_Cnt++; 
  } 
  else
  { 
    ConsoleIoSendString("Clear Skies Likely, Good visibility to fly!"); 
  } 
  ConsoleIoSendString("\r\n");
  /*Pressure Change */ 
  if(pressure == 1) 
  { 
    ConsoleIoSendString("Pressure Increasing Rapidly, Weather Conditions Improving"); 
  } 
  else if(pressure == 2) 
  { 
    ConsoleIoSendString("Pressure Decreasing Rapidly, CAUTION: Weather Conditions Worsening");
    caution_Cnt++; 
  } 
  else 
  { 
    ConsoleIoSendString("Pressure Stable, No Change in Weather Conditions"); 
  } 
  ConsoleIoSendString("\r\n");
  
  ConsoleIoSendString("\r\n");
  
  return caution_Cnt; 
  
} 

/**
  * @brief  Outputs Final Forecast to the console, in the future will output over BLE
  *          
  * @retval 
  *
  */  
void OutputData(uint8_t caution_Cnt)
{ 
   ConsoleIoSendString("\r\n"); 
   ConsoleIoSendString("FLIGHT RECOMMENDATION"); 
   ConsoleIoSendString("\r\n"); 
   ConsoleIoSendString("##########################################################");
   ConsoleIoSendString("\r\n"); 
   
   if(caution_Cnt == 0) 
   { 
     ConsoleIoSendString("GO FLY! GREAT CONDTIIONS"); 
   } 
   if((caution_Cnt == 1) | (caution_Cnt == 2)) 
   { 
     ConsoleIoSendString("FLYING OK, BUT BE CAUTIOUS"); 
   } 
   if(caution_Cnt >= 3) 
   { 
     ConsoleIoSendString("DO NOT FLY UNLESS INSTRUMENT RATED AND EXPERIENCED"); 
   } 
     
  
  
} 
  