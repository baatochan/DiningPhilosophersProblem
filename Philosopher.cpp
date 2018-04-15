//
// Created by baatochan on 3/14/18.
//

#include <random>
#include <chrono>
#include <mutex>
#include "Philosopher.h"

using namespace std;

void Philosopher::setState(unsigned char state) {
	stateMutex->lock();
		Philosopher::state = state;
	stateMutex->unlock();
}

void Philosopher::think(unsigned int seconds) {
	state = 1;
	this_thread::sleep_for(chrono::seconds(seconds));
}

void Philosopher::eat() {
	state = 2;
	leftFork = false;
	rightFork = false;
	this_thread::sleep_for(chrono::seconds(2));
	leftFork = true;
	rightFork = true;
}

void Philosopher::live() {
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(1, 10);

	for (int i = 0; i < 5; i++) {
		think((unsigned int) dist(mt));
		eat();
	}
	state = 3;
}

Philosopher::Philosopher(unsigned int id) {
	this->id = id;
	leftFork = true;
	rightFork = true;
	state = 0;
	stateMutex = new mutex;
}

std::thread Philosopher::spawnThread() {
	return std::thread([this] { this->live(); });
}

unsigned char Philosopher::getState() const {
	return state;
}
