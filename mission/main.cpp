/*

 Copyright © 2022 DTU, Christian Andersen jcan@dtu.dk

 The MIT License (MIT)  https://mit-license.org/

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the “Software”), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
 is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies
 or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE. */

#include <iostream>
#include <string>
#include <fstream>

#include "src/ubridge.h"
#include "src/uvision.h"
#include "src/upose.h"
#include "src/uirsensor.h"
#include "src/ulinesensor.h"
#include "src/ucomment.h"
#include "src/ustate.h"
#include "src/uplay.h"
#include "src/uevent.h"
#include "src/ujoy.h"

// to avoid writing std::
using namespace std;

bool setup(int argc, char **argv)
{ // check for command line parameters
    for (int i = 1; i < argc; i++)
    { // check for command line parameters
        // for process debug
        if (strcmp(argv[i], "help") == 0)
        {
            printf("-----\n# User mission command line help\n");
            printf("# usage:\n#   ./user_mission [help] [ball] [show] [aruco] [videoX]\n-----\n");
            return false;
        }
    }
    // connect to robot hardware using bridge
    bridge.setup("127.0.0.1", "24001", argc, argv);
    if (true or bridge.connected)
    { /// call setup for data structures
        pose.setup();
        lineSensor.setup();
        irSensor.setup();
        comment.setup();
        state.setup();
        vision.setup(argc, argv);
        event.setup();
        joy.setup();
        printf("# Setup finished OK\n");
    }
    else
        printf("# Setup failed\n");
    sound.say("me?... I am a depressed robot.", 0.1);
    //   while (sound.isSaying())
    //     usleep(100000);
    // a bit of background music
    sound.play("/home/local/Music/music.mp3", 0.05);
    return true;
}

// void step1()
// {
//     cout<<"step 1"<<"\n";

//     // remove old mission
//     bridge.tx("regbot mclear\n");

//     // clear events received from last mission
//     event.clearEvents();

//     // read mission lines from file
//     std::ifstream input("./static/step_1.txt");
//     std::string line;

//     // add mission lines
//     while( std::getline( input, line ) ) {
//         std::string message = "regbot madd " + line + "\n";

//         cout << message;
//         bridge.tx(message.c_str());
//     }

//     // start this mission
//     bridge.tx("regbot start\n");
//     // wait until finished
//     //
//     cout << "Waiting for step 1 to finish (event 0 is send, when mission is finished)\n";
//     event.waitForEvent(0);
// }

void step(std::string mission_file)
{
    cout << "step: " << mission_file << "\n";

    // remove old mission
    bridge.tx("regbot mclear\n");

    // clear events received from last mission
    event.clearEvents();

    // read mission lines from file
    std::ifstream input("./static/" + mission_file + ".txt");
    std::string line;

    // add mission lines
    while (std::getline(input, line))
    {
        if (line.front() != '#')
        {
            std::string message = "regbot madd " + line + "\n";
            // cout << message;
            bridge.tx(message.c_str());
        }
    }

    // start this mission
    bridge.tx("regbot start\n");
    // wait until finished
    //
    cout << "Waiting for step : " << mission_file << " to finish (event 0 is send, when mission is finished)\n";
    event.waitForEvent(0);
}

void step3()
{
    sound.say(". Step three.", 0.3);
    // remove old mission
    bridge.tx("regbot mclear\n");
    // clear events received from last mission
    event.clearEvents();

    bool gotNewestFrame = vision.processImage(3);

    // start this mission
    bridge.tx("regbot:# start\n");
    // wait until finished
    //
    cout << "Waiting for step 1 to finish (event 0 is send, when mission is finished)\n";
    event.waitForEvent(0);
    //   sound.say(". Step one finished.");
}

void step4()
{
    cout << "Step 4\n";

    // sound.say(". Step four.", 0.3);
    // remove old mission
    bridge.tx("regbot mclear\n");
    // clear events received from last mission
    event.clearEvents();

    // start this mission
    bridge.tx("regbot:livn get\n");
    bridge.tx("regbot:ir get\n");
    // bridge.tx("regbot sub liwi 30\n");
    // wait until finished
    //
    //   cout << "Waiting for step 1 to finish (event 0 is send, when mission is finished)\n";
    event.waitForEvent(0);
    //   sound.say(". Step one finished.");
}

int main(int argc, char **argv)
{
    if (setup(argc, argv))
    { // start mission
        std::cout << "# Robobot mission starting ...\n";
        //
        // step("mission_blob");
        step("guillotine_ramp");
        step("axe");
        step("racetrack");
        step("goto_roundabout");
        // step("roundabout_start_debug");
        step("roundabout");
        //
        step("go_to_tunnel");
        std::cout << "# Robobot mission finished ...\n";
        // remember to close camera
        vision.stop();
        sound.say("I am finished... sorry danish.", 0.2);
        while (sound.isSaying())
            sleep(1);
        bridge.tx("regbot mute 1\n");
    }
    return 0;
}
