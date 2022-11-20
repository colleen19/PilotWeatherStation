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

//Function Prototypes for State Machine 
static eState ButtonPressHandler(eState currentState); 

WeatherData wd; 

//eState currentState; 

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
        ConsoleIoSendString("Getting Pressure Data"); 
        HAL_Delay(600); 
        i++;       
    } 

} 


/**
  * @brief starts the state machine 
  * 
  */
void executeStateMachine(void)
{ 
  eState eNextState = INIT;  /*Start in an init state*/ 
  eEvent eNewEvent; 
  
  while(1) 
  {   
      ConsoleIoSendString("In SM"); 
      switch(eNextState)
      { 
        /* initializes the system */ 
        case INIT: 
            //System_Init(); 
            //if(BUTTON_PRESS == eNewEvent)
            //{
             //  eNextState = ButtonPressHandler(INIT); 
            //}  
            
            eNextState = GETDATA; 
        break; 
        
        /*deinitializes the system */ 
        case SLEEP: 
            //System_DeInit(); 
            if(BUTTON_PRESS == eNewEvent)
            { 
               eNextState = ButtonPressHandler(SLEEP); 
            } 
        break; 
        
        /*Starts collecting data, enters forecast state when enough timer is complete*/ 
        case GETDATA:  
            ConsoleIoSendString("Getting Data"); 
            ForecastTimerHandler(&wd);  
            eNextState = FORECAST;
        break; 
        
        /*Executes the forecasting algorithm */ 
        case FORECAST: 
          ConsoleIoSendString("Forecasting"); 
           ForecastConditions(&wd); 
           eNextState = OUTPUTDATA;     
        break; 
        
        /*Outputs data to the console, starts over after outputting*/ 
        case OUTPUTDATA: 
           //OutputData(); 
           eNextState = GETDATA; 
         
        break; 
        
        /*Send Error Message to the console and deinits system*/ 
        case SYSTEMERROR: 
           ConsoleIoSendString("SYSTEM ERROR"); 
           eNextState = SLEEP; 
        break; 
        
      } 
        
        
  }  
             

} 





