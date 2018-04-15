//
// Created by barto on 13.03.18.
//

#ifndef DININGPHILOSOPHERSPROBLEM_PROGRAM_H
#define DININGPHILOSOPHERSPROBLEM_PROGRAM_H


#include <thread>
#include <vector>
#include "Philosopher.h"

class Program {
private:
	static int numberOfPhilosophers;

	static std::vector<Philosopher> philosophers;
	static std::vector<std::thread> threads;

	static time_t startTime;
public:
	static void start();

private:
	static void showHeader();

	static bool showPhilosophersStatus();
};


#endif //DININGPHILOSOPHERSPROBLEM_PROGRAM_H
