#include "assignment1.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

// Constants
    //SMD LED
/*    
    #define RED 1
    #define GRN 0
    #define BLU 3
    #define ALL 4
*/

void init_shared_variable(SharedVariable* sv) {
    sv->runningState = 1;
    sv->lastEncoderDirection = CLOCKWISE;
// You can initialize the shared variable if needed.
}

void ledInit(void) {
    softPwmCreate(PIN_SMD_RED, 0, 0xff);
    softPwmCreate(PIN_SMD_GRN, 0, 0xff);
    softPwmCreate(PIN_SMD_BLU, 0, 0xff);

    pinMode(PIN_DIP_RED, OUTPUT);
    pinMode(PIN_DIP_GRN, OUTPUT);

    pinMode(PIN_ALED, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
//......
//initialize SMD and DIP
}

void init_sensors(SharedVariable* sv) {
// .......
    pinMode(PIN_SMD_RED, OUTPUT);
    pinMode(PIN_SMD_GRN, OUTPUT);
    pinMode(PIN_SMD_BLU, OUTPUT);
    
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_MOTION, INPUT);
    pinMode(PIN_SOUND, INPUT);

    pinMode(PIN_ROTARY_CLK, INPUT);
    pinMode(PIN_ROTARY_DT, INPUT);
    
    ledInit();
    
}

// 1. Button
void body_button(SharedVariable* sv) {
    //while (1) {
        if (digitalRead(PIN_BUTTON) == LOW) { // Button pressed
            sv->runningState = !sv->runningState;
            //printf("System %s\n", sv->runningState ? "Running" : "Paused");

            if (!sv->runningState) {
                digitalWrite(PIN_ALED, LOW);
                digitalWrite(PIN_DIP_RED, LOW);
                digitalWrite(PIN_DIP_GRN, LOW);
                
                softPwmWrite(PIN_SMD_RED, 0);
                softPwmWrite(PIN_SMD_GRN, 0);
                softPwmWrite(PIN_SMD_BLU, 0);
                
                digitalWrite(PIN_BUZZER, LOW);
            }
            //delay(500);
        }
        //delay(50);
    //}
}

// 2. Infrared Motion Sensor
void body_motion(SharedVariable* sv) {
    while (1) {
        if (sv->runningState) {
            int motion = digitalRead(PIN_MOTION);
            sv->motionDetected = motion;
        }
        delay(100);
    }
}

// 3. Servo Motor
void body_servo(SharedVariable* sv){

}

// 4. Stepper Motor
void body_stepper(SharedVariable* sv){
    // Insert code
}

// 5. Camera Signal
void body_camera(SharedVariable* sv){
    // Insert code
}
