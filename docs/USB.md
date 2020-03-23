# USB Protocol

The Teensy presents itself as a Generic Desktop GamePad **H**uman **I**nterface **D**evice (HID) to the host computer. It has one configuration that transfers data to the host computer via an Interrupt IN pipe. All data is contained in 9 bytes described by the following configuration report descriptor:

```
 Usage Page (Generic Desktop) 
 Usage (GamePad)    
   Collection (Application)    
     Collection (Physical)
         
       Usage Page (Generic Desktop) 
       Usage (X)    
       Usage (Y)    
       Usage (Z)    
       Usage (Rx)    
       Usage (Ry)    
       Usage (Rz)    
       Usage (Slider)    
       Usage (Slider)    
       Logical Minimum (-127)  
       Logical Maximum (127)  
       Report Count (8)  
       Report Size (8)  
       Input (Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bitfield) 

       Usage Page (Button) 
       Usage Minimum (1)  
       Usage Maximum (8)  
       Logical Minimum (0)  
       Logical Maximum (1)  
       Report Count (8)  
       Report Size (1)  
       Input (Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bitfield) 

    End Collection     
  End Collection     
```

The first eight bytes contain the first eight channels the receiver sends. The eleven bit sbus channel values are converted to USB friendly signed bytes of -127 to 127. The next eight channels get encoded into one byte as buttons that are either "on" or "off" (one bit equals one button).

Vendor and Product ID (0x03EB, 0x2043) belong to Atmel and should under no circumstances be used commercially. Please see the LUFA documentation for details.
