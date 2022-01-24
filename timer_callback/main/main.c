/* Question 2
*/

#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/timers.h>

TimerHandle_t result;

void task()
{
	printf("Periodic function turned on\n");
}

int app_main()
{
	result=xTimerCreate("Task",pdMS_TO_TICKS(5000),pdTRUE,NULL,task);
	xTimerStart(result,0);

	if(result==NULL)
	{
		printf("Timer Task Creation Failed\n");
		return 0;
	}

	while(1)
	{
		printf("Periodic function turned off\n");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
	
	return 0;
}
