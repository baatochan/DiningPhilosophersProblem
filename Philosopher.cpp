//
// Created by baatochan on 3/14/18.
//

#include <random>
#include <chrono>
#include "Philosopher.h"

using namespace std;

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

Philosopher::Philosopher(unsigned int id) {
	this->id = id;
	leftFork = true;
	rightFork = true;
	state = 0;
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

std::thread Philosopher::spawnThread() {
	return std::thread([this] { this->live(); });
}
