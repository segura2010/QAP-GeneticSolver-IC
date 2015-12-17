
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

// Local search for memetic GA
#include "LocalSearch.h"

using namespace std;

int main(int argc, char * argv[])
{

	Seed = 123456;

	char buffer[140];
	LOG_ON = true;

	// Set threads number for parallel code
	omp_set_num_threads(4);

	cout << "Starting!\n";

	int tamPob = 50;
	double mutProb = 0.3;
	GeneticSolver solver(tamPob, mutProb, "data/chr20b.dat");

	solver.lamarckianSolve(10000);

	printSolution( solver.getBestSolution() );
	cout << "Fitness: " << solver.getBestSolutionFitness() << endl;

}



