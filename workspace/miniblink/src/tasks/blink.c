//
// Created by originou on 24/05/2020.
//

#include "blink.h"

#include <FreeRTOS.h>
#include <task.h>

#include <libopencm3/stm32/gpio.h>


void blink_led(void *args __attribute((unused))) {
    for (;;) {
        gpio_toggle(GPIOC, GPIO13);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
