
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>

// Macros
#define READ(pin) digitalRead(pin)
#define WRITE(pin, x) digitalWrite(pin, x)

#define LOW 0
#define HIGH 1

typedef struct shared_variable {
    int bProgramExit; // Once set to 1, the program will terminate.
    // You can add more variables if needed.
    int runningState;
    int motionDetected;
} SharedVariable;


#define SERVO_PIN 14 // BCM GPIO 14

#define DEGREEUP 1800, 1800
#define DEGREE0 2100, 2200
#define DEGREEDOWN 2400, 2800

unsigned long elapsedTime = 0;
int frequency = 0;
int period = 0;
unsigned long startTime = 0;
int angles[2] = {2100, 2200}; // Neutral

void degreeUp(int amt){
    // 1800 1800
    
    for(int j = 0; j < amt; j++){
        angles[0] -= 200;
        angles[1] -= 300;
        for(int i=0; i < 200; i++){
            WRITE(SERVO_PIN, HIGH);

            //printf("UP angles[0] = %d\n", angles[0]);
            delayMicroseconds(angles[0]);

            WRITE(SERVO_PIN, LOW);

            //printf("UP angles[1] = %d\n", angles[1]);
            delayMicroseconds(angles[1]); 

        }
    }
}

void degreeNeutral(){
    // 2100, 2200
        for(int i=0; i < 200; i++){
            WRITE(SERVO_PIN, HIGH);
            delayMicroseconds(2100);
            //printf("ZERO angles[0] = %d\n", angles[0]);
            
            WRITE(SERVO_PIN, LOW);
            delayMicroseconds(2200); 
            //printf("ZERO angles[1] = %d\n", angles[1]);
        }
}

void degreeDown(int amt){
    // 2400 2300
    
    
    for(int j = 0; j < amt; j++){
        angles[0] += 200;
        angles[1] += 300;
    
        for(int i=0; i < 200; i++){
            WRITE(SERVO_PIN, HIGH);

            delayMicroseconds(angles[0]);
            //printf("DOWN angles[0] = %d\n", angles[0]);

            WRITE(SERVO_PIN, LOW);
            delayMicroseconds(angles[1]);    
            //printf("DOWN angles[1] = %d\n", angles[1]);
        }
    }
}

int main() {
    wiringPiSetupGpio(); // Initialize WiringPi
 
    pinMode(SERVO_PIN, OUTPUT); // Set the GPIO pin as PWM output
    
    degreeNeutral();

    delayMicroseconds(2000);
    degreeUp(1);
    printf("yo");

    delayMicroseconds(2000);
    degreeDown(2);

    degreeNeutral();
 
    printf("done\n");
 
 }
 
 