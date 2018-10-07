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

#ifndef _SBUS_H_
#define _SBUS_H_

/* Includes: */
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/* Macros: */

/** To get a linear equation from two points in a 2d Cartesian
 *  coordinate system you need to solve y = m * x + b for both
 *  points (x1, y1), (x2, y2). This gives you two equations with
 *  two unkowns (m and b) which can then be solved for m and b.
 */

// range for sbus values (min:0, max:2047)
#define X1 175.0
#define X2 1810.0

// range for usb values
#define Y1 -127.0
#define Y2 127.0

// values for normalize function
#define M (Y2-Y1)/(X2-X1)
#define B Y1-M*X1

// rx_buffer default value
#define CENTER_POSITION X1+(X2-X1)/2

// buffer sizes
#define CH_BUFFER_SIZE 16
#define RX_BUFFER_SIZE 32

// sbus macros

/** The UART currently operates without the U2X1 bit set in UCSR1A.
 *  The U2X1 bit reduces the divisor for the UART clock from 16 to 8
 *  making higher baud rates possible. The drawback of using the U2X1
 *  bit is it also halves the samples taken by the UART. So without
 *  the U2X1 bit set serial operations should be more stable.
 */
#define SBUS_BAUD F_CPU/16/100000-1

#define SBUS_FLAGS 1+((CH_BUFFER_SIZE/8)*11)
#define SBUS_FLAG_FRAME_LOST 2
#define SBUS_FLAG_FAILSAVE_ACTIVATED 3

/** At 100000 baud a bit takes 10 us time. A byte is made up of 12 bits
 *  (1 start bit, 8 data bits, 1 bit even parity and 2 stop bits). This
 *  comes to a total of 120 us for each byte sent. Setting the timer to
 *  200 us should give the AVR adequate time to reset the timer while
 *  receiving a sbus packet: 16 bit - CPU clock * 200 us / prescaler value
 */
#define TIMER1_INIT_COUNT 0xffff-F_CPU*0.0002/8

/* Function Prototypes */
void SBus_Init(void);
uint8_t SBus_GetChannel(uint8_t channel, int8_t *value);
int8_t SBus_Normalize(float x);
void SBus_Disable(void);

#endif

