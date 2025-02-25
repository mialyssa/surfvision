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
    //while (1) {
        if (sv->runningState) {
            int motion = digitalRead(PIN_MOTION);
            sv->motionDetected = motion;
        }
        //delay(100);
    //}
}

// 3. Microphone Sound Sensor
void body_sound(SharedVariable* sv) {
    //while (1) {
        if (sv->runningState && digitalRead(PIN_SOUND) == DETECT_SOUND) {
            body_buzzer(sv);
        }
        //delay(100);
    //}
}

// 4. Rotary Encoder
void body_encoder(SharedVariable* sv) {
    //while (1) {
        if (sv->runningState) {
            if (digitalRead(PIN_ROTARY_CLK) == LOW) {
                sv->lastEncoderDirection = CLOCKWISE;
            } else if (digitalRead(PIN_ROTARY_DT) == LOW) {
                sv->lastEncoderDirection = COUNTER_CLOCKWISE;
            }
        }
        //delay(50);
    //}
}

// 5. DIP two-color LED
void body_twocolor(SharedVariable* sv) {
    if(sv->runningState) {
        digitalWrite(PIN_DIP_RED, HIGH);
        digitalWrite(PIN_DIP_GRN, LOW);
    } else {
        digitalWrite(PIN_DIP_RED, LOW);
        digitalWrite(PIN_DIP_GRN, HIGH);
    }
}

// 6. SMD RGB LED
void body_rgbcolor(SharedVariable* sv) {
    //while (1) {
        if (sv->runningState) {
            if (sv->lastEncoderDirection == CLOCKWISE) {
                if(sv->motionDetected){
                    softPwmWrite(PIN_SMD_RED, 128);
                    softPwmWrite(PIN_SMD_GRN, 255);
                    softPwmWrite(PIN_SMD_BLU, 0);
                } else {
                    softPwmWrite(PIN_SMD_RED, 255);
                    softPwmWrite(PIN_SMD_GRN, 0);
                    softPwmWrite(PIN_SMD_BLU, 0);
                }
            } else {
                if(sv->motionDetected){
                    softPwmWrite(PIN_SMD_RED, 0);
                    softPwmWrite(PIN_SMD_GRN, 255);
                    softPwmWrite(PIN_SMD_BLU, 255);
                } else {
                    softPwmWrite(PIN_SMD_RED, 238);
                    softPwmWrite(PIN_SMD_GRN, 0);
                    softPwmWrite(PIN_SMD_BLU, 200);
                }
            }
        } else {
            softPwmWrite(PIN_SMD_RED, 0);
            softPwmWrite(PIN_SMD_GRN, 0);
            softPwmWrite(PIN_SMD_BLU, 0);
        }
        //delay(100);
    //}
}

// 7. Auto-flash LED
void body_aled(SharedVariable* sv) {
    //while (1) {
        if (sv->runningState) {
            digitalWrite(PIN_ALED, HIGH);
        } else {
            digitalWrite(PIN_ALED, LOW);
        }
        //delay(100);
    //}
}

// 8. Buzzer
void body_buzzer(SharedVariable* sv) {
    if(sv->runningState){
        digitalWrite(PIN_BUZZER, HIGH);
        //delay(300);
        digitalWrite(PIN_BUZZER, LOW);
    }
}
