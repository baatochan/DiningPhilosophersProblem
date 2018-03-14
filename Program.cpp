//
// Created by barto on 13.03.18.
//

#include <iostream>
#include <thread>
#include <conio.h>
#include "Program.h"

using namespace std;

void Program::start() {

	char c;
	std::cout<<"press esc to exit! "<<std::endl;
	while(true)
	{
		cout<<"xxx";
		c=getch();
		if (c=='q')
			break;
	}
}
