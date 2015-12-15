
#include <omp.h>
#include <stdio.h>
#include <iostream>

// To read files
#include <fstream>

// QAP Solver
#include "QAP.h"

// LOGS
#include "LOG.h"

using namespace std;

int main(int argc, char * argv[])
{

	LOG_ON = true;

	cout << "Starting!\n";

	QAP problem;

	problem.readFile("data/chr15a.dat");

}
