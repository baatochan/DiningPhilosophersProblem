//
// Created by barto on 13.03.18.
//

#ifndef DININGPHILOSOPHERSPROBLEM_PROGRAM_H
#define DININGPHILOSOPHERSPROBLEM_PROGRAM_H


#include <thread>
#include <vector>
#include "Philosopher.h"
#include "Waiter.h"

class Program {
private:
	static int numberOfPhilosophers;

	static Waiter* waiter;

	static std::vector<Philosopher*> philosophers;
	static std::vector<std::thread> threads;

	static bool fileExport;
	static bool shouldTerminate;

	static time_t startTime;
public:
	static void start();

private:
	static std::string getHeader();

	static std::string getThreadsStatus();
};


#endif //DININGPHILOSOPHERSPROBLEM_PROGRAM_H
