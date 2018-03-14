//
// Created by baatochan on 3/14/18.
//

#include <random>
#include <unistd.h>
#include "Philosopher.h"
#include "Program.h"

void Philosopher::think(unsigned int seconds) {
	state = false;
	Program::showPhilosophersStatus();
	sleep(seconds);
}

void Philosopher::eat() {
	state = true;
	leftFork = false;
	rightFork = false;
	Program::showPhilosophersStatus();
	sleep(2);
	leftFork = true;
	rightFork = true;
}

Philosopher::Philosopher(unsigned int id) {
	this->id = id;
	leftFork = true;
	rightFork = true;
}

void Philosopher::live() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 10);

	for (int i = 0; i < 5; i++) {
		think((unsigned int) dist(mt));
		eat();
	}
}

std::thread Philosopher::spawnThread() {
	return std::thread( [this] { this->live(); } );
}
