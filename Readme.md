# SBus Gamepad

## Description
This is software for a USB dongle to use a FrSky Taranis wirelessly with PC simulators like [FPVFreerider](https://fpv-freerider.itch.io/) or [RC-Airsim](http://www.fabricated-reality.com/). On the USB side there is a Teensy 2.0 with an eight bit atmega32u4 CPU. And the receiver is a FrSky XM with sbus output. The Teensy reads the sbus signal of the receiver via UART and then presents that data as a USB HID gamepad to the computer. To read the sbus signal the Teensy needs an inverter in form of a simple transistor. Please see the docs directory for more details.

## Hardware
* Teensy 2.0
	* available here: [PJRC](https://www.pjrc.com/)
* FrSky XM Receiver
	* available here: [FrSky](https://www.frsky-rc.com/)
* A transistor & resistor to invert the sbus signal for the Teensy
	* available here: [Reichelt](https://www.reichelt.de/) 	
## Software
* AVR 8-bit gcc tool chain
	* available here: [Microchip](http://www.microchip.com/) 
* HalfKey Loader teensy_loader_cli
	* available here: [PJRC](https://www.pjrc.com/)
* Dean Camera's excellent **L**ightweight **U**SB **F**ramework for **A**VRs (LUFA)
	* available here: [Four Walled Cubicle](http://www.fourwalledcubicle.com/) 

## Build
* clone or download the firmware
* edit the Makefile and change the LUFA_PATH to where ever you installed LUFA
* make sure the avr-gcc and teensy_loader_cli are in your path
* execute `make` to build the HEX file
* press and release the tiny Teensy pushbutton to activate the HalfKey bootloader
* execute `make teensy` to download the HEX file to the attached Teensy
 
If you don't want to build the software yourself just download the Gamepad.hex.save file and load it to the Teensy 2.0 using: `teensy_loader_cli --mcu=atmega32u4 -w -v Gamepad.hex.save`

## Usage
Create a new model for the sbus gamepad on your transmitter. Make sure that you enable at least 4 channels (e.g ailerons, elevator, throttle and rudder) for the receiver. Bind the receiver like you normally would. Use software like [HTML5 Gamepad Tester](http://html5gamepad.com/) to test the sbus gamepad. Once you have confirmed operation start your favorite simulator and see if it recognizes the sbus gamepad.

Date: 2018-09-21

