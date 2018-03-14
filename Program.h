//
// Created by barto on 13.03.18.
//

#ifndef DININGPHILOSOPHERSPROBLEM_PROGRAM_H
#define DININGPHILOSOPHERSPROBLEM_PROGRAM_H


#include <thread>
#include "Philosopher.h"

class Program {
private:
	static Philosopher* philosophers[5];
	static std::thread threads[5];

	static time_t startTime;
public:
	static void start();

	static void showPhilosophersStatus();
};


#endif //DININGPHILOSOPHERSPROBLEM_PROGRAM_H
