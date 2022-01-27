//Question_20

#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_intr_alloc.h>
#include<freertos/semphr.h>

TaskHandle_t main_task,isr_task;
esp_err_t intr_result;
intr_handle_t isr;
intr_handler_t isr_handler;
SemaphoreHandle_t sem;

void task(void *pv)
{
	bool gpio_state;

 	while(1)
	{  
		gpio_set_level(13,0);
		gpio_state=gpio_get_level(14);
		printf("Main Task\nPin State: %d\n",gpio_state);
		vTaskDelay(1000/portTICK_PERIOD_MS);
 	}
}

void int_task(void *pv)
{
	xSemaphoreTake(sem,portMAX_DELAY);
	gpio_set_level(13,1);	
	vTaskDelay(1000/portTICK_PERIOD_MS);
}

void IRAM_ATTR intr(void *pv)
{
 	xSemaphoreGiveFromISR(sem,pdFALSE);
}


int app_main()
{
	BaseType_t result;

	sem=xSemaphoreCreateBinary();
	if(sem==NULL)
	{
		perror("Error creating Binary Semaphore");
		return 0;
	}

    gpio_reset_pin(14);
	gpio_reset_pin(13);
  	gpio_set_direction(14, GPIO_MODE_INPUT);
	gpio_set_direction(13, GPIO_MODE_OUTPUT);
	gpio_intr_enable(14);
	
  	gpio_set_intr_type(14, GPIO_INTR_LOW_LEVEL);
	if(intr_result!=ESP_OK)
	{
		perror("Interrupt type");
		return 0;
	}  

	gpio_install_isr_service(ESP_INTR_FLAG_EDGE); //ESP_INTR_FLAG_EDGE
	if(intr_result!=ESP_OK)
	{
		perror("Interrupt service");
		return 0;
	}

  	gpio_isr_handler_add(14, int_task, NULL);
	if(intr_result!=ESP_OK)
	{
		perror("Interrupt not enabled");
		return 0;
	}

	result=xTaskCreate(task, "task", 4096, NULL , 5, &main_task);
	if(result!=pdTRUE)
	{
		perror("Main Task not created");
		return 0;
	}
	
	result=xTaskCreate(int_task, "interrupt_task", 4096, NULL , 6, &isr_task);
	if(result!=pdTRUE)
	{
		perror("Interrupt Task not created");
		return 0;
	}

	vTaskStartScheduler();
//	vTaskEndScheduler();

	//xSemaphoreTake(sem,portMAX_DELAY);
	return 0;
}

