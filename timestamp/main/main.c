// Question 3

#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/timers.h>

BaseType_t result;
TickType_t timestamp;

void task1(void *pv)
{
	while(1)
	{
		
		printf("Task 1 Timestamp: %dms\n",xTaskGetTickCount()*portTICK_PERIOD_MS-timestamp);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task2(void *pv)
{
	while(1)
	{
		
		printf("Task 2 Timestamp: %dms\n",xTaskGetTickCount()*portTICK_PERIOD_MS-timestamp);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task3(void *pv)
{
	while(1)
	{
		
		printf("Task 3 Timestamp: %dms\n",xTaskGetTickCount()*portTICK_PERIOD_MS-timestamp);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task4(void *pv)
{
	while(1)
	{
		
		printf("Task 4 Timestamp: %dms\n",xTaskGetTickCount()*portTICK_PERIOD_MS-timestamp);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task5(void *pv)
{
	while(1)
	{
		
		printf("Task 5 Timestamp: %dms\n",xTaskGetTickCount()*portTICK_PERIOD_MS-timestamp);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task6(void *pv)
{
	while(1)
	{
		
		printf("Task 6 Timestamp: %dms\n",xTaskGetTickCount()*portTICK_PERIOD_MS-timestamp);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task7(void *pv)
{
	while(1)
	{
		
		printf("Task 7 Timestamp: %dms\n",xTaskGetTickCount()*portTICK_PERIOD_MS-timestamp);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task8(void *pv)
{
	while(1)
	{
		
		printf("Task 8 Timestamp: %dms\n",xTaskGetTickCount()*portTICK_PERIOD_MS-timestamp);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task9(void *pv)
{
	while(1)
	{
		
		printf("Task 9 Timestamp: %dms\n",xTaskGetTickCount()*portTICK_PERIOD_MS-timestamp);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task10(void *pv)
{
	while(1)
	{
		
		printf("Task 10 Timestamp: %dms\n",xTaskGetTickCount()*portTICK_PERIOD_MS-timestamp);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

int app_main()
{
	timestamp=xTaskGetTickCount()*portTICK_PERIOD_MS;

	result=xTaskCreate(task1,"Task 1",2048,NULL,4,NULL);
	if(result!=pdPASS)
	{
		printf("Task 1 Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(task2,"Task 2",2048,NULL,5,NULL);
	if(result!=pdPASS)
	{
		printf("Task 2 Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(task3,"Task 3",2048,NULL,6,NULL);
	if(result!=pdPASS)
	{
		printf("Task 3 Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(task4,"Task 4",2048,NULL,7,NULL);
	if(result!=pdPASS)
	{
		printf("Task 4 Creation Failed\n");
		return 0;
	}
	
	result=xTaskCreate(task5,"Task 5",2048,NULL,8,NULL);
	if(result!=pdPASS)
	{
		printf("Task 5 Creation Failed\n");
		return 0;
	}

	
	result=xTaskCreate(task6,"Task 6",2048,NULL,9,NULL);
	if(result!=pdPASS)
	{
		printf("Task 6 Creation Failed\n");
		return 0;
	}
	
	result=xTaskCreate(task7,"Task 7",2048,NULL,10,NULL);
	if(result!=pdPASS)
	{
		printf("Task 7 Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(task8,"Task 8",2048,NULL,11,NULL);
	if(result!=pdPASS)
	{
		printf("Task 8 Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(task9,"Task 9",2048,NULL,12,NULL);
	if(result!=pdPASS)
	{
		printf("Task 9 Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(task10,"Task 10",2048,NULL,13,NULL);
	if(result!=pdPASS)
	{
		printf("Task 10 Creation Failed\n");
		return 0;
	}

	return 0;
}
