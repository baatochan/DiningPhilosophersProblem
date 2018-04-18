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
	std::mutex forksQueueMutex;
	std::vector<bool> forks; //false if used, true if free
	std::vector<Philosopher*> queue;

	std::mutex stateMutex;
	unsigned char state; // 0 - not started yet; 1 - sleeping; 2 - checking queue; 3 - dead

	std::condition_variable waiterSleep;
	std::mutex waiterMutex;
	bool checkQueue;

	bool terminate;

	int numberOfPhilosophers;

	void setState(unsigned char state);

public:
	Waiter(int numberOfPhilosophers);

	void start();

	void askForForks(Philosopher* p);

	void returnForks(Philosopher* p);

	void setTerminate(bool terminate);

	std::thread spawnThread();

	unsigned char getState();

	void wakeUp();

	const std::vector<bool> getForks();
};


#endif //DININGPHILOSOPHERSPROBLEM_WAITER_H
