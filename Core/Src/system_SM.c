/**
 ******************************************************************************
 * @file    system_SM.c
 * @author  Colleen Staeger 
 * @brief   This file contains the State Machine for the System 
 ******************************************************************************
 */ 
#include <stdio.h> 

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


/**
  * @brief handler for button press event 
  * 
  */
eState ButtonPressHandler(eCurrentState)
{ 
    if (eCurrentState == INIT) 
    { 
      return SLEEP; 
    }
    else if (eCurrentState == SLEEP) 
    { 
      return ACTIVE; 
    } 
    
} 

/**
  * @brief handler for the 20 min forecast timer event 
  * 
  */
eState ForecastTimerHandler(void) 
{ 
 
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
      eSystemEvent eNewEvent = ReadEvent(); //TODO: fix this 
      
      switch(eNextState)
      { 
        /* initializes the system */ 
        case INIT: 
        { 
            System_Init(); 
            if(BUTTON_PRESS == eNewEvent)
            {
               eNextState = ButtonPressHandler(INIT); 
            } 
        } 
        break; 
        /*deinitializes the system */ 
        case SLEEP: 
        { 
            System_DeInit(); 
            if(BUTTON_PRESS == eNewEvent)
            { 
               eNextState = ButtonPressHandler(SLEEP); 
            } 
        } 
        break; 
        /*Starts collecting data, enters forecast state when enough data has been collected*/ 
        case GETDATA: 
        { 
            System_DATA 

} 





