//
// Created by barto on 13.03.18.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include "Program.h"
#include "WaitForInput.h"

using namespace std;

int Program::numberOfPhilosophers = 5;

Waiter* Program::waiter = new Waiter(Program::numberOfPhilosophers);

vector<Philosopher*> Program::philosophers;
vector<thread> Program::threads;

time_t Program::startTime;

void Program::start() {
	thread waiterThread = waiter->spawnThread();

	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		philosophers.push_back(new Philosopher(i, waiter));
	}

	showHeader();

	time(&startTime);

	for (auto &philosopher : philosophers) {
		threads.emplace_back(philosopher->spawnThread());
	}

	WaitForInput wfi(&philosophers);
	thread waitThread = wfi.spawnThread();

	bool run = true;
	while (run) {
		run = showThreadsStatus();
		this_thread::sleep_for(chrono::milliseconds(250));
	}

	waitThread.join();

	waiter->setTerminate(true);

	for (int i = 0; i <threads.size(); i++) {
		threads[i].join();
	}

	waiter->wakeUp();
	waiterThread.join();
}

bool Program::showThreadsStatus() {
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
			if (philosophers[i]->getState() == 4)
				shouldTerminate = true;
			else
				shouldTerminate = false;
		} else {
			if (shouldTerminate && philosophers[i]->getState() == 4)
				shouldTerminate = true;
			else
				shouldTerminate = false;
		}

		if (philosophers[i]->getState() == 4) {
			cout << "Dead";
			cout << "         ";

		} else if (philosophers[i]->getState() == 3) {
			cout << "Eating";
			cout << "       ";
		} else if (philosophers[i]->getState() == 2) {
			cout << "Waiting";
			cout << "      ";
		} else if (philosophers[i]->getState() == 1) {
			cout << "Thinking";
			cout << "     ";
		} else if (philosophers[i]->getState() == 0)
			cout << "Not yet start";
		else {
			cout << "Error!";
			cout << "       ";
		}
		cout << " | ";
		/*if (i < numberOfPhilosophers - 1)
			cout << " | ";
		else
			cout << endl;*/
	}

	if (waiter->getState() == 3) {
		cout << "Dead";
		cout << "         ";

	} else if (waiter->getState() == 2) {
		cout << "Checking";
		cout << "     ";
	} else if (waiter->getState() == 1) {
		cout << "Sleeping";
		cout << "     ";
	} else if (waiter->getState() == 0)
		cout << "Not yet start";
	else {
		cout << "Error!";
		cout << "       ";
	}

	cout << " | ";
	vector<bool> forks = waiter->getForks();

	for(int i = 0; i < forks.size(); i++) {
		if (forks[i]) {
			cout << "Free";
			cout << "    ";

		} else if (!forks[i]) {
			cout << "Occupied";
			cout << "";
		} else {
			cout << "Error!";
			cout << "  ";
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
		cout << " | ";
		/*if (i < numberOfPhilosophers - 1)
			cout << " | ";
		else
			cout << endl;*/
	}
	cout<<"Waiter       "<<" | ";
	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		cout << "Fork " << i << "  ";
		if (i < numberOfPhilosophers - 1)
			cout << " | ";
		else
			cout << endl;
	}
	for (unsigned int i = 0; i < 155; i++) {
		cout << "-";
	}
	cout << endl;
}
