//
// Created by originou on 24/05/2020.
//

#include <limits.h>

#include <FreeRTOS.h>
#include <task.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

void blink_led_(void *args __attribute((unused))) {
    for (;;) {
        gpio_toggle(GPIOC, GPIO13);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void setup();
void config_usart();
_Noreturn void task_1(void __unused *args);
static inline void uart_putc(char ch);

extern void vApplicationStackOverflowHook(xTaskHandle __unused *pxTask, __unused signed portCHAR *pcTaskName);

void vApplicationStackOverflowHook(xTaskHandle __unused *pxTask, __unused signed portCHAR *pcTaskName) {
for (;;) {}
}

_Noreturn int main(void) {
    setup();
    // xTaskCreate(blink_led_, "LED", 100, NULL, configMAX_PRIORITIES - 1, NULL);
	xTaskCreate(task_1, "task_1", 100, NULL, configMAX_PRIORITIES - 1, NULL);
	vTaskStartScheduler();
	for(;;);
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

	usart_set_baudrate(USART1, 38400);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX_RX);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
	usart_enable(USART1);
}

_Noreturn void task_1(void __unused *args) {
	int c = '0' - 1;

	for(;;) {
		gpio_toggle(GPIOC, GPIO13);
		vTaskDelay(pdMS_TO_TICKS(200));
		if (++c >= 'Z') {
			uart_putc(c);
			uart_putc('\r');
			uart_putc('\n');
			c = '0' - 1;
		} else {
			uart_putc(c);
		}
	}
}

static inline void uart_putc(char ch) {
	usart_send_blocking(USART1, ch);
}

