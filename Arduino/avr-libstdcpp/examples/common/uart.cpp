/*
 * Copyright (c) 2018, Christopher Durand
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#define BAUD 9600

#ifndef F_CPU
#error "F_CPU must be defined!"
#endif

#include <util/setbaud.h>

#include <avr/io.h>
#include <cstdio>

// naive unbuffered uart implementation for C standard IO

static int
uart_putc(char c, [[maybe_unused]] FILE* stream)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	return 0;
}

static int
uart_getc([[maybe_unused]] FILE* stream)
{
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}

// constructor attribute: call function before main
static void uart_init() __attribute__ ((constructor, used));

static void
uart_init()
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

#if USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~(_BV(U2X0));
#endif

	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);

	static FILE uart_output = {};
	static FILE uart_input = {};

	fdev_setup_stream(&uart_output, uart_putc, nullptr, _FDEV_SETUP_WRITE);
	fdev_setup_stream(&uart_input, nullptr, uart_getc, _FDEV_SETUP_READ);

	stdout = &uart_output;
	stdin = &uart_input;
}
