# USB Protocol

The teensy presents itself as a generic desktop **H**uman **I**nterface **D**evice (HID) to the host computer. It has one configuration that transfers data to the host computer via an Interrupt IN pipe. All data is contained in 9 bytes described by the report descriptor:

* Collection (Application)    
	* Usage (Pointer)    
		* Collection (Physical)    
			* Usage (X)    
			* Usage (Y)    
			* Usage (Z)    
			* Usage (Rx)    
			* Usage (Ry)    
			* Usage (Rz)    
			* Usage (Slider)    
			* Usage (Slider)    
			* Logical Minimum (-127)  
			* Logical Maximum (127)  
			* Report Count (8)  
			* Report Size (8)  
			* Input (Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bitfield) 
		* End Collection     
		* Usage Page (Button) 
		* Usage Minimum (1)  
		* Usage Maximum (8)  
		* Logical Minimum (0)  
		* Logical Maximum (1)  
		* Report Count (8)  
		* Report Size (1)  
		* Input (Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bitfield) 
* End Collection

The first 8 bytes contain the first 8 channels the receiver sends. The channel values of 0 to 2047 are converted to a USB friendly signed byte (-127 to 127). The next 8 channels get encoded into 1 byte as buttons that are either "on" or "off" (one bit equals one button). If the converted channel value is greater than zero the button is "on" (1) and otherwise "off" (0). Be aware that the XM receiver sends the **R**adio **S**trength **S**ignal **I**ndicator (RSSI) in channel 16 to the teensy (this button is usually "on").