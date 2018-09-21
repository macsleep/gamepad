/*
  Copyright 2018 Jan Schlieper
  Copyright 2017 Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for Gamepad.c.
 */

#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

/* Includes: */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>

#include "Descriptors.h"
#include "sbus.h"

#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>

/* Type Defines: */

/** Type define for the joystick HID report structure, for creating and sending HID reports to the host PC.
 *  This mirrors the layout described to the host in the HID report descriptor, in Descriptors.c.
 */
typedef struct {
        uint8_t X; // analog value, mapped to channel 1
        uint8_t Y; // analog value, mapped to channel 2
        uint8_t Z; // analog value, mapped to channel 3
        uint8_t Rx; // analog value, mapped to channel 4
        uint8_t Ry; // analog value, mapped to channel 5
        uint8_t Rz; // analog value, mapped to channel 6
        uint8_t S1; // analog value, mapped to channel 7
        uint8_t S2; // analog value, mapped to channel 8
        uint8_t Buttons1; // mapped to channels 9-16, on if channel > 0
} USB_GamepadReport_Data_t;

/* Macros: */
/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
#define LEDMASK_USB_NOTREADY LEDS_LED1

/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
#define LEDMASK_USB_ENUMERATING (LEDS_LED2 | LEDS_LED3)

/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
#define LEDMASK_USB_READY (LEDS_LED2 | LEDS_LED4)

/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
#define LEDMASK_USB_ERROR (LEDS_LED1 | LEDS_LED3)

/* Function Prototypes: */
void SetupHardware(void);

void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);
void EVENT_USB_Device_StartOfFrame(void);

bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t * const HIDInterfaceInfo,
        uint8_t * const ReportID,
        const uint8_t ReportType,
        void* ReportData,
        uint16_t * const ReportSize);
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t * const HIDInterfaceInfo,
        const uint8_t ReportID,
        const uint8_t ReportType,
        const void* ReportData,
        const uint16_t ReportSize);

#endif

