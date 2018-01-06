#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

#define OUTPUT_PWM		PB3
#define INPUT_COMP		PB4
#define TTOTAL_US		170
#define TON_US			110
#define TOFF_US			(TTOTAL_US - TON_US)

int main(void) {
	PORTB = _BV(INPUT_COMP);		// Pullup
	DDRB = _BV(OUTPUT_PWM);

	while (true) {
		if (PINB & _BV(INPUT_COMP)) {
			PORTB |= _BV(OUTPUT_PWM);
		}
		_delay_us(TON_US);

		PORTB &= ~_BV(OUTPUT_PWM);
		_delay_us(TOFF_US);
	}

	return 0;
}
