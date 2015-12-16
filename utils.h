#ifndef UTILS_H
#define UTILS_H

#include <omp.h>
#include <stdio.h>
#include <iostream>

// for random
#include <stdlib.h> // rand
#include <time.h> // time

#include <vector>
#include <algorithm>

// QAP Problem
#include "QAP.h"

// LOGS
#include "LOG.h"

// Random
#include "random.h"

using namespace std;


void printSolution(const vector<int> &s)
{
	cout << "[";
	for(int i=0;i<s.size();i++)
	{
		cout << s[i] << ",";
	}
	cout << "]" << endl;
}


#endif