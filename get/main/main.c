/* Question 1 & 2
Displaying Task priority and range of priority
Periodic Task of 500ms - setting and restting GPIO pin 2
Periodic Task of 1000ms - displaying information about Task
*/

#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<driver/gpio.h>

BaseType_t result;

void tasklog(void *pv)
{
	printf("Sensor Task\n");
	vTaskDelete(NULL);
}

void blink(void *pv)
{
	esp_rom_gpio_pad_select_gpio(2);
	gpio_set_direction(2,GPIO_MODE_OUTPUT);

	while(1)
	{
		gpio_set_level(2,1);
		vTaskDelay(500/portTICK_PERIOD_MS); 
		gpio_set_level(2,0);
		vTaskDelay(500/portTICK_PERIOD_MS);
		printf("\nStack High Water Mark: %d\nTask Affinity: %d\nTask Priority: %d\nMax Priority: %d\n",uxTaskGetStackHighWaterMark(NULL),xTaskGetAffinity(NULL),uxTaskPriorityGet(NULL),configMAX_PRIORITIES);
	}
}

int app_main()
{
	result=xTaskCreate(tasklog,"Tasklog",2048,NULL,4,NULL);
	if(result!=pdPASS)
	{
		printf("Task Log Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(blink,"Blink",2048,NULL,4,NULL);
	if(result!=pdPASS)
	{
		printf("Task Blink Creation Failed\n");
		return 0;
	}
	
	return 0;
}
