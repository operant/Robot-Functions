# The Com Library

### A simple but effective library for comunications with the cRIO over I2C

## Credits

Written by me but I have to credit Grant Farrand with the original design of the protocol used by the library.


## Installing

The Com folder should be moved into your Arduino IDE's libraries folder. Follow the steps below for your respective system:

### Mac

1) Locate your Arduino IDE app and left-click on its icon.
2) Click on "Show Package Contents."
3) Navigate to 'Contents/Resources/Java/libraries' and drop the folders in there.

### Windows

Locate your Arduino folder and drop them in the libraries folder

### Linux

1) Navigate to your home folder and then to the sketchbook folder.
2) Paste the folders inside the "libraries" folder (create it if does not exist)

**Be sure to restart your IDE after adding these libraries!**

Finally open the sketch in your IDE and continue to the configuring section of this readme.

## Utilizing the Library

This library has a few functions that can be used to enable communications between the cRIO and your Arduino. For a complete example of these implemented in a sketch, see the example sketch file.

### Com.start(address, areWeDebugging)

This function is what sets up the I2C communications on the Arduino. To use this, simply pass in an integer that corresponds to the HEX address that you want to use for the Arduino and enable or disable debugging over the serial connection by setting "areWeDebugging" to true or false respectively. This function will call the Wire library's "begin" function and then the Wire library's "onReceive" function. If you are using the debugging code, you will need to call Serial.begin() with the proper baud rate passed in from the setup function of your sketch.

## Communicating with the Arduino

We have created a simple protocol that we use when talking with the cRIO. The protocol itself has verifications built in to insure the integrity of the data being passed between the cRIO and the Arduino. In addition, packets containing more packets than the required 5 will be detected and removed from the buffer. Please note that although this is a dirty fix, the rare nature of these bad packets ensures few valid packets are lost (a more elegant solution is in the works). To create a valid packet, simply follow the guide below:

**Side Note: All is represented in hex in the program and thus I will be using hex for this portion. Please be aware that most of the hex values do not correspond to any relative ASCII characters and the program is simply looking for raw hex data. However, there are a few functions that may require specific bytes to be sent based on events that are occuring. Check the comments in the code to see if the functions you want to use require any.**

     ______________________ ________________________________________________ _________________________ _________________________
    |                      |                      |                         |       Inverse of        |        Inverse of       |
    |     Command Byte     |    Payload Byte #1   |     Payload Byte #2     |     Payload Byte #1     |      Payload Byte #2    |
    |______________________|______________________|_________________________|_________________________|_________________________|
    |                      |                      |                         |                         |                         |
    |         0x01         |         0xA0         |          0x05           |          0x5F           |           0xFA          |
    |______________________|______________________|_________________________|_________________________|_________________________|


So what is the "inverse" of a byte? Well, lets look at this packet in binary.

     ______________________ ________________________________________________ _________________________ _________________________
    |                      |                      |                         |       Inverse of        |        Inverse of       |
    |     Command Byte     |    Payload Byte #1   |     Payload Byte #2     |     Payload Byte #1     |      Payload Byte #2    |
    |______________________|______________________|_________________________|_________________________|_________________________|
    |                      |                      |                         |                         |                         |
    |         0x01         |         0xA0         |          0x05           |          0x5F           |           0xFA          |
    |______________________|______________________|_________________________|_________________________|_________________________|
    |                      |                      |                         |                         |                         |
    |       00000001       |       10100000       |        00000101         |        01011111         |         11111010        |
    |______________________|______________________|_________________________|_________________________|_________________________|
    
Notice the pattern? To produce the inverses of the payload bytes, just flip the bits and then use those to calculate the respective hexadecimal representation.

Once you have your packets constructed, you need to ensure that the Arduino is properly set up as a slave device with a non-conflicting address (you only need to worry about this if you are using multiple slave devices over the same I2C lines). The Wire library expects the address that is passed in to be a numerical value instead of a hexadecimal value which is more commonly used. Simply choose a hexadecimal address and find the corresponding numerical address (convert to ASCII characters). Then use this for the i2cAddress variable.

## Contributing

I am completely open to any changes that you think should be made. If you think you have a better way to do something, feel free to submit a pull request. I want to learn from your code! :)

## Copyright

This software is licensed under the GPL license. See LICENSE.txt for a copy of this license.