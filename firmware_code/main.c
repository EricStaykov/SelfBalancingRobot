#define F_CPU									20000000UL

#define COMPLEMENTARY_FILTER_GYRO_GAIN			0.98
#define COMPLEMENTARY_FILTER_ACCEL_GAIN			0.02
#define OFFSET_ITERATIONS_INT					100
#define OFFSET_ITERATIONS_FLOAT					100.0
#define PID_KP									25.5
#define PID_KI									200.0
#define PID_KD									0.0
#define PID_OFFSET								50.0

#include <avr/interrupt.h>
#include <avr/io.h>
#include <ctype.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <util/twi.h>
#include "i2c.h"
#include "mpu6050.h"
#include "usart.h"
#include "l298n.h"
#include "led.h"
#include "general_timer.h"

float accelXOffset = 0, gyroYOffset = 0, currentAngle = 0, previousAngle = 0, integralAngle = 0;

void get_offsets(void) {
	for (uint16_t iteration = 0; iteration < OFFSET_ITERATIONS_INT; iteration++) {
		collect_data_mpu();
		_delay_ms(LOOP_DELAY_MS);
	}
	for (uint16_t iteration = 0; iteration < OFFSET_ITERATIONS_INT; iteration++) {
		collect_data_mpu();
		accelXOffset += accelX;
		gyroYOffset += gyroY;
		_delay_ms(LOOP_DELAY_MS);
	}
	accelXOffset /= OFFSET_ITERATIONS_FLOAT;
	gyroYOffset /= OFFSET_ITERATIONS_FLOAT;
}

int main(void) {
	_delay_ms(5000);
	init_leds();
	init_motor_data();
	configure_mpu();
	usart_init();
	get_offsets();
	init_general_timer();
	sei();
	while (1);
	return 1;
}

ISR(TIMER1_COMPA_vect) {
	cli();
	collect_data_mpu();
	float rotationalSpeed = -(gyroY - gyroYOffset) / GYROSCOPE_SENSITIVITY;
	currentAngle = COMPLEMENTARY_FILTER_GYRO_GAIN * (currentAngle + (rotationalSpeed * LOOP_DELAY_SEC)) + COMPLEMENTARY_FILTER_ACCEL_GAIN * (((accelX - accelXOffset) / ACCELEROMETER_SENSITIVITY) * 180.0 / M_PI);
	integralAngle += currentAngle * LOOP_DELAY_SEC;
	float derivativeAngle = (currentAngle - previousAngle) / LOOP_DELAY_SEC;
	float outputPID = PID_KP * currentAngle + PID_KI * integralAngle + PID_KD * derivativeAngle;
	previousAngle = currentAngle;
	if (outputPID < 0) {
		motor_set_direction(MOTOR_DIRECTION_FORWARD);
		set_led_green_state(LED_STATE_ON);
		set_led_red_state(LED_STATE_OFF);
	} else {
		motor_set_direction(MOTOR_DIRECTION_BACKWARD);
		set_led_red_state(LED_STATE_ON);
		set_led_green_state(LED_STATE_OFF);
	}
	outputPID = (outputPID < 0) ? (outputPID * -1) : outputPID;
	outputPID += PID_OFFSET;
	outputPID = (outputPID > 255) ? 255 : outputPID;
	motor_set_speed((uint8_t)outputPID);
	sei();
}