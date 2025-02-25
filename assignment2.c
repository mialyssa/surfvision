#include "assignment1.h"
#include "assignment2.h"
#include "workload.h"
#include "scheduler.h"
#include "governor.h"

#include <stdio.h>
#include <limits.h>


// Helper Functions for energy calculation
#define HI_FREQ_PWR 2.0
#define LOW_FREQ_PWR 1.2
#define IDLE_PWR 0.05

double total_en_low_freq = 0;
double total_en_hi_freq = 0;
double total_en_idle = 0;

double calc_energy(double power, long long time_us){
	double time_s = time_us / 1e6;
	return power * time_s;
}

void get_energy(){
	printDBG("Total Energy for task exec (hi-freq): %.4f J\n", total_en_hi_freq);
	printDBG("Total Energy for task exec (low-freq): %.4f J\n", total_en_low_freq);
	printDBG("Total Energy for idle: %.4f J\n", total_en_idle);
}

void track_energy(long long execTime, long long idleTime, int freq){
	double energy;
	
	if(freq == 1){
		energy = calc_energy(HI_FREQ_PWR, execTime);
		//printDBG("Energy for task exec (hi-freq): %.4f J\n", energy);
		total_en_hi_freq += energy;
	} else {
		energy = calc_energy(LOW_FREQ_PWR, execTime);
		//printDBG("Energy for task exec (low-freq): %.4f J\n", energy);
		total_en_low_freq += energy;
	}
	
	energy = calc_energy(IDLE_PWR, idleTime);
	//printDBG("Energy for idle time: %.4f J\n", energy);
	total_en_idle += energy;
}

void check_deadline(long long execTime, int taskID){
	if(execTime > workloadDeadlines[taskID]){
		printDBG("Task %d missed deadline\n", taskID);
	}
}


// Note: Deadline of each workload is defined in the "workloadDeadlines" variable.
// i.e., You can access the dealine of the BUTTON thread using workloadDeadlines[BUTTON]

// Assignment: You need to implement the following two functions.

// learn_workloads(SharedVariable* v):
// This function is called at the start part of the program before actual scheduling
// - Parameters

// sv: The variable which is shared for every function over all threads
static long long execTimes[NUM_TASKS] = {0};

void learn_workloads(SharedVariable* v) {
	
	set_by_max_freq();
	
	for(int i = 0; i < NUM_TASKS; i++){
		long long startTime = get_current_time_us();
		
		switch(i){
			case BUTTON: thread_button(v); break;
			case TWOCOLOR: thread_twocolor(v); break;
			case MOTION: thread_motion(v); break;
			case ENCODER: thread_encoder(v); break;
			case SOUND: thread_sound(v); break;
			case RGBCOLOR: thread_rgbcolor(v); break;
			case ALED: thread_aled(v); break;
			case BUZZER: thread_buzzer(v); break;
		}
		
		long long endTime = get_current_time_us();
		execTimes[i] = endTime - startTime;
	}
	
	set_by_min_freq();
	
}


// select_task(SharedVariable* sv, const int* aliveTasks):
// This function is called while runnning the actual scheduler
// - Parameters
// sv: The variable which is shared for every function over all threads
// aliveTasks: an array where each element indicates whether the corresponed task is alive(1) or not(0).
// idleTime: a time duration in microsecond. You can know how much time was waiting without any workload
//           (i.e., it's larger than 0 only when all threads are finished and not reach the next preiod.)
// - Return value
// TaskSelection structure which indicates the scheduled task and the CPU frequency
TaskSelection select_task(SharedVariable* sv, const int* aliveTasks, long long idleTime) {
	
	static int prev_selection = -1;
	
	TaskSelection sel;
	sel.task = -1;
	sel.freq = 1;
		
	long long curTime = get_scheduler_elapsed_time_us();
	long long minDeadline = LLONG_MAX;
	long long execTime = 0;
	int selectedTask = -1;

	for (int i = 0; i < NUM_TASKS; i++) {
		if (aliveTasks[i] == 1) {
			prev_selection = i;
			
			if(workloadDeadlines[i] < minDeadline){
				minDeadline = workloadDeadlines[prev_selection];
				selectedTask = prev_selection;
			}
		}
	}
	
	int freq = (selectedTask % 2 == 0) ? 1 : 0;
	track_energy(execTime, idleTime, sel.freq);
	check_deadline(execTime, sel.task);
	
	if(selectedTask != -1){
		sel.task = selectedTask;
		if(idleTime > 100000){
			sel.freq = 0;
		} else {
			sel.freq = 1;
		}
	}
	
//	printDBG("Total Energy for task exec (hi-freq): %.4f J\n", total_en_hi_freq);
//	printDBG("Total Energy for task exec (low-freq): %.4f J\n", total_en_low_freq);
//	printDBG("Total Energy for idle: %.4f J\n", total_en_idle);

    return sel;
}

