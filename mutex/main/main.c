//	Question 22

#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/semphr.h>

BaseType_t result;
SemaphoreHandle_t sem;
int count=0;

void receive(void *pv)
{
	while(1)
	{
		
		xSemaphoreTake(sem,portMAX_DELAY);
		xSemaphoreTake(sem,portMAX_DELAY); //if uncommented rest of task will not be executed
		count=uxSemaphoreGetCount(sem);
		printf("Received Count: %d\n",count);
		vTaskDelay(1000/portTICK_PERIOD_MS);
		
	}
}

void send(void *pv)
{
	while(1)
	{
		xSemaphoreGive(sem);
		count=uxSemaphoreGetCount(sem);
		printf("Sent Count: %d\n",count);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

int app_main()
{
	sem=xSemaphoreCreateMutex();

	if(sem==NULL)
		printf("Semaphore not created\n");
	
	result=xTaskCreate(send,"Send",2048,NULL,5,NULL);
	if(result!=pdPASS)
	{
		printf("Task Send Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(receive,"Receive",2048,NULL,5,NULL);
	if(result!=pdPASS)
	{
		printf("Task Receive Creation Failed\n");
		return 0;
	}
	
	return 0;
}
