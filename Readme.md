# SBus Gamepad

## Description
This is software for a USB dongle to use a FrSky Taranis wirelessly with PC simulators like <a href="https://fpv-freerider.itch.io/fpv-freerider" target="_blank">FPVFreerider</a> or <a href="http://www.fabricated-reality.com" target="_blank">RC-Airsim</a>. On the USB side there is a Teensy 2.0 with an eight bit atmega32u4 CPU. And the receiver is a FrSky XM with sbus output. The Teensy reads the sbus signal of the receiver via UART and then presents that data as a USB HID gamepad to the computer. To read the sbus signal the Teensy needs an inverter in form of a simple transistor. Please see the docs directory for more details.

## Hardware
* Teensy 2.0
	* available here: <a href="https://www.pjrc.com/" target="_blank">PJRC</a>
* FrSky XM Receiver
	* available here: <a href="https://www.frsky-rc.com/" target="_blank">FrSky</a>
* A transistor & resistor to invert the sbus signal for the Teensy
	* available here: <a href="https://www.reichelt.de/" target="_blank">Reichelt</a>
## Software
* AVR 8-bit gcc tool chain
	* available here: <a href="http://www.microchip.com/" target="_blank">Microchip</a>
* HalfKey Loader teensy_loader_cli
	* available here: <a href="https://www.pjrc.com/" target="_blank">PJRC</a>
* Dean Camera's excellent **L**ightweight **U**SB **F**ramework for **A**VRs (LUFA)
	* available here: <a href="http://www.fourwalledcubicle.com/" target="_blank">Four Walled Cubicle</a>

## Build
* Clone or download the firmware
* Edit the Makefile and change the LUFA_PATH to where ever you installed LUFA
* Make sure the avr-gcc and teensy_loader_cli are in your path
* Execute "make" to build the HEX file
* Execute "make program" to download the HEX file to the attached Teensy 2.0

If you don't want to build the software yourself just download the Gamepad.hex.save file and load it to the Teensy 2.0 using teensy_loader_cli (see Makefile for parameters).

## Usage
Create a new model for the SBus Gamepad on your transmitter. Make sure that you enable ailerons, elevator, throttle and rudder for the receiver at minimum. Bind the receiver like you normally would. Use software like <a href="http://html5gamepad.com">HTML5 Gamepad Tester</a> to test the sbus gamepad. Once you have confirmed operation start your favorite simulator and see if it recognizes the sbus gamepad.

## Testing

All testing was done using a Teensy 2.0 and the 16 channel FrSky XM receiver (no other hardware was tested). Shoud you need to adjust the range of the sbus values sent by your transmitter please edit the X1, X2 macros in the SBus.h file and rebuild. The Teensy needs to run with 5 volts to be a full speed USB device. Also the FrSky XM receiver needs the 5 volts to operate (output of the sbus signal is 3.3 volts though). Total power consumption should be around 50 ma at 5 volts (30 ma for the Teensy and 20 ma for the XM receiver).

## SBus Protocol

The sbus protocol is a 100 kilo baud serial protocol (1 start bit, 8 data bits, 1 even parity bit and 2 stop bits). Every 7 milliseconds a packet of 25 bytes get sent by the receiver. The packet is made up of a start byte, 22 data bytes, one flag byte and an end byte:

<span style="color:#ff0000">[start]</span><span style="color:#2a4b8d">[data1][data2][data3][data4][data5][data6][data7][data8][data9][data10][data11][data12][data13][data14][data15][data16][data17][data18][data19][data20][data21][data22]</span><span style="color:#fc3">[flags]</span><span style="color:#ff0000">[end]</span>

The start byte is 0x0f and the end byte usually 0x00. Remember these are the values the teensy sees after the sbus protocol has been inverted by the transistor. The teensys UART needs the inverter to recognize the start bit (low), partity bit and stop bits (high).

Inside the 22 data bytes the 16 rc channels are encoded. Each rc channel is made up of 11 bits (a value between 0 and 2047). Because of this a rc channel value is spread over 2-3 data bytes. Channel 1 e.g. can be found in [data1] and the next 3 bits of [data2]. Please see the code for details.

---

10 Sep 2018
