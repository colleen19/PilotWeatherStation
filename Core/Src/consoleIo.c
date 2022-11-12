// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.


#include "consoleIo.h"
#include "usart.h"
#include <stdio.h> 
#include <stdint.h> 


eConsoleError ConsoleIoInit(void) 
{
	return CONSOLE_SUCCESS;
}

// This is modified for the Wokwi RPi Pico simulator. It works fine 
// but that's partially because the serial terminal sends all of the 
// characters at a time without losing any of them. What if this function
// wasn't called fast enough?
eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{
	char ch;
	uint32_t i = 0;

        HAL_UART_Receive(&huart1, &ch, 1, 1);
        
	while (( i < bufferLength))
	{
		if (ch != '\0') {
			buffer[i] = (uint8_t) ch;
			i++;
			if (ch == '\r') {
				HAL_UART_Receive(&huart1, &ch, 1, 1);
			    break;
			}
			ch = '\0';
		}
		HAL_UART_Receive(&huart1, &ch, 1, 1);
	}
	*readLength = i;
	buffer[*readLength] = '\0';
	return CONSOLE_SUCCESS;
} 

eConsoleError ConsoleIoSendString(const char *buffer)
{
	HAL_UART_Transmit(&huart1, (unsigned char*) buffer, strlen(buffer), HAL_MAX_DELAY); 
	return CONSOLE_SUCCESS;
}

