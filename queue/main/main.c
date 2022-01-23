/*	Question 18
	Data sent from task "send" to "receive" only when set_value is divisible by 5
*/

#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/queue.h>

BaseType_t result;
QueueHandle_t queue;

void send(void *pv)
{
	int set_value=0;

	while(1)
	{
		set_value++;
		printf("Sending data: %d\n",set_value);

		if(set_value%5==0)
			xQueueSend(queue,&set_value,portMAX_DELAY);

		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void receive(void *pv)
{
	int sensor_data;
	while(1)
	{
		xQueueReceive(queue,&sensor_data,portMAX_DELAY);
		printf("Received Data: %d\n",sensor_data);
		//vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

int app_main()
{
	queue=xQueueCreate(5,sizeof(int));

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
