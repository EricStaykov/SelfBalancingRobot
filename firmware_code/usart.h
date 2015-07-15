#define CPU_SPEED								20000000UL
#define USART_BAUDRATE							57600
//#define USART_BAUDRATE_PRESCALER				(uint16_t)((CPU_SPEED / (USART_BAUDRATE * 16UL)) - 1)
#define USART_BAUDRATE_PRESCALER				(uint16_t)21 // see http://www.wormfood.net/avrbaudcalc.php

void usart_init(void);
void usart_send_string(char *message);
void usart_send_byte(uint8_t data);
ISR(USART_RX_vect);