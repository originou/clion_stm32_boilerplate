//
// Created by originou on 23/05/2020.
//
#include <limits.h>

#include <FreeRTOS.h>
#include <task.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "tasks/blink.h"

void setup();

extern void vApplicationStackOverflowHook(xTaskHandle __unused *pxTask, __unused signed portCHAR *pcTaskName);

void vApplicationStackOverflowHook(xTaskHandle __unused *pxTask, __unused signed portCHAR *pcTaskName) {
    for (;;) {}
}

int main(void) {
    setup();
    xTaskCreate(blink_led, "LED", 100, NULL, configMAX_PRIORITIES - 1, NULL);

    vTaskStartScheduler();
    for (;;) {}

    return 0; // should never trigger
}

void setup() {
#if defined(STM32F1)
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);


#elif defined(STM32F4)
    // HELLO
#endif
}

