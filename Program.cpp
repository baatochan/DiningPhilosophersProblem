//
// Created by barto on 13.03.18.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include "Program.h"
#include "WaitForInput.h"

using namespace std;

int Program::numberOfPhilosophers = 5;

Waiter* Program::waiter = new Waiter(Program::numberOfPhilosophers);

vector<Philosopher*> Program::philosophers;
vector<thread> Program::threads;

bool Program::fileExport = false;
bool Program::shouldTerminate = false;

time_t Program::startTime;

void Program::start() {
	cout<<"Save simulation output to file? [Y/n]: ";
	char temp = 'n';
	cin>>temp;
	if (temp == 'Y' || temp == 'y') fileExport = true;

	fstream* file;

	if (fileExport) {
		string path = to_string(time(0));
		path += "-DiningPhilosophersProblem-" + to_string(numberOfPhilosophers) + ".txt";

		file = new fstream(path, fstream::out);

		if (!file->is_open()) {
			cout << "There was a problem with creating a file. The app will continue without saving the output into a file." << endl;
		} else {
			cout << "Saving a simulation output to: " << path << endl;
		}
	}

	thread waiterThread = waiter->spawnThread();

	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		philosophers.push_back(new Philosopher(i, waiter));
	}

	string buffer = "";

	buffer = getHeader();

	cout<<buffer;
	if (fileExport) (*file)<<buffer;

	time(&startTime);

	for (auto &philosopher : philosophers) {
		threads.emplace_back(philosopher->spawnThread());
	}

	WaitForInput wfi(&philosophers);
	thread waitThread = wfi.spawnThread();

	while (!shouldTerminate) {
		buffer = getThreadsStatus();

		cout<<buffer;
		if (fileExport) (*file)<<buffer;

		this_thread::sleep_for(chrono::milliseconds(250));
	}

	waitThread.join();

	waiter->setTerminate(true);

	for (int i = 0; i <threads.size(); i++) {
		threads[i].join();
	}

	waiter->wakeUp();
	waiterThread.join();

	buffer = "Simulation over.\n";

	cout<<buffer;
	if (fileExport) (*file)<<buffer;
	if (fileExport) file->close();
}

string Program::getThreadsStatus() {
	string output = "";

	time_t currentTime;
	time(&currentTime);

	string diffTime = to_string((int) difftime(currentTime, startTime));

	output += diffTime;
	for (int i = 0; i < (5 - diffTime.length()); i++) {
		output += " ";
	}
	output += "| ";

	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		if (i == 0) {
			if (philosophers[i]->getState() == 4)
				shouldTerminate = true;
			else
				shouldTerminate = false;
		} else {
			if (shouldTerminate && philosophers[i]->getState() == 4)
				shouldTerminate = true;
			else
				shouldTerminate = false;
		}

		if (philosophers[i]->getState() == 4) {
			output += "Dead";
			output += "         ";

		} else if (philosophers[i]->getState() == 3) {
			output += "Eating";
			output += "       ";
		} else if (philosophers[i]->getState() == 2) {
			output += "Waiting";
			output += "      ";
		} else if (philosophers[i]->getState() == 1) {
			output += "Thinking";
			output += "     ";
		} else if (philosophers[i]->getState() == 0)
			output += "Not yet start";
		else {
			output += "Error!";
			output += "       ";
		}
		output += " | ";
	}

	if (waiter->getState() == 3) {
		output += "Dead";
		output += "         ";

	} else if (waiter->getState() == 2) {
		output += "Checking";
		output += "     ";
	} else if (waiter->getState() == 1) {
		output += "Sleeping";
		output += "     ";
	} else if (waiter->getState() == 0)
		output += "Not yet start";
	else {
		output += "Error!";
		output += "       ";
	}

	output += " | ";
	vector<bool> forks = waiter->getForks();

	for(int i = 0; i < forks.size(); i++) {
		if (forks[i]) {
			output += "Free";
			output += "    ";

		} else if (!forks[i]) {
			output += "Occupied";
			output += "";
		} else {
			output += "Error!";
			output += "  ";
		}
		if (i < numberOfPhilosophers - 1)
			output += " | ";
		else
			output += "\n";
	}

	return output;
}

string Program::getHeader() {
	string output = "";

	output += "Time | ";
	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		output += "Philosopher " + to_string(i);
		output += " | ";
	}
	output += "Waiter        | ";
	for (unsigned int i = 0; i < numberOfPhilosophers; i++) {
		output += "Fork " + to_string(i) + "  ";
		if (i < numberOfPhilosophers - 1)
			output += " | ";
		else
			output += "\n";
	}
	for (unsigned int i = 0; i < 155; i++) {
		output += "-";
	}
	output += "\n";

	return output;
}
