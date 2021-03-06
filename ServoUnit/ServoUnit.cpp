#include "Arduino.h"
#include "Servo.h"
#include "ServoUnit.h"

ServoUnit::ServoUnit() {
	_pin = -1;
	_spd = 0;
	_targetPos = 0;
}

ServoUnit::ServoUnit(int pinNumber) {
  _servo.attach(pinNumber); 
  _pin = pinNumber;
  _spd = 0;
  _targetPos = 0;
}

/**
 * Sets the position of the servo.
 * @param pos The position value to send to the servo (0-180). 
 */
void ServoUnit::setPos(int pos) {
  _servo.write(pos);
}

/**
 * Sets the speed of the servo.
 * @param spd The speed value to send to the servo (0-9). A value of zero stops the servo.
 */ 
void ServoUnit::setSpd(int spd) {
  _spd = spd;
}

/**
 * Sets the target position of the servo (the position the servo should increment towards).
 * @param pos The target position of the servo (0-180).
 */
void ServoUnit::setTargetPos(int pos) {
	_targetPos = pos;
}

/**
 * Gets the current position of the servo.
 * @return The position value of the servo (0-180).
 */
int ServoUnit::getPos() {
  return _servo.read();
}

/**
 * Gets the current speed of the servo.
 * @return The speed of the servo (0-9).
 */
int ServoUnit::getSpd() {
  return _spd;
}

/**
 * Gets the target position of the servo (the position the servo should increment towards).
 * @return The position the servo is incrementing towards (0-180).
 */
int ServoUnit::getTargetPos() {
  return _targetPos;
}

/**
 * Gets the pin number the current servo is attached to.
 * @return The pin number assigned to the servo.
 */
int ServoUnit::getPin() {
  return _pin;
}


