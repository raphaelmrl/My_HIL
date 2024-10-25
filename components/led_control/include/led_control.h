#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "led_strip.h"
#include <stdint.h>

// Fonction pour configurer la bande de LEDs
led_strip_handle_t configure_led(void);

// Fonction pour allumer la LED avec des valeurs RGB spécifiques
void led_on(led_strip_handle_t led_strip, uint8_t r, uint8_t g, uint8_t b);

// Fonction pour éteindre la LED
void led_off(led_strip_handle_t led_strip);

// Fonction pour exécuter le cycle d'allumage/extinction
void led_cycle(led_strip_handle_t led_strip);

#endif // LED_CONTROL_H