/**
 ******************************************************************************
 * @file    forecast.c
 * @author  Colleen Staeger 
 * @brief   This file contains the main algorithm for forecasting 
 ******************************************************************************
 */ 


#include "forecast_algo.h" 
#include "consoleIo.h" 

/**
  * @brief Caculates the dewpoint spread based on incoming Temp and Relative Humidity 
  *        if there is 2 degree C difference between temp and dewpoint that is a indication that
  *        foggy conditions and low clouds are on the way 
  * @retval Td - the dewpoint spread 
  *
  */ 
float Calc_DPSpread(float temp, float humidity)
{ 
  
     float Td; 
     
     /*Calculate dewpoint spread*/ 
     Td = (temp - (100.0 - humidity))/ 5.0; 
     
     return Td; 
                                               
} 
                         
 
/**
  * @brief  Calculates the Cloud Height Based on incoming Temp and Relative Humidity  
  * @retval 
  *
  */ 
void Calc_CloudBase(float temp, float humidity, float currentElevation) 
{ 
    float Cb; 
    
    /*Convert from Relative Humidity to Dewpoint*/
    //Td = 
    
    /*Calculate Cloud Basis*/ 
    //Cb = (((temp - dewpoint) / 4.5) * 1000) + currentElevation; 
    
    
}  
/**
  * @brief  Uses the change in pressure over 20 mins to 
  * @retval 
  *
   */ 
void Calc_PressureChange(float pressure) 
{ 

}         
 
  
/**
  * @brief  Calculates current rainy conditions using the change in pressure
  *          and the dewpoint spread 
  * @retval 
  *
  */ 
void Calc_Raining(float pressure) 
{ 
    
}
                         
                         
/**
  * @brief  Calculates the final forecast using all the functions above 
  *          
  * @retval 
  *
  */  
void ForecastConditions(void)
{
    //switch(newCondition) {
} 
     
  