#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "hal.h"

struct counting_state_t {
	uint32_t total_cts;
	uint32_t timer1_ovfs;
	uint16_t last_cnt1_value;
	uint16_t xored_cnt1_value;
};
static struct counting_state_t state;
static bool sound = false;
static uint16_t msg_delay_ms = 1000;
static uint16_t current_sleep_ms;

static void rs232_tx(char data) {
	while (!(UCSRA & _BV(UDRE)));
	UDR = data;
}

static void rs232_tx_hexnibble(uint8_t nibble) {
	nibble &= 0xf;
	if (nibble < 10) {
		rs232_tx(nibble + '0');
	} else {
		rs232_tx(nibble + 'a' - 10);
	}
}

static void rs232_tx_hexval16(uint16_t value) {
	bool had_digits = false;
	for (int8_t bit = 12; bit >= 0; bit -= 4) {
		uint8_t nibble = (value >> bit) & 0xf;
		if ((nibble != 0) || had_digits || (bit == 0)) {
			rs232_tx_hexnibble(nibble);
			had_digits = true;
		}
	}
}

static void rs232_tx_hexval32(uint32_t value) {
	bool had_digits = false;
	for (int8_t bit = 28; bit >= 0; bit -= 4) {
		uint8_t nibble = (value >> bit) & 0xf;
		if ((nibble != 0) || had_digits || (bit == 0)) {
			rs232_tx_hexnibble(nibble);
			had_digits = true;
		}
	}
}

static void rs232_tx_str(const char *string) {
	char nextbyte;
	while ((nextbyte = pgm_read_byte(string)) != 0) {
		rs232_tx(nextbyte);
		string++;
	}
}

static void show_status(const struct counting_state_t *state) {
	rs232_tx('T');
	rs232_tx('=');
	rs232_tx_hexval32(state->timer1_ovfs);
	rs232_tx(' ');
	rs232_tx('C');
	rs232_tx('=');
	rs232_tx_hexval32(state->total_cts);
	rs232_tx(' ');
	rs232_tx('L');
	rs232_tx('=');
	rs232_tx_hexval16(state->last_cnt1_value);
	rs232_tx(' ');
	rs232_tx('X');
	rs232_tx('=');
	rs232_tx_hexval16(state->xored_cnt1_value);
	rs232_tx('\r');
	rs232_tx('\n');
}

ISR(USART_RX_vect) {
	uint8_t rxbyte = UDR;
	if (rxbyte == 's') {
		/* Turn sound off */
		sound = false;
		LEDY_SetInactive();
	} else if (rxbyte == 'S') {
		/* Turn sound on */
		sound = true;
		LEDY_SetActive();
	} else if (rxbyte == '1') {
		msg_delay_ms = 5000;
	} else if (rxbyte == '2') {
		msg_delay_ms = 2500;
	} else if (rxbyte == '3') {
		msg_delay_ms = 1000;
	} else if (rxbyte == '4') {
		msg_delay_ms = 500;
	} else if (rxbyte == '5') {
		msg_delay_ms = 250;
	} else if (rxbyte == '6') {
		msg_delay_ms = 100;
	} else if (rxbyte == '7') {
		msg_delay_ms = 50;
	} else if (rxbyte == '8') {
		msg_delay_ms = 25;
	} else if (rxbyte == '9') {
		msg_delay_ms = 0;
	} else if (rxbyte == '?') {
		rs232_tx_str(PSTR("Help:\r\n"));
		rs232_tx_str(PSTR("   ?        This help page.\r\n"));
		rs232_tx_str(PSTR("   1 to 9   Change output rate to 5000, 2500, 1000, 500, 250, 100, 50, 25 or 0 milliseconds.\r\n"));
		rs232_tx_str(PSTR("   s        Turn clicker sound off\r\n"));
		rs232_tx_str(PSTR("   S        Turn clicker sound on\r\n"));
		rs232_tx_str(PSTR("Message format:\r\n"));
		rs232_tx_str(PSTR("   T=time C=counts L=last_tcnt1 X=xored_tcnt1\r\n"));
		rs232_tx_str(PSTR("   Time in multiples of 4/1125th of a second (approx. 3.56 ms).\r\n"));
		rs232_tx_str(PSTR("   last_tcnt1 and xored_tcnt1 give the last TCNT1 value at an event\r\n"));
		rs232_tx_str(PSTR("   and the cumulative XORed TCNT1 value of all events so far. Regardless\r\n"));
		rs232_tx_str(PSTR("   of timer setting, lines are only printed when event count has changed.\r\n"));
	}
	current_sleep_ms = 1;
}

