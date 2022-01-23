/* Question 4,5,11
Task with higher priority gets executed first
*/

#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

BaseType_t result;

void task1(void *pv)
{
	printf("Task 1\n");
	vTaskDelete(NULL); //API for deleting Task
}

void task2(void *pv)
{
	printf("Task 2\n");
	vTaskDelete(NULL); //API for deleting Task
}

int app_main()
{
	int i=0,p1=10,p2=20,k;

	while(i<2)
	{
		result=xTaskCreate(task1,"Task 1",2048,NULL,p1,NULL);
		if(result!=pdPASS)
		{
			printf("Task 1 Creation Failed\n");
			return 0;
		}
	
		result=xTaskCreate(task2,"Task 2",2048,NULL,p2,NULL);
		if(result!=pdPASS)
		{
			printf("Task 2 Creation Failed\n");
			return 0;
		}

		k=p1;
		p1=p2;
		p2=k;
		i++;
	}

	return 0;
}
