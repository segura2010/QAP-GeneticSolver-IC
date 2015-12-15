
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

	vector<int> solution;
	problem.simpleSolutionInit(solution);

	char buffer[140]; sprintf(buffer, "S: %d", solution.size());
	string l = buffer;
	LOG(l);

}
