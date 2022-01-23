#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

TaskHandle_t xHandleTasklog;

void tasklog(void *pvParameters)
{

	printf("Tasklog created\n");
	vTaskDelete(xHandleTasklog);
}

void app_main()
{
	BaseType_t result;
	result=xTaskCreate(tasklog,"TaskLog",1024,NULL,5,&xHandleTasklog);

	if(result!=pdPASS)
		printf("Task Creation Failed\n");
}
