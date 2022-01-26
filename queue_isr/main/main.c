//Question_22

#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_intr_alloc.h>
#include<freertos/queue.h>

TaskHandle_t main_task,isr_task;
esp_err_t intr_result;
intr_handle_t isr;
intr_handler_t isr_handler;
QueueHandle_t queue;

void task(void *pv)
{
	uint32_t data=0;

 	while(1)
	{  
		data=0;
		gpio_set_level(13,0);
		printf("Main Task\nPin State: %d\n",gpio_get_level(14));
		vTaskDelay(1000/portTICK_PERIOD_MS);
		xQueueReceiveFromISR(queue,&data,pdFALSE);
		printf("Data: %d\n",data);
		vTaskDelay(10/portTICK_PERIOD_MS);
 	}
}

void int_task(void *pv)
{
	vTaskSuspend(NULL);
	uint32_t intr_data=0;
	intr_data++;
	xQueueSendFromISR(queue,&intr_data,pdFALSE);
	gpio_set_level(13,1);	
	vTaskDelay(1000/portTICK_PERIOD_MS);
}

void IRAM_ATTR intr(void *pv)
{
 	xTaskResumeFromISR(isr_task);
}


int app_main()
{
	BaseType_t result;

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

	queue=xQueueCreate(1,sizeof(bool));
	
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
	return 0;
}

