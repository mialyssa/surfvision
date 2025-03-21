#include "assignment1.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

void init_shared_variable(SharedVariable* sv) {
    sv->runningState = 1;
// You can initialize the shared variable if needed.
}

void ledInit(void) {
    pinMode(PIN_ALED, OUTPUT);
    pinMode(PIN_SERVO, OUTPUT);
    pinMode(PIN_STEPPER, OUTPUT);
}

void init_sensors(SharedVariable* sv) {
// .......
    
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_MOTION, INPUT);
    pinMode(PIN_CAMERA, INPUT);
    pinMode(PIN_TILTBALL, INPUT);

    pullUpDnControl(PIN_TILTBALL, PUD_UP);
    
    ledInit();
    
}

// 1. Button
void body_button(SharedVariable* sv) {
    printf("Yob\n");
    //while (1) {
        if (digitalRead(PIN_BUTTON) == LOW) { // Button pressed
            sv->runningState = !sv->runningState;
            //printf("System %s\n", sv->runningState ? "Running" : "Paused");

            if (!sv->runningState) {
                digitalWrite(PIN_ALED, LOW);
            }
            delay(50);
        }
        delay(50);
    //}
}

// 2. Camera Signal
void body_camera(SharedVariable* sv){
    // Insert code
    printf("Yoa\n");
}

// 3. Infrared Motion Sensor
void body_motion(SharedVariable* sv) {
    printf("Yoc\n");
    while (1) {
        if (sv->runningState) {
            int motion = digitalRead(PIN_MOTION);
            sv->motionDetected = motion;
        }
        delay(100);
    }
}

// 4. Tiltball Sensor
void body_tiltball(SharedVariable* sv){
    printf("Yod\n");
    // Insert code
    while (1) {
        int state = digitalRead(PIN_TILTBALL);
        
        if (state == HIGH) {    // Tilted, open circuit
            printf("Tilt detected!\n");
        } else {    // No Tilt, closed circuit
            printf("No tilt detected.\n");
        }
        
        delay(500);  // Delay to reduce CPU usage
    }
}

// 5. Servo Motor
void body_servo(SharedVariable* sv){
    printf("Yoe\n");
}

// 6. Stepper Motor
void body_stepper(SharedVariable* sv){
    // Insert code
    printf("Yof\n");
}

// 7. ALED Sensor
void body_aled(SharedVariable* sv){
    printf("Yog\n");
    // Insert code
}
