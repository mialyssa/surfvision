#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define TILT_SENSOR_PIN 5  // Use GPIO 17 (WiringPi pin 0)

void setup() {
    if (wiringPiSetup() == -1) {
        printf("Failed to initialize WiringPi!\n");
        exit(1);
    }

    pinMode(TILT_SENSOR_PIN, INPUT);  // Set tilt sensor pin as input
    pullUpDnControl(TILT_SENSOR_PIN, PUD_UP);  // Enable pull-up resistor
}

void loop() {
    while (1) {
        int state = digitalRead(TILT_SENSOR_PIN);
        
        if (state == HIGH) {  // When tilted, the circuit closes
            printf("Tilt detected!\n");
        } else {
            printf("No tilt detected.\n");
        }
        
        delay(500);  // Delay to reduce CPU usage
    }
}

int main() {
    setup();
    loop();
    return 0;
}
