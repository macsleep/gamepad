/*
  Copyright 2018 Sleepy

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
 * functions for reading the sbus packets via an inverter into the uart of the teensy 2.0
 */

#include "SBus.h"

// uart buffer written by interrupt
static volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
static volatile uint8_t rx_buffer_head;

// rc channel values sent by transmitter
static volatile uint16_t ch_buffer[CH_BUFFER_SIZE];

/** Initialize UART */
void SBus_Init(void) {
        cli();

        // UART
        UBRR1 = SBUS_BAUD;
        UCSR1B = (1 << RXEN1) | (1 << RXCIE1); // enable receiver, interrupt
        UCSR1C = (1 << UCSZ11) | (1 << UCSZ10) | (1 << UPM11); // 8 bit, even parity
        rx_buffer_head = 0;

        // Timer1
        TCCR1A = 0; // no pwm
        TCCR1B = 0; // no clock for prescaler
        TCNT1 = TIMER1_INIT_COUNT; // start value
        TCCR1B |= (1 << CS11); // prescaler 8
        TIMSK1 |= (1 << TOIE1); // enable timer interrupt

        sei();
}

/** Parse the serial buffer for results
 *
 *  \param[out]    buffer where parsed result should be stored
 *  \param[in]     size of buffer
 *
 *  \return Int \c zero if there is something to report, \c non zero if problem
 */
uint8_t SBus_Parse(int8_t *channels, uint8_t size) {
        uint8_t i;

        ch_buffer[0] = (rx_buffer[1] | rx_buffer[2] << 8) & 0x07ff;
        ch_buffer[1] = (rx_buffer[2] >> 3 | rx_buffer[3] << 5) & 0x07ff;
        ch_buffer[2] = (rx_buffer[3] >> 6 | rx_buffer[4] << 2 | rx_buffer[5] << 10) & 0x07ff;
        ch_buffer[3] = (rx_buffer[5] >> 1 | rx_buffer[6] << 7) & 0x07ff;
        ch_buffer[4] = (rx_buffer[6] >> 4 | rx_buffer[7] << 4) & 0x07ff;
        ch_buffer[5] = (rx_buffer[7] >> 7 | rx_buffer[8] << 1 | rx_buffer[9] << 9) & 0x07ff;
        ch_buffer[6] = (rx_buffer[9] >> 2 | rx_buffer[10] << 6) & 0x07ff;
        ch_buffer[7] = (rx_buffer[10] >> 5 | rx_buffer[11] << 3) & 0x07ff;
        ch_buffer[8] = (rx_buffer[12] | rx_buffer[13] << 8) & 0x07ff;
        ch_buffer[9] = (rx_buffer[13] >> 3 | rx_buffer[14] << 5) & 0x07ff;
        ch_buffer[10] = (rx_buffer[14] >> 6 | rx_buffer[15] << 2 | rx_buffer[16] << 10) & 0x07ff;
        ch_buffer[11] = (rx_buffer[16] >> 1 | rx_buffer[17] << 7) & 0x07ff;
        ch_buffer[12] = (rx_buffer[17] >> 4 | rx_buffer[18] << 4) & 0x07ff;
        ch_buffer[13] = (rx_buffer[18] >> 7 | rx_buffer[19] << 1 | rx_buffer[20] << 9) & 0x07ff;
        ch_buffer[14] = (rx_buffer[20] >> 2 | rx_buffer[21] << 6) & 0x07ff;
        ch_buffer[15] = (rx_buffer[21] >> 5 | rx_buffer[22] << 3) & 0x07ff;

        if (size < CH_BUFFER_SIZE) return (1);

        for (i = 0; i < CH_BUFFER_SIZE; i++) {
                channels[i] = SBus_Normalize(ch_buffer[i]);
        }

        return (0);
}

/** Normalize SBus values
 *
 *  \param[in]     sbus value (0 to 2047)
 *
 *  \return        usb value (-127 to 127)
 */
int8_t SBus_Normalize(float x) {
        float y;

        y = M * x + B;
        if (y < Y1) y = Y1;
        if (y > Y2) y = Y2;

        return y;
}

/** Disable UART & Timer */
void SBus_Disable(void) {
        cli();
        UCSR1B &= ~((1 << RXEN1) | (1 << RXCIE1));
        TIMSK1 &= ~(1 << TOIE1);
        sei();
}

/** Receive Interrupt */
ISR(USART1_RX_vect) {
        uint8_t c, i;

        c = UDR1;
        i = rx_buffer_head;
        TCNT1 = TIMER1_INIT_COUNT; // reset timer
        rx_buffer[i++] = c;
        if (i >= RX_BUFFER_SIZE) i = 0;
        rx_buffer_head = i;
}

/** Timer Interrupt
 * The timer overflow interrupt will get triggered between sbus packets.
 * Because it looks for the gaps there is no need to check for length,
 * header or trailer in the data.
 */
ISR(TIMER1_OVF_vect) {
        rx_buffer_head = 0;
}

