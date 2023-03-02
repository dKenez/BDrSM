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
#include "uirsensor.h"
#include "ubridge.h"

// create
UIrSensor irSensor;

// Bridge class:
void UIrSensor::setup()
{ /// subscribe to # information (debug text messages)
    bridge.tx("regbot:ir subscribe -1\n");
}

// regbot:liw 925 1090 1177 1113 1046 875 928 1114
// regbot:liw
bool UIrSensor::decode(char *msg)
{ // catch all messages starting with '#'
    // from any source
    bool used = true;
    const char *p1 = strchrnul(msg, ':');
    if (strncmp(p1, ":ir ", 4) == 0)
    { // decode line sensor message

        // advance to first parameter
        if (strlen(p1) > 4)
            p1 += 4;
        else
            return false;

        // get data
        dataLock.lock();
        // time in seconds
    var1 = (int)strtol(p1, (char **)&p1, 10); // var1
    var2 = (int)strtol(p1, (char **)&p1, 10); // var2
    var3 = (int)strtol(p1, (char **)&p1, 10); // var3
    var4 = (int)strtol(p1, (char **)&p1, 10); // var4
    var5 = (int)strtol(p1, (char **)&p1, 10); // var5
    var6 = (int)strtol(p1, (char **)&p1, 10); // var6
    var7 = (int)strtol(p1, (char **)&p1, 10); // var7
    var8 = (int)strtol(p1, (char **)&p1, 10); // var8
    var9 = (int)strtol(p1, (char **)&p1, 10); // var9
        dataLock.unlock();
    }
    else
        used = false;
    //
    return used;
}
