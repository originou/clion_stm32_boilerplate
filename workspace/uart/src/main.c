//
// Created by originou on 24/05/2020.
//

#include <limits.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

static QueueHandle_t uart_txq; // TX Queue for UART

void setup();
void config_usart();
//_Noreturn void task_1(void __unused *args);
static inline void uart_putc(char ch);
static void uart_puts(const char *s);
_Noreturn static void uart_task(void __unused *args);
_Noreturn static void demo_task(void __unused *args);

extern void vApplicationStackOverflowHook(xTaskHandle __unused *pxTask, __unused signed portCHAR *pcTaskName);

void vApplicationStackOverflowHook(xTaskHandle __unused *pxTask, __unused signed portCHAR *pcTaskName) {
for (;;) {}
}

int main(void) {
    setup();
    // xTaskCreate(blink_led_, "LED", 100, NULL, configMAX_PRIORITIES - 1, NULL);
	xTaskCreate(uart_task, "uart_task", 100, NULL, configMAX_PRIORITIES - 1, NULL);
	xTaskCreate(demo_task, "demo_task", 100, NULL, configMAX_PRIORITIES - 2, NULL);
	vTaskStartScheduler();
	for(;;);
	return 0;
}

void setup() {
#if defined(STM32F1)
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

	config_usart();


#elif defined(STM32F4)
    // HELLO
#endif
}

void config_usart() {
	// UART TX ON PA9 (GPIO_USART1_TX)
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_USART1);

	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);

	usart_set_baudrate(USART1, 115200);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX_RX);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
	usart_enable(USART1);

	uart_txq = xQueueCreate(256, sizeof(char));
}

_Noreturn static void uart_task(void __unused *args) {
	char ch;
	for(;;) {
		// Receive char to TX from queue
		if(xQueueReceive(uart_txq, &ch, 500) == pdPASS) {
			while(!usart_get_flag(USART1, USART_SR_TXE)) {
				taskYIELD(); // while usart tx is not empty, render CPU charge to others tasks.
			}
			usart_send(USART1, ch);
		}
		gpio_toggle(GPIOC, GPIO13);
	}
}

_Noreturn static void demo_task(void __unused *args) {
	for(;;) {
		uart_puts("Now this is a message \n");
		uart_puts("  sent via FreeRTOS queues. youhou\n");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

static void uart_puts(const char *s) {
	for(; *s; ++s) {
		xQueueSend(uart_txq, s, portMAX_DELAY); // blocks when queue is full
	}
}

/* _Noreturn void task_1(void __unused *args) { */
/* 	int c = '0' - 1; */
/*  */
/* 	for(;;) { */
/* 		gpio_toggle(GPIOC, GPIO13); */
/* 		vTaskDelay(pdMS_TO_TICKS(200)); */
/* 		if (++c >= 'Z') { */
/* 			uart_putc(c); */
/* 			uart_putc('\r'); */
/* 			uart_putc('\n'); */
/* 			c = '0' - 1; */
/* 		} else { */
/* 			uart_putc(c); */
/* 		} */
/* 	} */
/* } */

static inline void uart_putc(char ch) {
	usart_send_blocking(USART1, ch);
}

