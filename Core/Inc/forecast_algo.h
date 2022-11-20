#ifndef FORECAST_ALGO_H
#define FORECAST_ALGO_H


#include <stdio.h>

typedef struct 
{ 
  float temperature; 
  float humidity;  
  float pressure[5];  
} WeatherData;

extern WeatherData Data1; 

float Calc_CloudBase(WeatherData *wd); 
float Calc_PressureChange(WeatherData *wd); 
void ForecastConditions(WeatherData *wd); 
void OutputData(void); 

#endif // FORECAST_TEST_H