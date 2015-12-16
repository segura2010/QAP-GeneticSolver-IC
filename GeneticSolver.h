
#ifndef GeneticSolver_H
#define GeneticSolver_H

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

using namespace std;


class GeneticSolver
{
	private:
		// VARS
		// Population of solutions and their fitness
		vector< vector<int> > population;
		vector<int> fitness;

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
					int r = random(0, dimension-1);
					vector<int>::iterator it = find(population[i].begin(), population[i].end(), r);
					
					while( it != population[i].end() )
					{	// if the generated num is already selected, i will search the next number
						// not selected yet
						r = (r + 1) % dimension;
						it = find(population[i].begin(), population[i].end(), r);
					}
					population[i].push_back(r);
				}
			}
		}

		int random(int lower, int upper)
		{	// generate a random int between (lower, upper)
			return (rand() % upper + lower);
		}

		void calculateAllFitness()
		{	// recalculate and save all fitness
			fitness.clear();
			for(int i=0;i<population.size();i++)
			{
				fitness.push_back( problem.fitness( population[i] ) );
			}
		}

		void saveBestSolution()
		{	// seach the best solution and save it
			int best = 0;
			for(int i=1;i<fitness.size();i++)
			{
				if( fitness[best] > fitness[i] )
				{
					best = i;
				}
			}

			bestSolution = population[best];
		}

		void selection()
		{}

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

		void solve(int generations)
		{
			// Generate first generation and calculate fitness
			randomInitialization();
			calculateAllFitness();

			saveBestSolution();

			for(int g=0;g<generations;g++)
			{
				// selection

				// cross

				// mutation
			}

		}
		
};

#endif