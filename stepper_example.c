// gcc -o stepper_example stepper_example.c -lwiringPi
// sudo ./stepper_example

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STEPS_PER_REVOLUTION 2048
#define REVOLUTIONS_PER_MINUTE 30
#define STEP_DELAY (60000000 / (STEPS_PER_REVOLUTION * REVOLUTIONS_PER_MINUTE))

// Define the GPIO pins connected to the stepper motor driver
//int motorPins[4] = {0, 2, 3, 1}; // WiringPi pin numbering for GPIO 17, 27, 22, 18
int motorPins[4] = {21, 22, 23, 24}; // WiringPi pin numbering for GPIO 21, 22, 23, 24,

// Stepper motor sequence for 28BYJ-48 (half-step mode)
int stepSequence[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}};

void stepMotor(int step) {
    for (int i = 0; i < 4; i++) {
        digitalWrite(motorPins[i], stepSequence[step][i]);
    }
}

void step(int steps) {
    int direction = 1;
    int stepIndex;
    
    if(steps < 0){
        direction = -1;
        steps = -steps;
    }
    
    for (int i = 0; i < steps; i++) {
        if(direction > 0){
            stepIndex = i % 8;
        } else {
            stepIndex = 7 - (i % 8);
        }
        stepMotor(stepIndex);
        usleep(STEP_DELAY);
    }
    
}

int main() {
    // Initialize wiringPi and set up GPIO pins
    if (wiringPiSetup() == -1) {
        printf("WiringPi setup failed!\n");
        return 1;
    }
    for (int i = 0; i < 4; i++) {
        pinMode(motorPins[i], OUTPUT);
    }

    while (1) {
        printf("Clockwise\n");
        step(STEPS_PER_REVOLUTION);
        usleep(500000);

        

        printf("Counterclockwise\n");
        step(-1*STEPS_PER_REVOLUTION);
        usleep(500000);
    }
    return 0;
}


