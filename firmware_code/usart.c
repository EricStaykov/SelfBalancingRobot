#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include "usart.h"

void usart_init(void) {
	UBRR0H = (uint8_t)(USART_BAUDRATE_PRESCALER >> 8);
	UBRR0L = (uint8_t)(USART_BAUDRATE_PRESCALER);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	UCSR0C = (3 << UCSZ00);
}

void usart_send_string(char *message) {
	for (int letters = 0; letters < strlen(message); letters++) {
		while(!(UCSR0A & (1 << UDRE0)));
		UDR0 = message[letters];
	}
}

void usart_send_byte(uint8_t data) {
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

// serial comms receive interrupt
ISR(USART_RX_vect) {
	cli();
	uint8_t input = UDR0;
	usart_send_byte(input);
	sei();
}