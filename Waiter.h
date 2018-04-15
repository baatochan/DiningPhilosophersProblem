//
// Created by barto on 16.04.18.
//

#ifndef DININGPHILOSOPHERSPROBLEM_WAITER_H
#define DININGPHILOSOPHERSPROBLEM_WAITER_H


#include <vector>
#include <condition_variable>
#include "Philosopher.h"

class Waiter {
private:
	std::vector<bool> forks; //false if used, true if free
	std::vector<Philosopher*> queue;

	std::condition_variable waiterSleep;
	std::mutex waiterMutex;

	bool terminate;

	int numberOfPhilosophers;
public:
	Waiter(int numberOfPhilosophers);

	void start();

	void askForForks(Philosopher* p);

	void returnForks(Philosopher* p);

	void setTerminate(bool terminate);
};


#endif //DININGPHILOSOPHERSPROBLEM_WAITER_H
