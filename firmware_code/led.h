#define LED_GREEN_DDR							DDRB
#define LED_GREEN_PORT_OUT						PORTB
#define LED_GREEN_PIN							0x01
#define LED_RED_DDR								DDRD
#define LED_RED_PORT_OUT						PORTD
#define LED_RED_PIN								0x80
#define LED_STATE_ON							0
#define LED_STATE_OFF							1

void init_leds(void);
void set_led_green_state(uint8_t state);
void set_led_red_state(uint8_t state);