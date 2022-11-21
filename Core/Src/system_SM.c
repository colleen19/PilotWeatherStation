/**
 ******************************************************************************
 * @file    system_SM.c
 * @author  Colleen Staeger 
 * @brief   This file contains the State Machine for the System 
 ******************************************************************************
 */ 

#include "system_SM.h" 

/* States */ 
typedef enum
{ 
  INIT, 
  SLEEP, 
  GETDATA, 
  FORECAST, 
  OUTPUTDATA, 
  SYSTEMERROR, 
} eState; 



/*Events*/ 
typedef enum 
{ 
  BUTTON_PRESS, 
  FORECAST_TIMER, 
} eEvent; 

eEvent eNewEvent;

//Function Prototypes for State Machine 
static eState ButtonPressHandler(eState currentState); 

/*Define Weather Data Types*/ 
WeatherData wd; 
WeatherData sunny; 
WeatherData foggy; 
WeatherData snowy; 
WeatherData rainy; 

/**
  * @brief handler for button press event, called from interrupt  
  * 
  */
eState ButtonPressHandler(eState currentState)
{ 
    if (currentState == INIT) 
    { 
      return SLEEP; 
    }
    else if (currentState == SLEEP) 
    { 
      return INIT; 
    } 
    
} 

/**
  * @brief handler to get data every 1 min and stop at 5 min
  * In the future this should be longer to get more accruate data 
  * 
  */
void ForecastTimerHandler(WeatherData *wd) 
{ 
    uint16_t i = 0; 
    
    wd->temperature = HTS221_ReadTemp(); 
    wd->humidity = HTS221_ReadHumidity(); 
    
    /*add values to the array every minute */ 
    while(i < 5)
    {   
        wd->pressure[i] = LPS22_ReadPressure();
        //ConsoleIoSendString("Getting Pressure Data"); 
        //ConsoleIoSendString("\r\n");
        HAL_Delay(6000); 
        i++;       
    } 

} 

/**
  * @brief Alternative Function to Forecast Timer Handler to collect 
  * weather condtions for demo/testing purposes. All weather data is taken from 
  * various days from the NOAA Website. 
  * 
  */
void SnowyWeatherTest(WeatherData *wd) 
{ 
    /*Snowy Conditions*/   
    ConsoleIoSendString("Test Snowy Weather Condition Report");  
    ConsoleIoSendString("\r\n"); 
    wd->temperature = -2.0; 
    wd->humidity = 74; 
    wd->pressure[0] = 30.151;
    wd->pressure[1] = 30.149; 
    wd->pressure[2] = 30.139;
    wd->pressure[3] = 30.132;
    wd->pressure[4] = 30.129; 
     
} 

void SunnyWeatherTest(WeatherData *wd) 
{ 
     /*Sunny Conditions*/   
    ConsoleIoSendString("Test Sunny Weather Condition Report");  
    ConsoleIoSendString("\r\n\r\n"); 
    wd->temperature = 72.0; 
    wd->humidity = 74; 
    wd->pressure[0] = 38.763;
    wd->pressure[1] = 38.765; 
    wd->pressure[2] = 38.764;
    wd->pressure[3] = 38.766;
    wd->pressure[4] = 38.765; 
} 
  
void FoggyWeatherTest(WeatherData *foggy) 
{ 
     /*Foggy Conditions*/   
    ConsoleIoSendString("Test Foggy Weather Condition Report");  
    ConsoleIoSendString("\r\n"); 
    foggy->temperature = -2.0; 
    foggy->humidity = 74; 
    foggy->pressure[0] = 30.15;
    foggy->pressure[1] = 30.14; 
    foggy->pressure[2] = 30.12;
    foggy->pressure[3] = 30.12;
    foggy->pressure[4] = 30.11;
}

void RainyWeatherTest(WeatherData *wd) 
{ 
     /*Rainy Conditions*/   
    ConsoleIoSendString("Test Rainy Weather Condition Report"); 
    ConsoleIoSendString("\r\n"); 
    wd->temperature = -2.0; 
    wd->humidity = 74; 
    wd->pressure[0] = 30.151;
    wd->pressure[1] = 30.150; 
    wd->pressure[2] = 30.147;
    wd->pressure[3] = 30.146;
    wd->pressure[4] = 30.145; 
}

/**
  * @brief starts the state machine 
  * 
  */
void executeStateMachine(void)
{ 
  eState eNextState = INIT;  /*Start in an init state*/ 
  
  while(1) 
  {   
      switch(eNextState)
      { 
        /* initializes the system */ 
        case INIT: 
            System_Init(); 
            if(BUTTON_PRESS == eNewEvent)
            {
               eNextState = ButtonPressHandler(INIT); 
            }  
            eNextState = GETDATA; 
        break; 
        
        /*deinitializes the system */ 
        case SLEEP: 
            System_DeInit(); 
            if(BUTTON_PRESS == eNewEvent)
            { 
               eNextState = ButtonPressHandler(SLEEP); 
            } 
        break; 
        
        /*Starts collecting data, enters forecast state when timer/get data is complete*/ 
        case GETDATA:  
            //ForecastTimerHandler(&wd); 
            //SunnyWeatherTest(&wd); 
            //FoggyWeatherTest(&wd); 
            //RainyWeatherTest(&wd); 
            SnowyWeatherTest(&wd); 
            eNextState = FORECAST;
        break; 
        
        /*Executes the forecasting algorithm */ 
        case FORECAST: 
           ForecastConditions(&wd); 
           eNextState = OUTPUTDATA;     
        break; 
        
        /*Outputs data to the console, starts over after outputting*/ 
        case OUTPUTDATA: 
           //OutputData(); 
           HAL_Delay(600000); 
           eNextState = GETDATA; 
           
        break; 
        
        /*Send Error Message to the console and deinits system*/ 
        case SYSTEMERROR: 
           ConsoleIoSendString("System Error, Going to Sleep State"); 
           eNextState = SLEEP; 
        break; 
        
      } 
        
        
  }  
             

} 





