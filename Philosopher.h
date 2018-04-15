//
// Created by baatochan on 3/14/18.
//

#ifndef DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H
#define DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H


#include <thread>
#include <mutex>
#include <condition_variable>

class Waiter;

class Philosopher {
private:
	unsigned int id;

	std::mutex * stateMutex;
	unsigned char state; // 0 - not started yet; 1 - thinking; 2 - sleeping (waiting for forks); 3 - eating; 4 - dead

	bool forksAvailable;

	void setState(unsigned char state);

	Waiter* waiter;

	std::mutex* philosopherMutex;
	std::condition_variable* philosopherSleep;
	std::unique_lock<std::mutex>* uniqueLock;

	void think(unsigned int seconds);

	void eat();

	void live();

public:

	Philosopher(unsigned int id, Waiter* waiter);

	std::thread spawnThread();

	unsigned char getState() const;

	unsigned int getId() const;

	void wakeUp();
};


#endif //DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H
