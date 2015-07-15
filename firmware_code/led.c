#include <avr/io.h>
#include "led.h"

void init_leds(void) {
	LED_GREEN_DDR |= LED_GREEN_PIN;
	LED_GREEN_PORT_OUT |= LED_GREEN_PIN;
	LED_RED_DDR |= LED_RED_PIN;
	LED_RED_PORT_OUT |= LED_RED_PIN;
}

void set_led_green_state(uint8_t state) {
	if (state == LED_STATE_ON) {
		LED_GREEN_PORT_OUT |= LED_GREEN_PIN;
	} else if (state == LED_STATE_OFF) {
		LED_GREEN_PORT_OUT &= ~LED_GREEN_PIN;
	}
}

void set_led_red_state(uint8_t state) {
	if (state == LED_STATE_ON) {
		LED_RED_PORT_OUT |= LED_RED_PIN;
	} else if (state == LED_STATE_OFF) {
		LED_RED_PORT_OUT &= ~LED_RED_PIN;
	}
}