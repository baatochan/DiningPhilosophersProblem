//
// Created by baatochan on 3/14/18.
//

#ifndef DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H
#define DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H


#include <thread>

class Philosopher {
private:
	unsigned int id;

	bool leftFork; //false if used, true if free
	bool rightFork;

	void think(unsigned int seconds);

	void eat();
public:
	unsigned char state; // 0 - not started yet; 1 - thinking; 2 - eating; 3 - dead

	Philosopher(unsigned int id);

	void live();

	std::thread spawnThread();
};


#endif //DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H
