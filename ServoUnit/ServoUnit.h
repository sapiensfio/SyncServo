#ifndef ServoUnit_h
#define ServoUnit_h

#include "Arduino.h"
#include "Servo.h"

class ServoUnit {
  public:
    ServoUnit();
    ServoUnit(int pinNumber);
    ServoUnit(int pinNumber, int minPos, int maxPos);

    /**
     * Sets the position of the servo.
     * @param pos The position value to send to the servo (0-180). 
     */
    void setPos(int pos);
    /**
     * Sets the speed of the servo.
     * @param spd The speed value to send to the servo (0-9). A value of zero stops the servo.
     */ 
    void setSpd(int spd);
    /**
     * Sets the target position of the servo (the position the servo should increment towards).
     * @param pos The target position of the servo (0-180).
     */
    void setTargetPos(int pos);
    /**
     * Returns the current position of the servo.
     * @return The position value of the servo (0-180).
     */
    int getPos();
    /**
     * Returns the current speed of the servo.
     * @return The speed of the servo (0-9).
     */
    int getSpd();
    /**
     * Returns the target position of the servo (the position the servo should increment towards).
     * @return The position the servo is incrementing towards (0-180).
     */
    int getTargetPos();
    /**
     * Returns the pin number the current servo is attached to.
     * @return The pin number assigned to the servo.
     */
    int getPin();
    /**
     * Returns the minimum position the servo is allowed to move to.
     * @return The minimum position.
     */
    int getMinPos();
    /**
     * Returns the maximum position the servo is allowed to move to.
     * @return The maximum position.
     */
    int getMaxPos();
  private:
    Servo _servo;
    int _pin;
    int _spd;
    int _targetPos;
    int _minPos;
    int _maxPos;
};
    
#endif
