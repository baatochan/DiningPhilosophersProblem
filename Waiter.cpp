//
// Created by barto on 16.04.18.
//

#include "Waiter.h"

using namespace std;

Waiter::Waiter(int numberOfPhilosophers) {
	this->numberOfPhilosophers = numberOfPhilosophers;

	for (int i = 0; i < numberOfPhilosophers; i++) {
		forks.push_back(true);
	}
}

void Waiter::start() {
	unique_lock<mutex> uniqueLock(waiterMutex);

	while (!terminate && queue.size() > 0) {
		waiterSleep.wait(uniqueLock, [this] {return true;});
		for (auto &philosopher : queue) {
			int id = philosopher->getId();
			int left = id;
			int right = id + 1;
			if (right == numberOfPhilosophers)
				right = 0;
			if (forks[left] && forks[right]) {
				forks[left] = false;
				forks[right] = false;
				philosopher->wakeUp();
			}
		}
	}
}

void Waiter::askForForks(Philosopher* p) {
	queue.push_back(p);
	waiterSleep.notify_all();
}

void Waiter::returnForks(Philosopher* p) {
	int id = p->getId();
	int left = id;
	int right = id + 1;
	if (right == numberOfPhilosophers)
		right = 0;
	forks[left] = true;
	forks[right] = true;
	waiterSleep.notify_all();
}

void Waiter::setTerminate(bool terminate) {
	Waiter::terminate = terminate;
}
