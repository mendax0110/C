/*rasperry pi pico host cdc msc hid*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bsp/board.h"
#include "tusb.h"

/*macro constant typedef protypes*/
void led_blinking_task(void);

extern void cdc_task(void);
extern void hid_app_task(void);

/*main part of the programm*/
int main(void)
{
    board_init();
    printf("TinyUSB Host CDC MSC HID Example\r\n");
    tusb_init();

    while(1)
    {
        /*tinyusb host task*/
        tuh_task();
        led_blinking_task();

        #if CFG_TUH_CDC
            cdc_task();
        #endif

        #if CFG_TUH_HID
            hid_app_task();
        #endif  
    }
    
    return 0;
}

/*usb CDC*/
#if CFG_TUH_CDC
CFG_TUSB_MEM_SECTION static char serial_in_buffer[64] = {0};

void tuh_mount_cb(uint8_t dev_addr)
{
    /*application setup*/
    printf("A device with address %d is mounted\r\n", dev_addr);
    tuh_cdc_receive(dev_addr, serial_in_buffer, sizeof(serial_in_buffer), true); /*schedule first transfer*/
}

void tuh_unmount_cb(uint8_t dev_addr)
{
    /*application tear-down*/
    printf("A device with address %d is unmounted\r\n", dev_addr);
}

/*invoked ISR context*/
void tuh_cdc_xfer_isr(uint8_t dev_addr, cfer_result_t event, cdc_pipeid_t pipe_id, uint32_t xferred_bytes)
{
    (void) event;
    (void) pipe_id;
    (void) xferred_bytes;

    printf(serial_in_buffer);
    tu_memclr(serial_in_buffer, sizeof(serial_in_buffer));
    tuh_cdc_receive(dev_addr, serial_in_buffer, sizeof(serial_in_buffer), true); /*waiting for the new data*/
}

void cdc_task(void)
{

}

#endif

/*tinyusb callbacks and blinking tasks*/
void led_blinking_task(void)
{
    const uint32_t interval_ms = 1000;
    static uint32_t start_ms = 0;

    static bool led_state = false;

    /*blink every interval ms*/
    if(board_millis() - start_ms < interval_ms) return; /*not enough time*/
    start_ms += interval_ms;

    board_led_write(led_state);
    led_state = 1 - led_state; /*toggle*/
}
