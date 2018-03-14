//
// Created by barto on 13.03.18.
//

#include <iostream>
#include "Program.h"

using namespace std;

Philosopher* Program::philosophers[5];
std::thread Program::threads[5];

void Program::start() {
	for (unsigned int i = 0; i < 5; i++) {
		Program::philosophers[i] = new Philosopher(i);
	}
	for (unsigned int i = 0; i < 5; i++) {
		cout << "Philosopher "<<i;
		if (i < 4)
			cout<<" | ";
		else
			cout<<endl;
	}
	for (unsigned int i = 0; i < 77; i++) {
		cout << "-";
	}
	cout<<endl;

	for (unsigned int i = 0; i < 5; i++) {
		threads[i] = philosophers[i]->spawnThread();
	}

	for (unsigned int i = 0; i < 5; i++) {
		threads[i].join();
	}
}

void Program::showPhilosophersStatus() {
	for (unsigned int i = 0; i < 5; i++) {
		if (philosophers[i]->state) {
			cout<<"Eating";
			cout<<"        ";
		} else {
			cout<<"Thinking";
			cout<<"      ";
		}
		if (i < 4)
			cout<<" | ";
		else
			cout<<endl;
	}
}
