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
	bool state; //false if thinking, true if eating

	Philosopher(unsigned int id);

	void live();

	std::thread spawnThread();
};


#endif //DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H
