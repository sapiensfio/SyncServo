#ifndef SyncServo
#define SyncServo_h

#include "Arduino.h"

class SyncServo {
  public:
    SyncServo();
    /**
     * Sets debug mode.
     * @param enabled True to enable debug mode, false to disable it.
     */ 
    void debug(boolean enabled);
    /**
     * Sets and intialises a servo.
     * @param pinNumber The pin number which the servo is attached to.
     */
    boolean initialiseServo(int pinNumber);
    /**
     * Sets and intialises a servo.
     * @param pinNumber The pin number which the servo is attached to.
     * @param minPos    The minimum position the servo is permitted to move to.
     * @param maxPos    The maximum position the servo is permitted to move to.
     * @return True if the servo was initialised successfully.
     */
    boolean initialiseServo(int pinNumber, int minPos, int maxPos);
    /**
     * Increments all servos to their next position. This method should be called in the "loop" function of the Arduino sketch.
     **/
    void incrementServos();
     /**
     * Sets the position of a servo.
     * @param pinNumber The pin number of the servo to set.
     * @param pos The value to send to the servo for positioning (0-180).
     */
    void setServo(int pinNumber, int pos);
    /**
     * Sets the position of a servo with a given speed.
     * @param pinNumber The pin number of the servo to set.
     * @param pos The value to send to the servo for positioning (0-180).
     * @param spd The speed to move the servo (0-9). A value of 0 stops the servo. 
     */ 
    void setServo(int pinNumber, int pos, int spd);
    /**
     * Returns the current position of a servo
     * @param pinNumber The pin number of the servo.
     * @return The position value of the servo (0-180).
     */ 
    int getServoPos(int pinNumber);
    /**
     * Returns the position the servo is currently moving to.
     * @param pinNumber The pin number of the servo.
     * @return The position value to the servo is currently moving to (0-180).
     */
    int getServoTargetPos(int pinNumber);
    
  private:
    boolean _debug; // Enter debug mode (prints messages via Serial Communication).
    unsigned int _servoDelay; // Minimum no. of milliseconds per degree for any given servo.
    LinkedList<ServoUnit*> _servos; 
    unsigned long _servoTime;
    /**
     * Returns a reference to the ServoUnit object corresponding to the supplied pin number.
     * @param pinNumber The pin number corresponding to the ServoUnit reference we wish to receive.
     * @return ServoUnit* A pointer to the ServoUnit object at the supplied pin number.
     */
    ServoUnit* _getServoByPin(int pinNumber);
  
};
    
#endif
