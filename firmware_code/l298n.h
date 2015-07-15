#define MOTOR_DATA_DDR							DDRD
#define MOTOR_DATA_PORT_OUT						PORTD
#define MOTOR_DATA_PIN_1						0x04
#define MOTOR_DATA_PIN_2						0x08
#define MOTOR_DATA_ENABLE						0x40
#define MOTOR_DATA_PWM_VALUE					OCR0A
#define MOTOR_DIRECTION_FORWARD					0
#define MOTOR_DIRECTION_BACKWARD				1

void init_motor_data(void);
void motor_set_direction(uint8_t direction);
void motor_set_speed(uint8_t speed);