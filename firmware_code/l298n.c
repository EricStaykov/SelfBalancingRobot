#include <avr/io.h>
#include "l298n.h"

void init_motor_data(void) {
	MOTOR_DATA_DDR |= (MOTOR_DATA_PIN_1 | MOTOR_DATA_PIN_2 | MOTOR_DATA_ENABLE);
	MOTOR_DATA_PORT_OUT &= ~(MOTOR_DATA_PIN_1 | MOTOR_DATA_PIN_2 | MOTOR_DATA_ENABLE);
	// PWM for the enable pins
	TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << CS01) | (1 << CS00);
	MOTOR_DATA_PWM_VALUE = 0;
}

void motor_set_direction(uint8_t direction) {
	if (direction == MOTOR_DIRECTION_FORWARD) {
		MOTOR_DATA_PORT_OUT = (MOTOR_DATA_PORT_OUT & ~MOTOR_DATA_PIN_1) | MOTOR_DATA_PIN_2;
	} else if (direction == MOTOR_DIRECTION_BACKWARD) {
		MOTOR_DATA_PORT_OUT = (MOTOR_DATA_PORT_OUT & ~MOTOR_DATA_PIN_2) | MOTOR_DATA_PIN_1;
	}
}

void motor_set_speed(uint8_t speed) {
	MOTOR_DATA_PWM_VALUE = speed;
}