# Dining Philosophers Problem
My attempt at resolving Dining Philosophers Problem done for Operating Systems (Systemy Operacyjne 2) course at the university.

Author: Bartosz Rodziewicz

My solution uses an additional waiter thread. That thread decides who should eat at the given time (given available forks and place in the queue).

Exiting the app is done on another additional thread which waits for `q` on standard input stream.

User Interface shows state of every thread and fork, updates every 250ms and is done on the main thread.

The life cycle of philosopher consists of:
* thinking (for random time - in the range of [0, 10s])
* waiting for the forks
* eating (for 2s)

The repo contains older release which solves the dining philosophers problem by giving every philosopher their own pair of forks.

You have to compile it under Linux to make it work.
