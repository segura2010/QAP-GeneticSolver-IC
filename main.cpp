
#include <omp.h>
#include <stdio.h>
#include <iostream>

// To read files
#include <fstream>

// QAP Problem
#include "QAP.h"

// Genetic Solver
#include "GeneticSolver.h"

// LOGS
#include "LOG.h"

// Random
#include "random.h"

using namespace std;

int main(int argc, char * argv[])
{

	Seed = 123456;

	char buffer[140];
	LOG_ON = true;

	cout << "Starting!\n";

	QAP problem;
	GeneticSolver solver(20, 0.2, "data/chr15a.dat");

	solver.solve(10);

}
