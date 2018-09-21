# SBus Protocol

The sbus protocol is a 100 kilo baud serial protocol (1 start bit, 8 data bits, 1 even parity bit and 2 stop bits). Every 9 milliseconds a packet of 25 bytes gets sent by the receiver. The packet is made up of a start byte, 22 data bytes, one flag byte and an end byte:

[start][data1][data2][data3][data4][data5][data6][data7][data8][data9][data10][data11][data12][data13][data14][data15][data16][data17][data18][data19][data20][data21][data22][flags][end]

The start byte is 0x0f and the end byte usually 0x00. Remember these are the values the Teensy sees after the sbus signal has been inverted by the transistor. The Teensys UART needs the inverter to recognize the start bit (low), partity bit and stop bits (high).

Inside the 22 data bytes the 16 rc channels are encoded. Each rc channel is made up of 11 bits (a value between 0 and 2047). Because of this a rc channel value is spread over 2-3 data bytes. Channel 1 e.g. can be found in [data1] and the next 3 bits of [data2]. Please see the code for details.

Date: 2018-09-21

