# SBus Gamepad

## Description
Ever wanted to use a FrSky Taranis wirelessly with PC simulators like [FPVFreerider](https://fpv-freerider.itch.io/) or [RC-Airsim](http://www.fabricated-reality.com/)? This project will help you do so. The idea was to use a Teensy 2.0 USB controller and pair it with a FrSky XM receiver. The Teensy on one side will provide a USB HID gamepad to the host computer while on the other it will read the sbus protocol off the receiver using the **U**niversal **A**synchronous **R**eceiver **T**ransmitter (UART). To read the sbus signal an inverter in form of a simple transistor will be needed between the Teensy and the receiver. For more details please see the docs directory.

## Hardware
* Teensy 2.0
	* available here: [PJRC](https://www.pjrc.com/)
* FrSky XM Receiver
	* available here: [FrSky](https://www.frsky-rc.com/)
* A transistor & resistor to invert the sbus signal for the Teensy
	* available here: [Reichelt](https://www.reichelt.de/) 	
## Software
* AVR 8-bit gcc tool chain
	* available here: [Microchip](http://www.microchip.com/), [gcc tool chains](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers)
* HalfKey Loader teensy_loader_cli
	* available here: [PJRC](https://www.pjrc.com/), [teensy_loader_cli](https://www.pjrc.com/teensy/loader_cli.html)
* Dean Camera's excellent **L**ightweight **U**SB **F**ramework for **A**VRs (LUFA)
	* available here: [Four Walled Cubicle](http://www.fourwalledcubicle.com/), [LUFA](http://www.fourwalledcubicle.com/LUFA.php)

## Build
* clone or download the firmware
* edit the Makefile and change the LUFA_PATH to wherever you installed LUFA
* make sure the avr-gcc and teensy_loader_cli are in your path
* execute `make` to build the hex file
* press and release the tiny Teensy pushbutton to activate the HalfKey bootloader
* execute `make teensy` to download the hex file to the attached Teensy
 
If you don't want to build the software yourself just download the Gamepad.hex.save file and load it onto the Teensy using: `teensy_loader_cli --mcu=atmega32u4 -w -v Gamepad.hex.save`

## Usage
Create a new model for the sbus gamepad on your transmitter. Make sure that you enable at least 4 channels (e.g. ailerons, elevator, throttle and rudder) for the receiver. Bind the receiver like you normally would. Use software like [HTML5 Gamepad Tester](http://html5gamepad.com/) to test the sbus gamepad. Once you have confirmed operation start your favorite simulator and see if it recognizes the sbus gamepad.

Date: 2018-09-21

