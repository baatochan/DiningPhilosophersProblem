//
// Created by barto on 13.03.18.
//

#define numberOfPhilosophers 5

#include <iostream>
#include <unistd.h>
#include "Program.h"

using namespace std;

Philosopher* Program::philosophers[numberOfPhilosophers];
std::thread Program::threads[numberOfPhilosophers];

time_t Program::startTime;

void Program::start() {
	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		Program::philosophers[i] = new Philosopher(i);
	}


	cout<<"Time | ";
	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		cout << "Philosopher "<<i;
		if (i < numberOfPhilosophers - 1)
			cout<<" | ";
		else
			cout<<endl;
	}
	for (unsigned int i = 0; i < 77; i++) {
		cout << "-";
	}
	cout<<endl;

	time(&startTime);

	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		threads[i] = philosophers[i]->spawnThread();
	}

	bool run = true;
	while (run) {
		run = showPhilosophersStatus();
		usleep(250000);
	}

	for (auto &thread : threads) {
		thread.join();
	}
}

bool Program::showPhilosophersStatus() {
	time_t currentTime;
	time(&currentTime);

	string diffTime = to_string((int)difftime(currentTime, startTime));

	cout<<diffTime;
	for (int i = 0; i < (5 - diffTime.length()); i++) {
		cout<<" ";
	}
	cout<<"| ";

	bool shouldTerminate = false;
	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		if (i == 0) {
			if (philosophers[i]->state == 3)
				shouldTerminate = true;
			else
				shouldTerminate = false;
		} else {
			if (shouldTerminate && philosophers[i]->state == 3)
				shouldTerminate = true;
			else
				shouldTerminate = false;
		}

		if (philosophers[i]->state == 3) {
			cout<<"Dead";
			cout<<"         ";

		} else if (philosophers[i]->state == 2) {
			cout<<"Eating";
			cout<<"       ";
		} else if (philosophers[i]->state == 1) {
			cout<<"Thinking";
			cout<<"     ";
		} else if (philosophers[i]->state == 0)
			cout<<"Not yet start";
		else {
			cout<<"Error!";
			cout<<"       ";
		}
		if (i < numberOfPhilosophers - 1)
			cout<<" | ";
		else
			cout<<endl;
	}

	return !shouldTerminate;
}
