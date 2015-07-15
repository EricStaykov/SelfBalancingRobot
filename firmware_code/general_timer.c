#include <avr/io.h>
#include "general_timer.h"

void init_general_timer(void) {
	TIMSK1 = 1 << OCIE1A;
	TCCR1B = (1 << CS11) | (1 << WGM12);
	OCR1A = (CPU_SPEED / GENERAL_TIMER_CLOCK_SPEED_SCALAR) / GENERAL_TIMER_FREQUENCY;
}