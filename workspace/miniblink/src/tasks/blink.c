//
// Created by originou on 24/05/2020.
//

#include "blink.h"

#include <FreeRTOS.h>
#include <task.h>

#include <libopencm3/stm32/gpio.h>


_Noreturn void blink_led(void *args __attribute((unused))) {
    for (;;) {
#if defined(STM32F1)
        gpio_toggle(GPIOC, GPIO13);
#else
        gpio_toggle(GPIOA, GPIO6);
#endif
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
