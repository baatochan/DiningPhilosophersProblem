//
// Created by baatochan on 3/14/18.
//

#ifndef DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H
#define DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H


class Philosopher {
private:
    unsigned int id;

    bool leftFork; //false if used, true if free
    bool rightFork;

    bool state; //false if thinking, true if eating

    void think(unsigned int seconds);
    void eat();

public:
    Philosopher(unsigned int id);

    void live();
};


#endif //DININGPHILOSOPHERSPROBLEM_PHILOSOPHER_H
