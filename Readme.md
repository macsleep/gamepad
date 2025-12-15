# S.BUS Gamepad

## Description
Ever wanted to use a FrSky Taranis wirelessly with PC simulators like [FPVFreerider](https://fpv-freerider.itch.io/) or [RC-AirSim](http://www.fabricated-reality.com/)? This project will help you do so. The idea was to use a Teensy 2.0 USB controller and pair it with a FrSky XM receiver. The Teensy on one side will provide a USB HID gamepad to the host computer while on the other it will read the S.BUS protocol off the receiver using the **U**niversal **A**synchronous **R**eceiver **T**ransmitter (UART). To read the S.BUS signal an inverter in form of a simple transistor will be needed between the Teensy and the receiver. For more details please see the [docs](docs) directory.

**Update:** If you would like to use an ExpressLRS receiver instead of the FrSky XM receiver then please check out these [instructions](docs/ELRS.md). 

## Hardware
* Teensy 2.0
	* available here: [PJRC](https://www.pjrc.com/), [Teensy 2.0](https://www.pjrc.com/store/teensy.html)
* FrSky XM Receiver
	* available here: [FrSky](https://www.frsky-rc.com/), [XM Receiver](https://www.frsky-rc.com/product/xm-1g-sbus-non-telemetry/)
* A transistor & resistor to invert the S.BUS signal for the Teensy
	* available here: [Reichelt](https://www.reichelt.de/), [2N7000](https://www.reichelt.de/mosfet-n-ch-60v-0-115a-0-4w-to-92-2n-7000-p41141.html), [10K Resistor](https://www.reichelt.de/widerstand-metallschicht-10-0-kohm-0207-0-6-w-1-metall-10-0k-p11449.html)

## Software
* AVR 8-bit gcc toolchain
	* available here: [Microchip](http://www.microchip.com/), [gcc toolchains](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers)
* HalfKey Loader teensy_loader_cli
	* available here: [PJRC](https://www.pjrc.com/), [teensy_loader_cli](https://www.pjrc.com/teensy/loader_cli.html)
* Dean Camera's excellent **L**ightweight **U**SB **F**ramework for **A**VRs (LUFA)
	* available here: [Four Walled Cubicle](http://www.fourwalledcubicle.com/), [LUFA](https://github.com/abcminiuser/lufa)

## Build
* clone or download the firmware
* edit the Makefile and change the LUFA_PATH to wherever you installed LUFA
* make sure the avr-gcc and teensy_loader_cli are in your path
* execute `make` to build the hex file
* press and release the tiny Teensy pushbutton to activate the HalfKey bootloader
* execute `make teensy` to download the hex file to the attached Teensy
 
If you don't want to build the software yourself just download the Gamepad.hex.teensy file and load it onto the Teensy using: `teensy_loader_cli --mcu=atmega32u4 -w -v Gamepad.hex.teensy`

## Alternative Build

Here are a few tips for adjusting the build to an [Arduino Micro](https://store.arduino.cc/products/arduino-micro) (original or clone). You will need [avrdude](https://www.nongnu.org/avrdude/) to program the Micro.

* edit the Makefile and change the BOARD variable from TEENSY to MICRO
* execute `make avrdude AVRDUDE_PROGRAMMER=avr109 AVRDUDE_PORT=<serial port>` to download the hex file to the attached Micro

Replace `<serial port>` with the device name the Micro is connected to on your computer after resetting. Depending on the bootloader installed on your Micro you might have to change AVRDUDE_PROGRAMMER value from avr109 to arduino. If you don't want to build the software yourself just download the Gamepad.hex.micro file and load it onto the Micro using: `avrdude -p atmega32u4 -P <serial port> -c avr109 -U flash:w:Gamepad.hex.micro`

## Usage
Create a new model for the S.BUS gamepad on your transmitter. Make sure that you enable at least 4 channels (e.g. ailerons, elevator, throttle and rudder) for the receiver. Bind the receiver like you normally would. Use software like [HTML5 Gamepad Tester](http://html5gamepad.com/) to test the S.BUS gamepad. Once you have confirmed operation start your favorite simulator and enjoy.

Date: 2024-05-20