ISR(INT0_vect) {
	state.total_cts++;
	state.last_cnt1_value = TCNT1;
	state.xored_cnt1_value ^= state.last_cnt1_value;
	GIMSK &= ~_BV(INT0);	/* Disable further INT0 IRQs */
	if (sound) {
		CLICK_SetActive();
	}

	TCNT0 = 0xaa;			/* Preload for 300µs */
	TIFR |= _BV(TOV0);		/* Clear pending IRQ flag */
	TIMSK |= _BV(TOIE0);	/* Enable timer IRQ (which will re-enable INT0 IRQs) */
}

ISR(TIMER0_OVF_vect) {
	EIFR |= _BV(INTF0);		/* Clear INT0 IRQ flag */
	GIMSK |= _BV(INT0);		/* Re-enable INT0 IRQ */
	TIMSK &= ~_BV(TOIE0);	/* Disable Timer0 IRQ */
	CLICK_SetInactive();
}

ISR(TIMER1_OVF_vect) {
	state.timer1_ovfs++;
}

static void init_rs232(void) {
	UBRRL = 9;		/* 115200 Baud at 18.432 MHz */
	UCSRB = _BV(RXCIE) | _BV(RXEN) | _BV(TXEN);
}

static void init_extirq(void) {
	/* Pulse length is approximately 200µs with some bouncing in the end of the
	 * signal. Signal is active-low. Holdoff IRQ generation for 300µs after
	 * each IRQ */
	MCUCR |= _BV(ISC01);	/* Falling edge on INT0 generates IRQ */
	GIMSK |= _BV(INT0);
}

static void init_irq_unlock_timer(void) {
	TCCR0B = _BV(CS01) | _BV(CS00);		/* 1/64 at 18.432 MHz, full OVF 889µs */
}

static void init_jitter_timer(void) {
	/* Free running TIMER1 measures time between events (for example, for TRNG) */
	TCCR1B = _BV(CS10);		/* Full overflow every 3.55 ms */
	TIMSK |= _BV(TOIE1);
}

int main(void) {
	initHAL();
	LEDY_SetConditional(sound);

	init_irq_unlock_timer();
	init_jitter_timer();
	init_rs232();
	init_extirq();
	sei();

	uint32_t last_count = 0;
	uint16_t switch_debounce_cnt = 0;
	bool switch_armed = true;
	while (true) {
		struct counting_state_t state_copy;
		do {
			cli();
			state_copy = state;
			sei();
		} while (state_copy.total_cts == last_count);
		last_count = state_copy.total_cts;

		show_status(&state_copy);
		current_sleep_ms = msg_delay_ms;
		while (current_sleep_ms) {
			current_sleep_ms--;
			_delay_ms(1);
			if (SWITCH_IsActive()) {
				if (switch_armed) {
					switch_debounce_cnt++;
					if (switch_debounce_cnt == 100) {
						sound = !sound;
						LEDY_SetConditional(sound);
						switch_armed = false;
					}
				}
			} else {
				if (switch_debounce_cnt) {
					switch_debounce_cnt--;
				} else {
					switch_armed = true;
				}
			}
		}
	}

	return 0;
}
