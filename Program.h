//
// Created by barto on 13.03.18.
//

#define numberOfPhilosophers 5

#ifndef DININGPHILOSOPHERSPROBLEM_PROGRAM_H
#define DININGPHILOSOPHERSPROBLEM_PROGRAM_H


#include <thread>
#include "Philosopher.h"

class Program {
private:
	static Philosopher* philosophers[numberOfPhilosophers];
	static std::thread threads[numberOfPhilosophers];

	static time_t startTime;
public:
	static void start();

	static bool showPhilosophersStatus();
};


#endif //DININGPHILOSOPHERSPROBLEM_PROGRAM_H
