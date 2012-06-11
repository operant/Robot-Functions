//  Com.cpp - A simple I2C protocol library
//  Version: 0.1
//  Copyright 2012 Josh Smith
//
//  This file is part of the Com library.
//
//  The Com libary is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  The Com library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with the Com library.  If not, see <http://www.gnu.org/licenses/>.
//  
//  Created by Josh Smith.

#include "Com.h"

static unsigned char commandByteHelper;
static unsigned char payloadByte1Helper;
static unsigned char payloadByte2Helper;
static bool dataChangedHelper;
static bool printDebugMessages;

unsigned char _dataByte1;

unsigned char _dataByte2;
unsigned char _dataByte3;
unsigned char _dataByte4;
unsigned char _dataByte5;

I2CComs::I2CComs()
{
    commandByteHelper = 0;
    payloadByte1Helper = 0;
    payloadByte2Helper = 0;
    dataChangedHelper = false;
    printDebugMessages = false;
    
    _dataByte1 = 0;
    _dataByte2 = 0;
    _dataByte3 = 0;
    _dataByte4 = 0;
    _dataByte5 = 0;
}

void I2CComs::start(int address, bool areWeDebugging)
{
    Wire.begin(address);
    Wire.onReceive(receiveData);
    printDebugMessages = areWeDebugging;
}

void receiveData(int byteCount)
{
    if (byteCount == 5)
    {
        _dataByte1 = (0x000000FF & Wire.read()); //Command Byte
        _dataByte2 = (0x000000FF & Wire.read()); //Payload Data 1
        _dataByte3 = (0x000000FF & Wire.read()); //Payload Data 2
        _dataByte4 = (0x000000FF & Wire.read()); //Flipped Version of Byte 2
        _dataByte5 = (0x000000FF & Wire.read()); //Flipped Version of Byte 3
        
        if (printDebugMessages == true)
        {
            Serial.println(_dataByte1, HEX);
            Serial.println(_dataByte2, HEX);
            Serial.println(_dataByte3, HEX);
            Serial.println(_dataByte4, HEX);
            Serial.println(_dataByte5, HEX);
            Serial.println("---------------");
        }
        
        //Check if the payload bytes and the flipped counterparts are indeed
        //opposite using XOR. If so, then set the bytes we actually use in loop()
        if ((0xFF == (_dataByte2 ^ _dataByte4)) &&
            (0xFF == (_dataByte3 ^ _dataByte5)))
        {
            if ((commandByteHelper != _dataByte1) || (payloadByte1Helper != _dataByte2) || (payloadByte2Helper != _dataByte3))
            {
                commandByteHelper = _dataByte1;
                payloadByte1Helper = _dataByte2;
                payloadByte2Helper = _dataByte3;
                
                //Set the flag to say that we have new data
                dataChangedHelper = true;
            }
        }
        if (printDebugMessages == true)
        {
            Serial.println(commandByteHelper, HEX);
            Serial.println(payloadByte1Helper, HEX);
            Serial.println(payloadByte2Helper, HEX);
            Serial.println("---------------");
        }
    }
    
    //The following logic needs to be checked because if too many packets are recieved at once, it may continue
    //"deleting" them
    else if (byteCount > 5)
    {
        while (Wire.available() > 0)
        {
            Wire.read();
        }
    }
}

unsigned char I2CComs::commandByte()
{
    return commandByteHelper;
}

unsigned char I2CComs::payloadByte1()
{
    return payloadByte1Helper;
}

unsigned char I2CComs::payloadByte2()
{
    return payloadByte2Helper;
}

bool I2CComs::dataChanged()
{
    return dataChangedHelper;
}

// We need to preinstantiate I2CComs so we don't have to in the sketch!

I2CComs Com = I2CComs();