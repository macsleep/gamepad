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
// range for sbus values
#define X1 175.0
#define X2 1810.0

// range for usb values
#define Y1 -127.0
#define Y2 127.0

// values for normalize function
#define M (Y2-Y1)/(X2-X1)
#define B Y1-M*X1

// buffer sizes
#define RX_BUFFER_SIZE 32
#define CH_BUFFER_SIZE 16

// sbus macros
#define SBUS_BAUD F_CPU/16/100000-1
#define SBUS_FLAG_FRAME_LOST 2
#define SBUS_FLAG_FAILSAVE_ACTIVATED 3

// timer1 start value = 16 bit - CPU clock * 200 us / prescaler value
#define TIMER1_INIT_COUNT 65536-F_CPU*0.0002/8

/* Function Prototypes */
void SBus_Init(void);
uint8_t SBus_Parse(int8_t *channels, uint8_t size);
int8_t SBus_Normalize(float x);
void SBus_Disable(void);

#endif

