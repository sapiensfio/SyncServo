SyncServo
=========

The SyncServo (Synchronous Servos) library was developed for the Arduino to provide an easy way to control servo motors simultaneously at different speeds (servos take an input signal to control the position of their output shaft - they have no concept of "speed"). To acomplish this, the library incrementally positions servos based on a user-specified speed set for each individual servo. This allows for extra ease and versatility in controlling servos in your robotics projects! 

Please note that the library is a work in progress and, at present, does not support servos modified for continuous rotation.

Installation
------------

1. [Download](https://github.com/sapiensfio/SyncServo/archive/master.zip) the latest release from GitHub.
2. Unzip the contents of the .zip file and place the following folders into the libraries folder in your Arduino installation directory: SyncServo, ServoUnit, LinkedList. Note that you can also download the latest version of the LinkedList library [here](https://github.com/ivanseidel/LinkedList) - it has already been bundled for your convenience). 
3. Restart your Arduino IDE if it was already open. 

Getting Started
---------------

For a complete example, please refer to the sketch in the examples folder. 

Refer to SyncServo.h for method documentation.

### Basic Setup

```c++
// Include the necessary libraries. 
#include "Arduino.h"
#include "Servo.h"
#include <ServoUnit.h>
#include <LinkedList.h>
#include "SyncServo.h"

SyncServo* syncServo;

void setup() {     
   // Instantiate the syncServo class.
   syncServo = new SyncServo();

   // Attach a servo to digital pin 3.
   syncServo->initialiseServo(3);
}

void loop() {
  // Update the position of all servos if required.
  syncServo->incrementServos();
}
```

## Set the speed and position of a servo.

Servos in an Arduino sketch require an integer value from 0 to 180 for setting the position (0 and 180 represent the minimal and maximal angle of the servo respectively).

The speed is an integer value ranging from 0 to 9 (0 represents no movement and 9 represents the fastest speed). 

```c++
// For the servo attached to digital pin 3, set the position to 180 at the fastest speed.
syncServo->setServo(3, 180);

// For the servo attached to digitial pin 3, set the position to 20 and the speed to 4. 
syncServo->setServo(3, 20, 4);
```

## Get the current position of the servo.

```c++
// Gets the current position of the servo attached to digitial pin 3. 
syncServo->getServoPos(3);
```

## Get the target position of the servo.

The target position of the servo is not the actual position of the servo at the time the function is invoked (use getServoPos() for that). Instead, the target position is the one set by the user which the servo is gradually incrementing towards.

```c++
// Gets the target position of the servo attached to digitial pin 3. 
syncServo->getServoTargetPos(3);
```

## Debug mode.

Debug mode prints messages to the Serial Port. Note that the baud rate needs to be set in your sketch before this can happen.

```c++
// Enable debug mode.
syncServo->debug(true);

// Disable debug mode.
syncServo->debug(false);
```

### Version History

* ```1.0 (2016-01-04)```: Original Release.

### To Do List

* Implement a more versatile/intuitive way to set servo speed.
* Support for continuous rotation servos. 
* Callback events for when a servo has reached its target position. 
