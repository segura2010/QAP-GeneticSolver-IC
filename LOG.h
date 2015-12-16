
#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <iostream>

using namespace std;

bool LOG_ON = false;
void LOG(string str)
{
	if(LOG_ON)
		cout << "[LOGGER] " << str << endl;
}

void LOG(char *str)
{
	if(LOG_ON)
		cout << "[LOGGER] " << str << endl;
}

#endif