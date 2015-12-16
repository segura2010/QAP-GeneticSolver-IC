
#ifndef GeneticSolver_H
#define GeneticSolver_H

#include <omp.h>
#include <stdio.h>
#include <iostream>

// for random
#include <stdlib.h> // rand
#include <time.h> // time

#include <vector>

// QAP Problem
#include "QAP.h"

// LOGS
#include "LOG.h"

using namespace std;


class GeneticSolver
{
	private:
		// VARS
		// Population of solutions
		vector< vector<int> > population;

		// To save best solution in the population
		vector<int> bestSolution;

		int populationSize;

		QAP problem;


		// FUNCTIONS
		void randomInitialization()
		{	// initialize the population with random solutions
			int dimension = problem.getDimension();
			population.clear();

			for(int i=0;i<populationSize;i++)
			{
				population.push_back( vector<int>() ); // add a new vector of ints
				for(int j=0;j<dimension;j++)
				{
					int r = random(0, dimension);
					vector<int>::iterator it;// = find(population[i].begin(), population[i].end(), r);
					while( it != population[i].end() )
					{	// if the generated num is already selected, i will search the next number
						// not selected yet
						r = (r + 1) % dimension;
						population[i].push_back(r);

						char buffer[140]; sprintf(buffer, "new element on solution %d: %d", i, r);
						LOG(buffer);
					}
				}
			}
		}

		int random(int lower, int upper)
		{	// generate a random int between (lower, upper)
			return (rand() % upper + lower);
		}

	public:

		GeneticSolver(int pSize, string probName)
		{	// read the problem and prepare all to solve the problem
			populationSize = pSize;
			problem.readFile(probName);

			// initialize random seed
			srand(time(NULL));
		}

		vector< vector<int> > getPopulation()
		{	// getter
			return population;
		}

		vector<int> getBestSolution()
		{	// getter
			return bestSolution;
		}

		void solve()
		{}
		
};

#endif