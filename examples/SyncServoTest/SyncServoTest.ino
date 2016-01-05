/**
 * An Arduino sketch to demonstrate the SyncServo library.
 * It continuously sweeps two servos simultaneously in opposite directions at
 * a slower speed.
 *
 * Author: Mitchell Bennett - 2016
 *
 */

// Include the necessary libraries. 
#include "Arduino.h"
#include "Servo.h"
#include <ServoUnit.h>
#include <LinkedList.h>
#include "SyncServo.h"

unsigned long time = 0; // Keeps track of the time in milliseconds.
boolean alternateDirection = false; // Whether or not to move the servos in their alternate direction.

SyncServo *syncServo;

void setup() {     
   // Instantiate the syncServo class.
   syncServo = new SyncServo();
   // Attach servos to pins 3 and 4.
   syncServo->initialiseServo(3);
   syncServo->initialiseServo(4);
   // Set the initial angle of the servos.
   syncServo->setServo(3, 180, 1);
   syncServo->setServo(4, 0, 1); 
}

void loop() {
  // Increment the servos.
  syncServo->incrementServos();
  
  // If one second has ellapsed...
  if(millis() - time >= 1000) {
   time = millis();
   // If alternateDirection is true, change the servos to move in the alternate direction.
   if (alternateDirection) {
     // Set the servo on pin 3 to move to position 0 at a speed of 5.
      syncServo->setServo(3, 0, 5);
      // Set the servo on pin 4 to move to position 180 at a speed of 5.
      syncServo->setServo(4, 180, 5);
    } else {
      // Set the servo on pin 3 to move to position 180 at a speed of 5.
      syncServo->setServo(3, 180, 5);
      // Set the servo on pin 4 to move to position 0 at a speed of 5.
      syncServo->setServo(4, 0, 5);
    }
    alternateDirection = !alternateDirection;
  }
}

