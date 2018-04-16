//
// Created by baatochan on 4/16/18.
//

#include <iostream>
#include "WaitForInput.h"

void WaitForInput::wait() {
	char c = 0;
	while (c != 'q') {
		//std::cin >> c;
		scanf(" %c", &c);
	}

	for (int i = 0; i < philosophers->size(); i++) {
		Philosopher * p = (*philosophers)[i];
		p->setTerminate(true);
	}
}

std::thread WaitForInput::spawnThread() {
	return std::thread([this] { this->wait(); });
}

WaitForInput::WaitForInput(std::vector<Philosopher *> *philosophers) {
	this->philosophers = philosophers;
}
