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
	stateMutex->lock();
		Philosopher::state = state;
	stateMutex->unlock();
}

void Philosopher::think(unsigned int seconds) {
	setState(1);
	this_thread::sleep_for(chrono::seconds(seconds));
}

void Philosopher::eat() {
	setState(2);
	waiter->askForForks(this);
	philosopherSleep->wait(*uniqueLock, [this]{return forksAvailable;});
	setState(3);
	this_thread::sleep_for(chrono::seconds(2));
	waiter->returnForks(this);
}

void Philosopher::live() {
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(1, 10);

	uniqueLock = new unique_lock<mutex>(*philosopherMutex);

	for (int i = 0; i < 5; i++) {
		think((unsigned int) dist(mt));
		eat();
	}
	setState(4);
}

Philosopher::Philosopher(unsigned int id, Waiter* waiter) {
	this->id = id;
	this->waiter = waiter;
	forksAvailable = false;
	stateMutex = new mutex;
	setState(0);
}

std::thread Philosopher::spawnThread() {
	return std::thread([this] { this->live(); });
}

unsigned char Philosopher::getState() const {
	unique_lock<mutex> uniqueLock(*stateMutex);
	return state;
}

unsigned int Philosopher::getId() const {
	return id;
}

void Philosopher::wakeUp() {
	forksAvailable = true;
	philosopherSleep->notify_all();
}
