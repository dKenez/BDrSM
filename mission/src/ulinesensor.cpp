/*
 *
 * Copyright © 2022 DTU,
 * Author:
 * Christian Andersen jcan@dtu.dk
 * Jacob Bechmann Pedersen
 *
 * The MIT License (MIT)  https://mit-license.org/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the “Software”), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE. */

#include <string>
#include <string.h>
#include "ulinesensor.h"
#include "ubridge.h"

// create
ULineSensor lineSensor;

// Bridge class:
void ULineSensor::setup()
{ /// subscribe to # information (debug text messages)
    bridge.tx("regbot:livn subscribe -1\n");
}

// regbot:liw 925 1090 1177 1113 1046 875 928 1114
// regbot:liw
bool ULineSensor::decode(char *msg)
{ // catch all messages starting with '#'
    // from any source
    bool used = true;
    const char *p1 = strchrnul(msg, ':');
    if (strncmp(p1, ":livn ", 6) == 0)
    { // decode line sensor message

        // advance to first parameter
        if (strlen(p1) > 6)
            p1 += 6;
        else
            return false;

        // get data
        dataLock.lock();
        // time in seconds
        L1 = (int)strtol(p1, (char **)&p1, 10); // L1
        L2 = (int)strtol(p1, (char **)&p1, 10); // L2
        L3 = (int)strtol(p1, (char **)&p1, 10); // L3
        L4 = (int)strtol(p1, (char **)&p1, 10); // L4
        L5 = (int)strtol(p1, (char **)&p1, 10); // L5
        L6 = (int)strtol(p1, (char **)&p1, 10); // L6
        L7 = (int)strtol(p1, (char **)&p1, 10); // L7
        L8 = (int)strtol(p1, (char **)&p1, 10); // L8
        dataLock.unlock();
    }
    else
        used = false;
    //
    return used;
}
