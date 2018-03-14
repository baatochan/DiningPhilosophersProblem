//
// Created by barto on 13.03.18.
//

#include <iostream>
#include "Program.h"

using namespace std;

Philosopher* Program::philosophers[5];
std::thread Program::threads[5];

time_t Program::startTime;

void Program::start() {
	for (unsigned int i = 0; i < 5; i++) {
		Program::philosophers[i] = new Philosopher(i);
	}


	cout<<"Time | ";
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

	time(&startTime);

	for (unsigned int i = 0; i < 5; i++) {
		threads[i] = philosophers[i]->spawnThread();
	}

	for (auto &thread : threads) {
		thread.join();
	}
}

void Program::showPhilosophersStatus() {
	time_t currentTime;
	time(&currentTime);

	string diffTime = to_string((int)difftime(currentTime, startTime));

	cout<<diffTime;
	for (int i = 0; i < (5 - diffTime.length()); i++) {
		cout<<" ";
	}
	cout<<"| ";

	for (unsigned int i = 0; i < 5; i++) {
		if (philosophers[i]->state == 3) {
			cout<<"Dead";
			cout<<"         ";

		} else if (philosophers[i]->state == 2) {
			cout<<"Eating";
			cout<<"       ";
		} else if (philosophers[i]->state == 1) {
			cout<<"Thinking";
			cout<<"     ";
		} else if (philosophers[i]->state == 0)
			cout<<"Not yet start";
		else {
			cout<<"Error!";
			cout<<"       ";
		}
		if (i < 4)
			cout<<" | ";
		else
			cout<<endl;
	}
}
