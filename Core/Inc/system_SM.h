/**
 ******************************************************************************
 * @file    hts221.h
 * @author  Colleen Staeger
 * @brief   System SM header file 
 ******************************************************************************
*/ 
 

#ifndef __system_SM__H 
#define __system_SM__H  

#include <stdio.h> 
#include <time.h> 
#include "forecast_algo.h" 
#include "hts221_driver.h" 
#include "lps22_driver.h"

   
 /*Events*/ 
enum eEvent
{ 
  BUTTON_PRESS, 
  FORECAST_TIMER, 
  NONE, 
}; 

extern enum eEvent eNewEvent; 
   
void SnowyWeatherTest(WeatherData *wd); 
void SunnyWeatherTest(WeatherData *wd); 
void FoggyWeatherTest(WeatherData *wd); 
void RainyWeatherTest(WeatherData *wd); 

void ForecastTimerHandler(WeatherData *wd); 
void executeStateMachine(void); 



#endif 