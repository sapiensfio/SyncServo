#include "Arduino.h"
#include "ServoUnit.h"
#include "LinkedList.h"
#include "SyncServo.h"

const int DEFAULT_MIN_POS = 0;
const int DEFAULT_MAX_POS = 180;

SyncServo::SyncServo() {
  _debug = false;
  _servoDelay = 15;
  _servoTime = 0;
  _servos = LinkedList<ServoUnit*>();
}

/**
 * Sets debug mode.
 * @param enabled True to enable debug mode, false to disable it.
 */ 
void SyncServo::debug(boolean enabled) {
  _debug = enabled;
}

 /**
   * Sets an intialises servos.
   * @param pinNumber The pin number which the servo is attached to.
   * @return True if the servo was initialised successfully.
   */
boolean SyncServo::initialiseServo(int pinNumber, int minPos = DEFAULT_MIN_POS, int maxPos = DEFAULT_MAX_POS) {
  ServoUnit* newServo;

  newServo = new ServoUnit(pinNumber, minPos, maxPos);
  newServo->setPos(minPos);
  newServo->setSpd(1);
  _servos.add(newServo);

  if(_debug) {
    Serial.println("Initialised servo on pin: " + String(pinNumber));
    Serial.println("Total servos set: " + String(_servos.size()));
  }
  return true;
}

 /**
   * Increments all servos to their next position. This method should be called in the "loop" function of the Arduino sketch.
   **/
void SyncServo::incrementServos() {
  ServoUnit* servo;

  if(millis() - _servoTime >= _servoDelay) {
    _servoTime = millis();
    
    // Increment each of the servos.
    for(int i = 0; i < _servos.size(); i++) {
      servo = _servos.get(i);

       // If the servo's current position is within a threshold of the target position then stop.
      if(servo->getPos() < servo->getTargetPos() + servo->getSpd() && servo->getPos() > servo->getTargetPos() - servo->getSpd()){
        servo->setPos(servo->getPos());
      // If the servo's current position is less than than the target position then increase the servo's position.
      } else if(servo->getPos() < servo->getTargetPos()){
        // If the servo attempts to exceed the maximum position it can rotate, then set it to this maximum position.
        if(servo->getPos() + servo->getSpd() >= servo->getMaxPos()){
          servo->setPos(servo->getMaxPos());
        // Otherwise increment the servo.
        } else {
          servo->setPos(servo->getPos() + servo->getSpd());
        }
      // If the servo's current position is less than the target position then decrease the servo's position.
      } else if (servo->getPos() > servo->getTargetPos()){
        // If the servo attempts to exceed the minimum position it can rotate, then set it to this minimum position.
        if(servo->getPos() - servo->getSpd() <= servo->getMinPos()){
          servo->setPos(servo->getMinPos());
        // Otherwise decrement the servo.
        } else {
          servo->setPos(servo->getPos() - servo->getSpd());
        }
      }
    }
  }
}  

/**
 * Sets the position of a servo .
 * @param pinNumber The pin number of the servo to set.
 * @param pos The value to send to the servo for positioning (0-180).
 */ 
void SyncServo::setServo(int pinNumber, int pos) {
  ServoUnit* servo = _getServoByPin(pinNumber);
  servo->setTargetPos(pos);
  servo->setPos(pos);
  if(_debug) {
    Serial.println("Setting servo on pin " + String(pinNumber) + " to position ");
  }
}

/**
 * Sets the position of a servo with a given speed.
 * @param pinNumber The pin number of the servo to set.
 * @param pos The value to send to the servo for positioning (0-180).
 * @param spd The speed to move the servo (0-9). A value of 0 stops the servo. 
 */ 
void SyncServo::setServo(int pinNumber, int pos, int spd) {
  ServoUnit* servo = _getServoByPin(pinNumber);
  servo->setTargetPos(pos);
  servo->setSpd(spd);
  if(_debug) {
    Serial.println("Setting servo on pin " + String(pinNumber) + " to position " +
      String(pos) + " at speed " + String(spd));
  }
}

/**
 * Gets the current position of a servo
 * @param pinNumber The pin number of the servo.
 * @return The position value of the servo (0-180).
 */ 
int SyncServo::getServoPos(int pinNumber) {
  ServoUnit* servo = _getServoByPin(pinNumber);
  return servo->getPos();
}

/**
 * Gets the position the servo is currently moving to.
 * @param pinNumber The pin number of the servo.
 * @return The position value to the servo is currently moving to (0-180).
 */
int SyncServo::getServoTargetPos(int pinNumber) {
  ServoUnit* servo = _getServoByPin(pinNumber);
  return servo->getTargetPos();
}

/**
 * Gets a reference to the ServoUnit object corresponding to the supplied pin number.
 * @param pinNumber The pin number corresponding to the ServoUnit reference we wish to receive.
 * @return ServoUnit* A pointer to the ServoUnit object at the supplied pin number.
 */
ServoUnit* SyncServo::_getServoByPin(int pinNumber) {
  ServoUnit* servo;
  for(int i = 0; i < _servos.size(); i++) {
    if(_servos.get(i)->getPin() == pinNumber) {
      servo = _servos.get(i);
      break;
    }
  }
  return servo;
}
