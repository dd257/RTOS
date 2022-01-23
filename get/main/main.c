#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<driver/gpio.h>

BaseType_t result;

void tasklog(void *pv)
{
	while(1)
	{
		printf("Sensor Task\n");
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void blink(void *pv)
{
	esp_rom_gpio_pad_select_gpio(2);
	gpio_set_direction(2,GPIO_MODE_OUTPUT);

	while(1)
	{
		gpio_set_level(2,1);
		vTaskDelay(1500/portTICK_PERIOD_MS);
		gpio_set_level(2,0);
		vTaskDelay(1500/portTICK_PERIOD_MS);
		printf("Stack High Water Mark: %d\nTask Affinity: %d\n",uxTaskGetStackHighWaterMark(NULL),xTaskGetAffinity(NULL));
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
