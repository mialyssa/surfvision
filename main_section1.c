// Important! DO NOT MODIFY this file.
// You will not submit this file.
// This file is provided for your understanding of the program procedure.

// Skeleton code of CSE237A, Sensor interaction
// For more details, please see the instructions on the class website.

#include <stdio.h>
#include <pthread.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "assignment1.h"
//#include "tempmotor.h"

// Thread declaration macros
#define thread_decl(NAME) \
void* thread_##NAME(void* param) { \
	SharedVariable* pV = (SharedVariable*) param; \
	body_##NAME(pV); \
	return NULL; }

// Declare threads for each sensor/actuator function
thread_decl(button)
thread_decl(camera)
thread_decl(motion)
thread_decl(tiltball)
thread_decl(servo)
thread_decl(stepper)
thread_decl(aled)

// Thread creation and joining macros
#define thread_create(NAME) pthread_create(&t_##NAME, NULL, thread_##NAME, &v);
#define thread_join(NAME) pthread_join(t_##NAME, NULL);

int main(int argc, char* argv[]) {
	// Initialize shared variable
	SharedVariable v;
	
	// Initialize WiringPi library
	if (wiringPiSetup() == -1) {
		printf("Failed to setup wiringPi.\n");
		return 1; 
	}

	// Initialize shared variable and sensors
	init_shared_variable(&v);
	init_sensors(&v);

	// Thread identifiers
	pthread_t t_button,
			  t_camera,
			  t_motion,
			  t_tiltball,
			  t_servo,
			  t_stepper,
			  t_aled;

	// Main program loop
	while (v.bProgramExit != 1) {
		// Create sensing threads
		thread_create(button);
		thread_create(camera);
		thread_create(motion);
		thread_create(tiltball);
		thread_create(servo);
		thread_create(stepper);
		thread_create(aled);

		// Wait for all threads to finish
		thread_join(button);
		thread_join(camera);
		thread_join(motion);
		thread_join(tiltball);
		thread_join(servo);
		thread_join(stepper);
		thread_join(aled);

		// Add a slight delay between iterations
		delay(10);
	}

	printf("Program finished.\n");

	return 0;
}
