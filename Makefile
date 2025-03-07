all:
	gcc -o main_section1 main_section1.c assignment1.c -lwiringPi -lpthread
	gcc -o tiltball_example tiltball_example.c -lwiringPi
	gcc -o stepper_example stepper_example.c -lwiringPi
	gcc -o servo_example servo_example.c -lwiringPi

clean:
	rm -rf main_section1
	rm -rf tiltball_example
	rm -rf stepper_example
	rm -rf servo_example

