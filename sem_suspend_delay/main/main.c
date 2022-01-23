#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/semphr.h>

BaseType_t result;
TaskHandle_t sendtask,recvtask;

void send(void *pv)
{
	int send_data=0;

	while(1)
	{
		send_data++;

		if(send_data%10==0)
		{
			vTaskResume(recvtask);
			printf("Sem Release\n");
		}

		printf("Sensor Task: %d\n",send_data);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void receive(void *pv)
{
	while(1)
	{
		vTaskSuspend(NULL);
		printf("Data received\n");
		vTaskDelay(1500/portTICK_PERIOD_MS);
	}
}

int app_main()
{
	result=xTaskCreate(send,"Send",2048,NULL,4,&sendtask);
	if(result!=pdPASS)
	{
		printf("Task Send Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(receive,"Receive",2048,NULL,4,&recvtask);
	if(result!=pdPASS)
	{
		printf("Task Receive Creation Failed\n");
		return 0;
	}
	
	return 0;
}
