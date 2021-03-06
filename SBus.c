/*
  Copyright 2018 Jan Schlieper

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
 */

/** \file
 *
 * functions for reading the SBus packets via an inverter into the UART of the teensy
 */

#include "SBus.h"

// UART buffer written by interrupt
static volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
static volatile uint8_t rx_buffer_head = 0;

// RC channel values sent by transmitter
static volatile uint16_t ch_buffer[CH_BUFFER_SIZE];

/** Initialize UART */
void SBus_Init(void) {
    uint8_t i, ch_base, rx_base;

    // initialize channel buffer
    for (i = 0; i < CH_BUFFER_SIZE; i++) ch_buffer[i] = ONE_HALF_POSITION;

    // initialize RX buffer
    for (i = 0; i < CH_BUFFER_OCTETS; i++) {
        ch_base = i * 8;
        rx_base = i * 11 + 1;

        rx_buffer[rx_base + 0] = (uint8_t) ch_buffer[ch_base + 0];
        rx_buffer[rx_base + 1] = (uint8_t) (ch_buffer[ch_base + 0] >> 8 | ch_buffer[ch_base + 1] << 3);
        rx_buffer[rx_base + 2] = (uint8_t) (ch_buffer[ch_base + 1] >> 5 | ch_buffer[ch_base + 2] << 6);
        rx_buffer[rx_base + 3] = (uint8_t) (ch_buffer[ch_base + 2] >> 2);
        rx_buffer[rx_base + 4] = (uint8_t) (ch_buffer[ch_base + 2] >> 10 | ch_buffer[ch_base + 3] << 1);
        rx_buffer[rx_base + 5] = (uint8_t) (ch_buffer[ch_base + 3] >> 7 | ch_buffer[ch_base + 4] << 4);
        rx_buffer[rx_base + 6] = (uint8_t) (ch_buffer[ch_base + 4] >> 4 | ch_buffer[ch_base + 5] << 7);
        rx_buffer[rx_base + 7] = (uint8_t) (ch_buffer[ch_base + 5] >> 1);
        rx_buffer[rx_base + 8] = (uint8_t) (ch_buffer[ch_base + 5] >> 9 | ch_buffer[ch_base + 6] << 2);
        rx_buffer[rx_base + 9] = (uint8_t) (ch_buffer[ch_base + 6] >> 6 | ch_buffer[ch_base + 7] << 5);
        rx_buffer[rx_base + 10] = (uint8_t) (ch_buffer[ch_base + 7] >> 3);
    }

    // UART
    UBRR1 = SBUS_BAUD;
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10) | (1 << UPM11); // 8 bit, even parity
    UCSR1B = (1 << RXEN1) | (1 << RXCIE1); // enable receiver, interrupt

    // Timer1
    TCCR1A = 0; // no PWM
    TCCR1B = (1 << CS11); // prescaler 8
    TCNT1 = 0; // start value
    TIMSK1 |= (1 << TOIE1); // enable interrupt
}

/** Channel Values */
uint16_t SBus_Channel(uint8_t num) {
    return (num < CH_BUFFER_SIZE) ? ch_buffer[num] : ONE_HALF_POSITION;
}

/** Normalize SBus values */
int8_t SBus_Normalize(float x) {
    float y;

    y = M * x + B;
    if (y < Y1) y = Y1;
    if (y > Y2) y = Y2;

    return y;
}

/** Disable UART & Timer */
void SBus_Disable(void) {
    UCSR1B &= ~((1 << RXEN1) | (1 << RXCIE1));
    TIMSK1 &= ~(1 << TOIE1);
}

/** Receive Interrupt */
ISR(USART1_RX_vect) {
    uint8_t c, i;

    // reset timer
    TCNT1 = TIMER1_INIT_COUNT;

    // save data
    c = UDR1;
    i = rx_buffer_head;
    rx_buffer[i++] = c;
    if (i >= RX_BUFFER_SIZE) i = 0;
    rx_buffer_head = i;
}

/** Timer Interrupt
 *  The timer overflow interrupt will get triggered between SBus packets.
 *  Because it looks for the gaps there is no need to check for length,
 *  header or trailer in the data.
 */
ISR(TIMER1_OVF_vect) {
    uint8_t i, ch_base, rx_base;

    // sync to sbus header
    rx_buffer_head = 0;

    // save sbus channels
    for (i = 0; i < CH_BUFFER_OCTETS; i++) {
        ch_base = i * 8;
        rx_base = i * 11 + 1;

        ch_buffer[ch_base + 0] = (rx_buffer[rx_base + 0] | rx_buffer[rx_base + 1] << 8) & 0x07ff;
        ch_buffer[ch_base + 1] = (rx_buffer[rx_base + 1] >> 3 | rx_buffer[rx_base + 2] << 5) & 0x07ff;
        ch_buffer[ch_base + 2] = (rx_buffer[rx_base + 2] >> 6 | rx_buffer[rx_base + 3] << 2 | rx_buffer[rx_base + 4] << 10) & 0x07ff;
        ch_buffer[ch_base + 3] = (rx_buffer[rx_base + 4] >> 1 | rx_buffer[rx_base + 5] << 7) & 0x07ff;
        ch_buffer[ch_base + 4] = (rx_buffer[rx_base + 5] >> 4 | rx_buffer[rx_base + 6] << 4) & 0x07ff;
        ch_buffer[ch_base + 5] = (rx_buffer[rx_base + 6] >> 7 | rx_buffer[rx_base + 7] << 1 | rx_buffer[rx_base + 8] << 9) & 0x07ff;
        ch_buffer[ch_base + 6] = (rx_buffer[rx_base + 8] >> 2 | rx_buffer[rx_base + 9] << 6) & 0x07ff;
        ch_buffer[ch_base + 7] = (rx_buffer[rx_base + 9] >> 5 | rx_buffer[rx_base + 10] << 3) & 0x07ff;
    }
}

