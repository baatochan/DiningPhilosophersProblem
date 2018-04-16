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

	while (!(terminate && queue.size() == 0)) {
		//cout<<"xxx"<<endl;
		setState(1);
		waiterSleep.wait(uniqueLock, [this] {return checkQueue;});
		setState(2);
		forksMutex.unlock();
		forksMutex.lock();
		checkQueue = false;
		int i = 0;
		for (auto &philosopher : queue) {
			if (philosopher == nullptr) continue;
			int id = philosopher->getId();
			int left = id;
			int right = id + 1;
			if (right == numberOfPhilosophers)
				right = 0;
			//cout<<"Id: "<<i<<"; Philos: "<<id<<"; forks: "<<(forks[left] && forks[right])<<endl;
			if (forks[left] && forks[right]) {
				forks[left] = false;
				forks[right] = false;
				philosopher->wakeUp();
				queue.erase(queue.begin() + i);
				i--;
			}
			i++;
		}
		forksMutex.unlock();
	}
	setState(3);
}

void Waiter::askForForks(Philosopher* p) {
	//if (p == nullptr) return;
	queue.push_back(p);
	checkQueue = true;
	waiterSleep.notify_all();
}

void Waiter::returnForks(Philosopher* p) {
	int id = p->getId();
	//cout<<"koniec: "<<id<<endl;
	int left = id;
	int right = id + 1;
	if (right == numberOfPhilosophers)
		right = 0;
	forksMutex.unlock();
	forksMutex.lock();
		forks[left] = true;
		forks[right] = true;
	forksMutex.unlock();
	checkQueue = true;
	waiterSleep.notify_all();
}

void Waiter::setTerminate(bool terminate) {
	Waiter::terminate = terminate;
}

std::thread Waiter::spawnThread() {
	return std::thread([this] { this->start(); });
}

void Waiter::wakeUp() {
	checkQueue = true;
	waiterSleep.notify_all();
}

unsigned char Waiter::getState() const {
	return state;
}

const vector<bool> &Waiter::getForks() const {
	return forks;
}
