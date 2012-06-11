//  Com.h - A simple I2C protocol library
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

#ifndef I2CComs_h
#define I2CComs_h

#include <Arduino.h>
#include <Wire.h>

class I2CComs
{
public:
    I2CComs();
    void start(int address, bool areWeDebugging);
    unsigned char commandByte();
    unsigned char payloadByte1();
    unsigned char payloadByte2();
    bool dataChanged();
};

//Com is a much better naming scheme
extern I2CComs Com;

void receiveData(int byteCount);


#endif
