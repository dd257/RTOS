#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_intr_alloc.h>

TaskHandle_t main_task,isr_task;
esp_err_t intr_result;
intr_handle_t isr;
intr_handler_t isr_handler;

void task(void *pv)
{
 	while(1)
	{  
		gpio_set_level(13,0);
		printf("Main Task\nPin State: %d\n",gpio_get_level(12));
		vTaskDelay(1000/portTICK_PERIOD_MS);
 	}
}

void int_task(void *pv)
{
 	//while(1)
	// {  
		vTaskSuspend(isr_task);
		gpio_set_level(13,1);	
		vTaskDelay(1000/portTICK_PERIOD_MS);
 	//}
}

void IRAM_ATTR intr(void *pv)
//void intr(void *pv)
{
 	xTaskResumeFromISR(isr_task);
}

int app_main()
{
   
    gpio_reset_pin(12);
	gpio_reset_pin(13);
  	gpio_set_direction(12, GPIO_MODE_INPUT);
	gpio_set_direction(13, GPIO_MODE_OUTPUT);
	gpio_intr_enable(12);
	
  	gpio_set_intr_type(12, GPIO_INTR_LOW_LEVEL);
	if(intr_result!=ESP_OK)
	{
		perror("Interrupt type");
		return 0;
	}  

	gpio_install_isr_service(ESP_INTR_FLAG_IRAM);
	if(intr_result!=ESP_OK)
	{
		perror("Interrupt service");
		return 0;
	}

  	gpio_isr_handler_add(12, int_task, NULL);
	if(intr_result!=ESP_OK)
	{
		perror("Interrupt not enabled");
		return 0;
	}

	xTaskCreate(task, "task", 4096, NULL , 10, &main_task);
	xTaskCreate(int_task, "int_task", 4096, NULL , 10, &isr_task);
	vTaskStartScheduler();

	return 0;
}

