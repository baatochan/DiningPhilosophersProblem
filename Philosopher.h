//
// Created by baatochan on 3/14/18.
//

#ifndef DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H
#define DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H


#include <thread>
#include <mutex>

class Philosopher {
private:
	unsigned int id;

	bool leftFork; //false if used, true if free
	bool rightFork;

	std::mutex * stateMutex;
	unsigned char state; // 0 - not started yet; 1 - thinking; 2 - eating; 3 - dead

	void setState(unsigned char state);

	void think(unsigned int seconds);

	void eat();

	void live();

public:

	Philosopher(unsigned int id);

	std::thread spawnThread();

	unsigned char getState() const;
};


#endif //DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H
