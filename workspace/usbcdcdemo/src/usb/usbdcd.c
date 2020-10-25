#include <limits.h>
//
// Created by originou on 29/05/2020.
//

#include "usbdc.h"

#include <libopencm3/cm3/scb.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/cm3/scb.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

// True when USB configured.
static volatile bool initialized = false;

static QueueHandle_t usb_txq; // USB transmit queue
static QueueHandle_t usb_rxq; // USB receive queue

static const struct usb_device_descriptor device_descriptor = {
        .bLength = USB_DT_DEVICE_SIZE,
        .bDescriptorType = USB_DT_DEVICE,
        .bcdUSB = 0x0200,
};

static const struct usb_config_descriptor config_descriptor = {
};

static const char *usb_strings[] = {
        "usbcdc.c driver",
        "usbcdc module",
        "usbcdcdemo"
};

/*
 * USB Receive Callback.
 * */
static void cdcacm_data_rx_cb(usbd_device *usb_dev, __unused uint8_t ep) {
    // How much queue capacity left ?
    unsigned long rx_available = uxQueueSpacesAvailable(usb_rxq);
    char buf[64]; // used for rx buffer
//    int len;
//    int x;

    if (rx_available <= 0) {
        return; // No space to RX.
    }

    // Bytes to read
    unsigned long len = sizeof(buf) < rx_available ? sizeof(buf) : rx_available;

    // Read what we can, leave the rest
    len = usbd_ep_read_packet(usb_dev, 0x01, buf, len);
    for (int x = 0; x < len; ++x) {
        // Send data to the rx queue
        xQueueSend(usb_rxq, &buf[x], 0);
    }

}

static enum usbd_request_return_codes cdcam_control_request(
        usbd_device __unused *usbd_dev,
        struct usb_setup_data *req,
        uint8_t __unused **buf,
        const uint16_t *len,
        void __unused (**complete)(__unused usbd_device *usbd_dev, __unused struct usb_setup_data *req)) {

    switch (req->bRequest) {
        case USB_CDC_REQ_SET_CONTROL_LINE_STATE:
            /*
             * The linux cdc_acm driver requires this to be implemented
             * even though it's optional in the DCD spec,
             * and we don't advertise it in the ACM functional descriptor.
             *
             */
            return USBD_REQ_HANDLED;
        case USB_CDC_REQ_SET_LINE_CODING:
            if (*len < sizeof(struct usb_cdc_line_coding)) {
                return USBD_REQ_NOTSUPP;
            }
            return USBD_REQ_HANDLED;
    }
    return USBD_REQ_NOTSUPP;
}

/*
 * USB Configuration.
 * */
static void cdcacm_set_config(usbd_device *usbd_dev, __unused uint16_t wValue) {
    usbd_ep_setup(usbd_dev, 0x01, USB_ENDPOINT_ATTR_BULK, 64, cdcacm_data_rx_cb);

    usbd_ep_setup(usbd_dev, 0x82, USB_ENDPOINT_ATTR_BULK, 64, NULL);

    usbd_register_control_callback(usbd_dev, USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
                                   USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT, cdcam_control_request);
    initialized = true;
}

// Buffer to be used for control requests.
static uint8_t usbd_control_buffer[128];


void usb_start(void) {

    usbd_device *udev = 0;

    usb_txq = xQueueCreate(128, sizeof(char));
    usb_rxq = xQueueCreate(128, sizeof(char));

#if defined(STM32F1)
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USB);

#endif

    udev = usbd_init(&st_usbfs_v1_usb_driver, &device_descriptor, &config_descriptor, usb_strings,
                     sizeof(usb_strings), usbd_control_buffer, sizeof(usbd_control_buffer));

    usbd_register_set_config_callback(udev, cdcacm_set_config);

    xTaskCreate(usb_task, "USB", 200, udev, configMAX_PRIORITIES - 1, NULL);


}


void usb_task(void *arg) {
    usbd_device *udev = (usbd_device *) arg;
    char txbuf[32];
    unsigned txlen = 0;

    for (;;) {
        usbd_poll(udev);
        if (initialized) {
            while (txlen < sizeof(txbuf) && xQueueReceive(usb_txq, &txbuf[txlen], 0) == pdPASS) {
                ++txlen;
            }
            if (txlen > 0 && usbd_ep_write_packet(udev, 0x82, txbuf, txlen) != 0) {
                txlen = 0; // reset if data sent ok
            } else {
                taskYIELD() // give up CPU.
            }

        }
    }
}

int usb_getc(void) {
    char ch;
    uint32_t rc;
    rc = xQueueReceive(usb_rxq, &ch, portMAX_DELAY);
    return rc != pdPASS ? -1 : 0;
}

void usb_putc(char ch) {
    static const char cr = '\r';
    while (!usb_ready()) {
        taskYIELD();
    }
    if (ch == '\n') {
        xQueueSend(usb_txq, &cr, portMAX_DELAY);
    }
    xQueueSend(usb_txq, &ch, portMAX_DELAY);
}

bool usb_ready() {
    return initialized;
}



