``# SBus Gamepad

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
* clone or download the firmware
* edit the Makefile and change the LUFA_PATH to where ever you installed LUFA
* make sure the avr-gcc and teensy_loader_cli are in your path
* execute `make` to build the HEX file
* press and release the tiny Teensy pushbutton to activate the HalfKey bootloader
* execute `make teensy` to download the HEX file to the attached Teensy
 
If you don't want to build the software yourself just download the Gamepad.hex.save file and load it to the Teensy 2.0 using: `teensy_loader_cli --mcu=atmega32u4 -w -v Gamepad.hex.save`

## Usage
Create a new model for the sbus gamepad on your transmitter. Make sure that you enable ailerons, elevator, throttle and rudder for the receiver at minimum. Bind the receiver like you normally would. Use software like <a href="http://html5gamepad.com">HTML5 Gamepad Tester</a> to test the sbus gamepad. Once you have confirmed operation start your favorite simulator and see if it recognizes the sbus gamepad.

## Testing

All testing was done using a Teensy 2.0 and the 16 channel FrSky XM receiver (no other hardware was tested). Shoud you need to adjust the range of the sbus values sent by your transmitter please edit the X1, X2 macros in the SBus.h file and rebuild. The Teensy needs to run with 5 volts to be a full speed USB device. Also the FrSky XM receiver needs the 5 volts to operate (output of the sbus signal is 3.3 volts though). Total power consumption should be around 50 ma at 5 volts (30 ma for the Teensy and 20 ma for the XM receiver).

Date: 2018-09-21

