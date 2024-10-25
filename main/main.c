#include "led_control.h"

void app_main(void)
{
    led_strip_handle_t led_strip = configure_led();
    led_cycle(led_strip);
}
