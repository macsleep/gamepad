# Testing

All testing was done using a Teensy 2.0 and the 16 channel FrSky XM receiver (no other hardware was used).

A nice way to check the values the sbus gamepad provides is the [HTML5 Gamepad Tester](http://html5gamepad.com/). Values should toogle between -1 and 1 for the analog inputs. On my computer the two sliders where not displayed.

![image](images/HTML5Gamepad.png)

Shoud you need to adjust the range of the sbus values sent by your transmitter please edit the X1, X2 macros in the SBus.h file and rebuild.

Be aware that the XM receiver sends the **R**adio **S**ignal **S**trength **I**ndicator (RSSI) in channel 16 to the Teensy. Because of this the last button (B7) is usually "on".

The Teensy needs to run with 5 Volts to be a full speed USB device. Also the FrSky XM receiver needs the 5 Volts to operate (output of the sbus signal is 3.3 Volts though). Total power consumption should be around 50 mA at 5 Volts (30 mA for the Teensy and 20 mA for the XM receiver).

Memory usage does not seem to be an issue currently. It might even be possible to fit this firmware into an atmega8u2 (8k flash, 512 bytes RAM):

```
AVR Memory Usage
Device: atmega32u4

Program:    6212 bytes (19.0% Full)
(.text + .data + .bootloader)

Data:        103 bytes (4.0% Full)
(.data + .bss + .noinit)
```
Depending on how you set the receiver failsafe the gamepad will provide those values when you shutdown the transmitter while the sbus gamepad is still connected. Please see the XM receiver documentation for details.

Date: 2018-09-22

