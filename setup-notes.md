# Steps for initial setup and testing of Mayfly datalogger
Ryan Cole 2023-12-18

## Setup
1. Download vscode
2. download the PlatformIO IDE extension for vscode from the extensions menu (four blocks) on the left sidebar.
    PlatformIO is a library manager for arduino that makes getting all the necessary libraries together a lot easeir
3. Clone github repo ryanpcole/EnviroDIY_Mayfly_Logger
4. create platformio.ini file in the root of the repo with the following:
        [env:mayfly]
        platform = atmelavr
        board = mayfly
        framework = arduino
        lib_ldf_mode = deep+
        lib_ignore = RTCZero
        build_flags = 
            -DSDI12_EXTERNAL_PCINT
        lib_deps = https://github.com/EnviroDIY/ModularSensors
            

Note: You may have to click on the platformio alien head to start the project if the platformio menu doesn't show up on the bottom.


## Test running code - blink examples
1. create a /src folder in the project root to store code we want to build
2. Copy /examples/blink_demo_1/blink_demo_1.ino into the /src
3. Build the file and send it to the mayfly datalogger to test that we can communicate
4. Copy /examples/blink_demo_2/blink_demo_2.ino to /src and delete blink_demo_1.ino
    This should work the same, but is slightly different code.

Success! Now we have confirmed we can send code to the mayfly and it will run the code!

## Test reading from serial monitor
1. put /examples/battery_measurement/battery_measurement.ino in /src (delete any other files)
2. build it and send to the mayfly
3. open the serial monitor. On my pc it was port /dev/ttyUSB0. I used vscode's built in serial monitor since I was not able to figure out how to change the baud rate of platformIO's serial monitor. If the serial monitor is reading gibberish, make sure the baud rate on the serial monitor matches the baud rate of the code

You may have to download the serial monitor extension to get a better interface to the arduino. Its just called "Serial Monitor" in the extension store.

Success! We can read data from the mayfly on our serial monitor!


## Test reading a sensor and the real time clock
1. put /examples/initial_demo_blink_temperature/intial_dem_blink_temperature.ino in /src
2. build and send to mayfly
    There may be an error about a missing library for the real time clock (RTC). If so, run `pio pkg install -l envirodiy/EnviroDIY_DS3231` in the terminal to install the missing library. Then build and send again.
3. open serial monitor and check that the mayfly is outputting a reasonable temperature

Congrats! We have installed a library using platformio that runs one of the components on the mayfly!


## Adding library dependencies using platformio
EnviroDIY recommends we install their entire group of libraries from github using PlatformIO.
To do this run the following command:
`pio pkg install -l https://github.com/EnviroDIY/ModularSensors`




Do the following if you can't build a file due to a missing library.

1. Read the error message or sketch to see what library dependency is missing. These are defined in the beginning of a sketch using the #include tab. If you are using vscode, then the missing dependency will probably be underlined with a red squiggle. If looking at the error message, look for something like this:

    *************************************************************************
    * Looking for Adafruit_Sensor.h dependency? Check our library registry!
    *
    * CLI  > platformio lib search "header:Adafruit_Sensor.h"
    * Web  > https://registry.platformio.org/search?q=header:Adafruit_Sensor.h
    *
    *************************************************************************


2. use the command 
`pio pkg install -l missing_package_path` 
replacing the missing_package_path with the correct package path. You can look up the available packages on the PlatformIO registry: https://registry.platformio.org/

Note: This will also add a line to the platformio.ini file for lib_deps

