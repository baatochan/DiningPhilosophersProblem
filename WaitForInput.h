//
// Created by baatochan on 4/16/18.
//

#ifndef DININGPHILOSOPHERSPROBLEM_WAITFORINPUT_H
#define DININGPHILOSOPHERSPROBLEM_WAITFORINPUT_H


#include <thread>
#include <vector>
#include "Philosopher.h"

class WaitForInput {
private:
	std::vector<Philosopher*>* philosophers;
	void wait();
public:
	WaitForInput(std::vector<Philosopher*>* philosophers);
	std::thread spawnThread();
};


#endif //DININGPHILOSOPHERSPROBLEM_WAITFORINPUT_H
