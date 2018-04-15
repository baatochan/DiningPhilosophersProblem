//
// Created by barto on 13.03.18.
//

#include <iostream>
#include <chrono>
#include <vector>
#include "Program.h"

using namespace std;

int Program::numberOfPhilosophers = 5;

vector<Philosopher> Program::philosophers;
vector<thread> Program::threads;

time_t Program::startTime;

void Program::start() {
	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		philosophers.emplace_back(i);
	}

	showHeader();

	time(&startTime);

	for (auto &philosopher : philosophers) {
		threads.emplace_back(philosopher.spawnThread());
	}

	bool run = true;
	while (run) {
		run = showPhilosophersStatus();
		this_thread::sleep_for(chrono::milliseconds(250));
	}

	for (auto &thread : threads) {
		thread.join();
	}
}

bool Program::showPhilosophersStatus() {
	time_t currentTime;
	time(&currentTime);

	string diffTime = to_string((int) difftime(currentTime, startTime));

	cout << diffTime;
	for (int i = 0; i < (5 - diffTime.length()); i++) {
		cout << " ";
	}
	cout << "| ";

	bool shouldTerminate = false;
	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		if (i == 0) {
			if (philosophers[i].getState() == 3)
				shouldTerminate = true;
			else
				shouldTerminate = false;
		} else {
			if (shouldTerminate && philosophers[i].getState() == 3)
				shouldTerminate = true;
			else
				shouldTerminate = false;
		}

		if (philosophers[i].getState() == 3) {
			cout << "Dead";
			cout << "         ";

		} else if (philosophers[i].getState() == 2) {
			cout << "Eating";
			cout << "       ";
		} else if (philosophers[i].getState() == 1) {
			cout << "Thinking";
			cout << "     ";
		} else if (philosophers[i].getState() == 0)
			cout << "Not yet start";
		else {
			cout << "Error!";
			cout << "       ";
		}
		if (i < numberOfPhilosophers - 1)
			cout << " | ";
		else
			cout << endl;
	}

	return !shouldTerminate;
}

void Program::showHeader() {
	cout << "Time | ";
	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		cout << "Philosopher " << i;
		if (i < numberOfPhilosophers - 1)
			cout << " | ";
		else
			cout << endl;
	}
	for (unsigned int i = 0; i < 77; i++) {
		cout << "-";
	}
	cout << endl;
}
