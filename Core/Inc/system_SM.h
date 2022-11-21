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

   
void SnowyWeatherTest(WeatherData *snowy); 
void SunnyWeatherTest(WeatherData *sunny); 
void FoggyWeatherTest(WeatherData *foggy); 
void RainyWeatherTest(WeatherData *rainy); 

void ForecastTimerHandler(WeatherData *wd); 
void executeStateMachine(void); 



#endif 