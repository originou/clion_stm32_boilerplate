//
// Created by originou on 29/05/2020.
//


#include <libopencm3/usb/usbd.h>

void usb_start(void);

static void cdcacm_set_config(usbd_device *usbd_dev, __unused uint16_t wValue);

static void cdcacm_data_rx_cb(usbd_device *usb_dev, __unused uint8_t ep);

int usb_getc(void);

void usb_putc(char ch);

bool usb_ready();

_Noreturn static void usb_task(void *arg);
