// led_control.c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"

led_strip_handle_t configure_led(void)
{
    // LED strip general initialization, according to your led board design
    led_strip_config_t strip_config = {
        .strip_gpio_num = 8,   // The GPIO that connected to the LED strip's data line
        .max_leds = 1,        // The number of LEDs in the strip,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
        .led_model = LED_MODEL_WS2812,            // LED strip model
        .flags.invert_out = false,                // whether to invert the output signal
    };

    // LED strip backend configuration: RMT
    led_strip_rmt_config_t rmt_config = {
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
        .rmt_channel = 0,
#else
        .clk_src = RMT_CLK_SRC_DEFAULT,        // different clock source can lead to different power consumption
        .resolution_hz = 10 * 1000 * 1000, // RMT counter clock frequency
        .flags.with_dma = false,               // DMA feature is available on ESP target like ESP32-S3
#endif
    };

    // LED Strip object handle
    led_strip_handle_t led_strip;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    return led_strip;
}


void led_on(led_strip_handle_t led_strip, uint8_t r, uint8_t g, uint8_t b)
{
    led_strip_set_pixel(led_strip, 0, r, g, b);
    led_strip_refresh(led_strip);
    printf("LED On\n");
}

void led_off(led_strip_handle_t led_strip)
{
    led_strip_clear(led_strip);
    printf("LED Off\n");
}

// Fonction principale de gestion du cycle LED
void led_cycle(led_strip_handle_t led_strip)
{
    for(int i = 1; i < 6; i++){
        led_on(led_strip, 0, 0, 40);
        vTaskDelay(pdMS_TO_TICKS(500));
        led_off(led_strip);
        vTaskDelay(pdMS_TO_TICKS(50));

        led_on(led_strip, 40, 40, 40);
        vTaskDelay(pdMS_TO_TICKS(500));
        led_off(led_strip);
        vTaskDelay(pdMS_TO_TICKS(50));

        led_strip_set_pixel(led_strip, 0, 40, 0, 0);
        led_strip_refresh(led_strip);
        printf("LED On final\n");
        vTaskDelay(pdMS_TO_TICKS(500));
        led_strip_clear(led_strip);
        printf("LED Off final\n");
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
