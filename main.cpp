
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

	if( argc < 2 )
	{
		cout << "Usage: " << argv[0] << " QAP_data_file" << endl;
		exit(0);
	}

	Seed = 9123456;

	char buffer[140];
	LOG_ON = false;

	// Set threads number for parallel code
	omp_set_num_threads(4);

	//cout << "Starting " << argv[1] << " \n";

	int tamPob = 50, generations = 1000;
	double mutProb = 0.3;
	GeneticSolver solver(tamPob, mutProb, argv[1]);

	solver.simpleSolve(generations);
	int simpleSolution = solver.getBestSolutionFitness();
	//cout << "Simple GA: " << endl;
	//printSolution( solver.getBestSolution() );
	//cout << "Fitness: " << solver.getBestSolutionFitness() << endl;


	solver.baldwinianSolve(generations, 1000);
	int baldSolution = solver.getBestSolutionFitness();
	//cout << "Baldwinian GA: " << endl;
	//printSolution( solver.getBestSolution() );
	//cout << "Fitness: " << solver.getBestSolutionFitness() << endl;

	solver.lamarckianSolve(generations, 1000);
	int lamarkSolution = solver.getBestSolutionFitness();
	//cout << "Lamarckian GA: " << endl;
	//printSolution( solver.getBestSolution() );
	//cout << "Fitness: " << solver.getBestSolutionFitness() << endl;

	cout << simpleSolution << " " << baldSolution << " " << lamarkSolution << endl;

}



