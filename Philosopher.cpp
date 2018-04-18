//
// Created by baatochan on 3/14/18.
//

#include <random>
#include <chrono>
#include <mutex>
#include "Philosopher.h"
#include "Waiter.h"

using namespace std;

void Philosopher::setState(unsigned char state) {
	stateMutex.lock();
		Philosopher::state = state;
	stateMutex.unlock();
}

void Philosopher::think(unsigned int deciseconds) {
	setState(1);
	this_thread::sleep_for(chrono::milliseconds(deciseconds*100));
}

void Philosopher::eat() {
	forksAvalibityMutex.lock();
		setState(2);
		waiter->askForForks(this);
	forksAvalibityMutex.unlock();

	philosopherSleep.wait(uniqueLock, [this]{return forksAvailable;});

	forksAvalibityMutex.lock();
		setState(3);
		this_thread::sleep_for(chrono::seconds(2));
		forksAvailable = false;
		waiter->returnForks(this);
	forksAvalibityMutex.unlock();
}

void Philosopher::live() {
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(1, 100);

	uniqueLock = unique_lock<mutex>(philosopherMutex);

	while (!terminate) {
		think((unsigned int) dist(mt));
		eat();
	}
	setState(4);
}

Philosopher::Philosopher(unsigned int id, Waiter* waiter) {
	this->id = id;
	this->waiter = waiter;
	forksAvailable = false;
	terminate = false;
	setState(0);
}

std::thread Philosopher::spawnThread() {
	return std::thread([this] { this->live(); });
}

unsigned char Philosopher::getState() {
	stateMutex.lock();
		unsigned char temp = state;
	stateMutex.unlock();

	return temp;
}

unsigned int Philosopher::getId() {
	return id;
}

void Philosopher::wakeUp() {
	forksAvalibityMutex.lock();
		forksAvailable = true;
		philosopherSleep.notify_all();
	forksAvalibityMutex.unlock();
}

void Philosopher::setTerminate(bool terminate) {
	Philosopher::terminate = terminate;
}
