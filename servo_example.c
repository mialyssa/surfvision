#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>

#define SERVO_PIN 6  // GPIO6 (WiringPi pin 6)
#define MIN_PULSE 50  // Adjust based on your servo (0-degree position)
#define MAX_PULSE 250 // Adjust based on your servo (180-degree position)
#define DELAY 500000  // Delay in microseconds (0.5 sec)

void setServoAngle(int angle) {
    int pulseWidth = MIN_PULSE + (angle * (MAX_PULSE - MIN_PULSE) / 180);
    pwmWrite(SERVO_PIN, pulseWidth);
    usleep(DELAY);  // Give servo time to move
}

int main() {
    if (wiringPiSetup() == -1) {
        printf("WiringPi setup failed!\n");
        return 1;
    }

    pinMode(SERVO_PIN, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(192);  // Set clock divider (adjust if necessary)
    pwmSetRange(2000); // Set range (adjust based on servo requirements)

    while (1) {
        printf("Moving to 0 degrees\n");
        setServoAngle(0);
        sleep(1);

        printf("Moving to 90 degrees\n");
        setServoAngle(90);
        sleep(1);

        printf("Moving to 180 degrees\n");
        setServoAngle(180);
        sleep(1);
    }

    return 0;
}
