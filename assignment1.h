
#ifndef _ASSIGNMENT_BODY_
#define _ASSIGNMENT_BODY_

#include <stdint.h>

// Macros
#define TURN_ON(pin) digitalWrite(pin, 1)
#define TURN_OFF(pin) digitalWrite(pin, 0)

#define READ(pin) digitalRead(pin)
#define WRITE(pin, x) digitalWrite(pin, x)

// Constants
#define RUNNING 3
#define PAUSE 2

#define LOW 0
#define HIGH 1

#define CLOCKWISE 0
#define COUNTER_CLOCKWISE 1

#define DETECT_SOUND 1
#define NO_SOUND 0

// A. Pin number definitions (SURFVISION)
// We use 8 sensors.
//
// 0. Button
#define PIN_BUTTON 0

// 1. Camera Signal
#define CAMERA_SIGNAL 3

// 2. Infrared motion sensor
#define PIN_MOTION 4

// 3. Tilt ball switch sensor
#define PIN_TILTBALL 5

// 4. Servo Motor 
#define PIN_SERVO 6

// 5. Stepper Motor
#define PIN_STEPPER 27

// B. Shared structure
// All thread functions get a shared variable of the structure
// as the function parameter.
// If needed, you can add anything in this structure.
typedef struct shared_variable {
    int bProgramExit; // Once set to 1, the program will terminate.
    // You can add more variables if needed.
    int runningState;
    int motionDetected;
} SharedVariable;

// C. Functions
void init_shared_variable(SharedVariable* sv);
void init_sensors(SharedVariable* sv);
void body_button(SharedVariable* sv);     // Button
void body_motion(SharedVariable* sv);     // Infrared motion sensor
void body_servo(SharedVariable* sv);      // Servo Motor
void body_stepper(SharedVariable* sv);    // Stepper Motor
void body_camera(SharedVariable* sv);     // Camera Signal

#endif
