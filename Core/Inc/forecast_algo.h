#ifndef FORECAST_ALGO_H
#define FORECAST_ALGO_H


#include <stdio.h>
#include <stdint.h> 

typedef struct 
{ 
  float temperature; 
  float humidity;  
  float pressure[5];  
} WeatherData;

extern WeatherData Data1; 

float Calc_CloudBase(WeatherData *wd); 
uint16_t Calc_PressureChange(WeatherData *wd); 
uint8_t ForecastConditions(WeatherData *wd); 
void OutputData(uint8_t caution_Cnt); 

#endif // FORECAST_TEST_H