//
// Created by barto on 16.04.18.
//

#include <iostream>
#include "Waiter.h"

using namespace std;


void Waiter::setState(unsigned char state) {
	stateMutex.lock();
		Waiter::state = state;
	stateMutex.unlock();
}

Waiter::Waiter(int numberOfPhilosophers) {
	terminate = false;
	checkQueue = false;
	this->numberOfPhilosophers = numberOfPhilosophers;

	for (int i = 0; i < numberOfPhilosophers; i++) {
		forks.push_back(true);
	}
}

void Waiter::start() {
	unique_lock<mutex> uniqueLock(waiterMutex);

	setState(1);
	while (!(terminate && queue.size() == 0)) {
		waiterSleep.wait(uniqueLock, [this] {return checkQueue;});
		forksQueueMutex.lock();
			setState(2);
			checkQueue = false;
			int i = 0;
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
					queue.erase(queue.begin() + i);
					i--;
				}
				i++;
			}
			setState(1);
		forksQueueMutex.unlock();
	}
	setState(3);
}

void Waiter::askForForks(Philosopher* p) {
	forksQueueMutex.lock();
		queue.push_back(p);

		checkQueue = true;
		waiterSleep.notify_all();
	forksQueueMutex.unlock();
}

void Waiter::returnForks(Philosopher* p) {
	int id = p->getId();
	int left = id;
	int right = id + 1;
	if (right == numberOfPhilosophers)
		right = 0;
	forksQueueMutex.lock();
		forks[left] = true;
		forks[right] = true;

		checkQueue = true;
		waiterSleep.notify_all();
	forksQueueMutex.unlock();
}

void Waiter::setTerminate(bool terminate) {
	Waiter::terminate = terminate;
}

std::thread Waiter::spawnThread() {
	return std::thread([this] { this->start(); });
}

void Waiter::wakeUp() {
	forksQueueMutex.lock();
		checkQueue = true;
		waiterSleep.notify_all();
	forksQueueMutex.unlock();
}

unsigned char Waiter::getState() {
	stateMutex.lock();
		unsigned char temp = state;
	stateMutex.unlock();

	return temp;
}

const vector<bool> Waiter::getForks() {
	forksQueueMutex.lock();
		vector<bool> temp;
		temp = forks;
	forksQueueMutex.unlock();

	return temp;
}
