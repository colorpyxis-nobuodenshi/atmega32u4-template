// #include<stdio.h>

// int main()
// {
// 	printf("application start.");
// 	while(1)
// 	{
// 	}
// 	return 0;
// }
#include <avr/io.h>
#include <util/delay.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"

#define STACK_SIZE 200
StackType_t xStack[ STACK_SIZE ];

void vTask1(void *pvParameters) 
{
    while(1)
    {
        vTaskDelay( 200 / portTICK_PERIOD_MS ); 
    }
}

void prvSetupTimerInterrupt()
{

}

void main()
{


    TaskHandle_t xHandle = NULL;
    xTaskCreate( vTask1, "Task1", STACK_SIZE, NULL, tskIDLE_PRIORITY, &xHandle );

    vTaskStartScheduler();

    while (1)
    {
        /* code */
    }
    
}
