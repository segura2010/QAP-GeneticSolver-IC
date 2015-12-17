
#ifndef GeneticSolver_H
#define GeneticSolver_H

#include <omp.h>
#include <stdio.h>
#include <iostream>

#include <vector>
#include <algorithm>

// QAP Problem
#include "QAP.h"

// LOGS
#include "LOG.h"

// Random
#include "random.h"

// Utils
#include "utils.h"

// Local search for memetic GA
#include "LocalSearch.h"

using namespace std;

struct ParentPairs
{
	vector<int> p1;
	vector<int> p2;
};


class GeneticSolver
{
	private:
		// VARS
		// Population of solutions and their fitness
		vector< vector<int> > population;
		vector<int> fitness;

		// To save best solution in the population
		vector<int> bestSolution;
		int bestSolutionFitness;

		int populationSize;
		double mutationProb; // probability of mutation

		// Problem
		QAP problem;

		// LocalSearch to improve solutions (MEMETIC GA)
		LocalSearch LS;


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

			bestSolution = *(population.end()-1);
			bestSolutionFitness = problem.fitness( *(population.end()-1) );
		}

		int random(int lower, int upper)
		{	// generate a random int between (lower, upper)
			return Randint(lower, upper);
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

			if( bestSolutionFitness > fitness[best] )
			{
				bestSolution = population[best];
				bestSolutionFitness = fitness[best];
			}
		}

		void saveBestSolution(vector< vector<int> > p, vector<int> f)
		{	// seach the best solution and save it
			int best = 0;
			for(int i=1;i<f.size();i++)
			{
				if( f[best] > f[i] )
				{
					best = i;
				}
			}

			if( bestSolutionFitness > fitness[best] )
			{
				bestSolution = p[best];
				bestSolutionFitness = f[best];
			}
		}

		void crossover_OX(int parent1, int parent2, vector<int> &son1, vector<int> &son2)
		{	// OX Crossover

			int dimension = problem.getDimension();

			// generate start and end for the center of the sons
			int start = random(0, (dimension/2) - 2);
    		int end = random((dimension/2) + 2, dimension-1);

    		// reset vectors
    		son1 = vector<int>(dimension, -1);
    		son2 = vector<int>(dimension, -1);

    		for(int i=start;i<end;i++)
    		{	// copy the middle of parents on sons
    			son1[i] = population[parent1][i];
    			son2[i] = population[parent2][i];
    		}

    		// complete the sons with the order of the other parent
    		int j=0;
    		bool isCenter = false;
    		for(int i=0;i<dimension;i++)
    		{	// for son 1
    			isCenter = (i>start && i<end);
    			if( !isCenter )
    			{
					while( find(son1.begin(), son1.end(), population[parent2][j]) != son1.end() )
					{	// search if son1 have these element, if not i will put it on the son
						// else, i must search the next candidate
						j++;
						j = j % dimension;
					}

					son1[i] = population[parent2][j];
				}
    		}

    		j = 0;
    		for(int i=0;i<dimension;i++)
    		{	// for son 2
    			isCenter = (i>start && i<end);
    			if( !isCenter )
    			{
					while( find(son2.begin(), son2.end(), population[parent1][j]) != son2.end() )
					{	// search if son1 have these element, if not i will put it on the son
						// else, i must search the next candidate
						j++;
						j = j % dimension;
					}

					son2[i] = population[parent1][j];
				}
    		}

		}

		void crossover_OX(const vector<int> &parent1, const vector<int> &parent2, vector<int> &son1, vector<int> &son2)
		{	// OX Crossover

			int dimension = problem.getDimension();

			// generate start and end for the center of the sons
			int start = random(0, (dimension/2) - 2);
    		int end = random((dimension/2) + 2, dimension-1);

    		// reset vectors
    		son1 = vector<int>(dimension, -1);
    		son2 = vector<int>(dimension, -1);

    		for(int i=start;i<end;i++)
    		{	// copy the middle of parents on sons
    			son1[i] = parent1[i];
    			son2[i] = parent2[i];
    		}

    		// complete the sons with the order of the other parent
    		int j=0;
    		bool isCenter = false;
    		for(int i=0;i<dimension;i++)
    		{	// for son 1
    			isCenter = (i>start && i<end);
    			if( !isCenter )
    			{
					while( find(son1.begin(), son1.end(), parent2[j]) != son1.end() )
					{	// search if son1 have these element, if not i will put it on the son
						// else, i must search the next candidate
						j++;
						j = j % dimension;
					}

					son1[i] = parent2[j];
				}
    		}

    		j = 0;
    		for(int i=0;i<dimension;i++)
    		{	// for son 2
    			isCenter = (i>start && i<end);
    			if( !isCenter )
    			{
					while( find(son2.begin(), son2.end(), parent1[j]) != son2.end() )
					{	// search if son1 have these element, if not i will put it on the son
						// else, i must search the next candidate
						j++;
						j = j % dimension;
					}

					son2[i] = parent1[j];
				}
    		}

		}

		void mutation(vector<int> &s)
		{	// Mutation
			// it is simple, we will mutate the solution with a specific probability
			// the mutation is to exchange an gen (location) with other
			double p = Rand();

			if( p<mutationProb )
			{
				int gen1 = Randint(0, s.size()-1);
				int gen2 = Randint(0, s.size()-1);

				int tmp = s[gen1];
				s[gen1] = s[gen2];
				s[gen2] = tmp;
			}
		}

		void localSearchImprove(vector< vector<int> > &improvedPopulation, vector<int> &improvedFitness)
		{	// improve all the population with localsearch (but do not replace it!)

			improvedPopulation = vector< vector<int> >(population);
			improvedFitness = vector<int>(fitness);

			#pragma omp parallel for
			for(int i=0;i<improvedPopulation.size();i++)
			{
				improvedFitness[i] = LS.improveSolution( improvedPopulation[i] );
			}
		}

	public:

		GeneticSolver(int pSize, double pMut, string probName)
		{	// read the problem and prepare all to solve the problem
			populationSize = pSize;
			mutationProb = pMut;
			problem.readFile(probName);

			LS = LocalSearch(probName);
		}

		vector< vector<int> > getPopulation()
		{	// getter
			return population;
		}

		vector<int> getBestSolution()
		{	// getter
			return bestSolution;
		}
		int getBestSolutionFitness()
		{	// getter
			return bestSolutionFitness;
		}

		void simpleSolve(int generations)
		{
			// Generate first generation and calculate fitness
			randomInitialization();
			calculateAllFitness();
			saveBestSolution();

			vector< vector<int> > newPopulation;

			vector< ParentPairs > pairs;

			for(int g=0;g<generations;g++)
			{
				// Schema:
					// selection
					// cross
					// mutation

				// Simple selection
				// choose 2 random solutions and get sons
				// sons will replace the parents in the population

				pairs.clear();
				newPopulation.clear();
				newPopulation = vector< vector<int> >(population.size());

				while(population.size() > 0)
				{
					// selection
					ParentPairs parents;
					int p1 = random(0, population.size()-1);
					int p2 = random(0, population.size()-1);

					if(p1 == p2)
					{
						p2 = (p1 + 1) % population.size();
					}

					parents.p1 = population[ p1 ];
					parents.p2 = population[ p2 ];

					pairs.push_back(parents);

					// delete parents from population
					population.erase( population.begin()+p1, population.begin()+p1+1 );
					population.erase( population.begin()+p2, population.begin()+p2+1 );
				}

				#pragma omp parallel for
				for(int i=0;i<pairs.size();i++)
				{
					vector<int> son1, son2;
					// Crossover (to get sons)
					crossover_OX(pairs[i].p1, pairs[i].p2, son1, son2);

					// mutation
					mutation(son1);
					mutation(son2);

					// add to new population
					newPopulation[i*2] = son1;
					newPopulation[(i*2)+1] = son2;
				}

				/*
				while(population.size() > 0)
				{
					// selection
					int parent1 = random(0, population.size()-1);
					int parent2 = random(0, population.size()-1);

					vector<int> son1, son2;

					// Crossover (to get sons)
					crossover_OX(parent1, parent2, son1, son2);

					// mutation
					mutation(son1);
					mutation(son2);

					// add to new population
					newPopulation.push_back(son1);
					newPopulation.push_back(son2);

					// delete parents from population
					population.erase( population.begin()+parent1, population.begin()+parent1+1 );
					population.erase( population.begin()+parent2, population.begin()+parent2+1 );
				}
				*/

				// update population
				population = newPopulation;

				// update fitness and best solution
				calculateAllFitness();
				saveBestSolution();
			}

		}

		void baldwinianSolve(int generations)
		{
			// Generate first generation and calculate fitness
			randomInitialization();
			calculateAllFitness();
			saveBestSolution();

			vector< vector<int> > newPopulation, improvedPopulation;
			vector<int> improvedFitness;
			vector< ParentPairs > pairs;

			for(int g=0;g<generations;g++)
			{
				// Schema:
					// selection
					// cross
					// mutation

				// Simple selection
				// choose 2 random solutions and get sons
				// sons will replace the parents in the population

				pairs.clear();
				newPopulation.clear();
				newPopulation = vector< vector<int> >(population.size());

				// baldwinian - pass local search but doesnt use it to generate sons
				localSearchImprove(improvedPopulation, improvedFitness);
				saveBestSolution(improvedPopulation, improvedFitness);

				while(population.size() > 0)
				{
					// selection
					ParentPairs parents;
					int p1 = random(0, population.size()-1);
					int p2 = random(0, population.size()-1);

					if(p1 == p2)
					{
						p2 = (p1 + 1) % population.size();
					}

					parents.p1 = population[ p1 ];
					parents.p2 = population[ p2 ];

					pairs.push_back(parents);

					// delete parents from population
					population.erase( population.begin()+p1, population.begin()+p1+1 );
					population.erase( population.begin()+p2, population.begin()+p2+1 );
				}

				#pragma omp parallel for
				for(int i=0;i<pairs.size();i++)
				{
					vector<int> son1, son2;
					// Crossover (to get sons)
					crossover_OX(pairs[i].p1, pairs[i].p2, son1, son2);

					// mutation
					mutation(son1);
					mutation(son2);

					// add to new population
					newPopulation[i*2] = son1;
					newPopulation[(i*2)+1] = son2;
				}

				/*
				while(population.size() > 0)
				{
					// baldwinian - pass local search but doesnt use it to generate sons
					localSearchImprove(improvedPopulation, improvedFitness);
					saveBestSolution(improvedPopulation, improvedFitness);

					// selection
					int parent1 = random(0, population.size()-1);
					int parent2 = random(0, population.size()-1);

					vector<int> son1, son2;

					// Crossover (to get sons)
					crossover_OX(parent1, parent2, son1, son2);

					// mutation
					mutation(son1);
					mutation(son2);

					// add to new population
					newPopulation.push_back(son1);
					newPopulation.push_back(son2);

					// delete parents from population
					population.erase( population.begin()+parent1, population.begin()+parent1+1 );
					population.erase( population.begin()+parent2, population.begin()+parent2+1 );
				}
				*/

				// update population
				population = newPopulation;

				// update fitness and best solution
				calculateAllFitness();
				saveBestSolution();
			}

		}

		void lamarckianSolve(int generations)
		{
			// Generate first generation and calculate fitness
			randomInitialization();
			calculateAllFitness();
			saveBestSolution();

			vector< vector<int> > newPopulation, improvedPopulation;
			vector<int> improvedFitness;
			vector< ParentPairs > pairs;

			for(int g=0;g<generations;g++)
			{
				// Schema:
					// selection
					// cross
					// mutation

				// Simple selection
				// choose 2 random solutions and get sons
				// sons will replace the parents in the population

				pairs.clear();
				newPopulation.clear();
				newPopulation = vector< vector<int> >(population.size());

				// lamarckian - pass local search and use it to generate sons
				localSearchImprove(improvedPopulation, improvedFitness);
				saveBestSolution(improvedPopulation, improvedFitness);
				population = vector< vector<int> >(improvedPopulation);
				fitness = vector<int>(improvedFitness);

				
				while(population.size() > 0)
				{
					// selection
					ParentPairs parents;
					int p1 = random(0, population.size()-1);
					int p2 = random(0, population.size()-1);

					if(p1 == p2)
					{
						p2 = (p1 + 1) % population.size();
					}

					parents.p1 = population[ p1 ];
					parents.p2 = population[ p2 ];

					pairs.push_back(parents);

					// delete parents from population
					population.erase( population.begin()+p1, population.begin()+p1+1 );
					population.erase( population.begin()+p2, population.begin()+p2+1 );
				}

				#pragma omp parallel for
				for(int i=0;i<pairs.size();i++)
				{
					vector<int> son1, son2;
					// Crossover (to get sons)
					crossover_OX(pairs[i].p1, pairs[i].p2, son1, son2);

					// mutation
					mutation(son1);
					mutation(son2);

					// add to new population
					newPopulation[i*2] = son1;
					newPopulation[(i*2)+1] = son2;
				}
				

				/*
				while(population.size() > 0)
				{
					// selection
					int parent1 = random(0, population.size()-1);
					int parent2 = random(0, population.size()-1);

					vector<int> son1, son2;

					// Crossover (to get sons)
					crossover_OX(parent1, parent2, son1, son2);

					// mutation
					mutation(son1);
					mutation(son2);

					// add to new population
					newPopulation.push_back(son1);
					newPopulation.push_back(son2);

					// delete parents from population
					population.erase( population.begin()+parent1, population.begin()+parent1+1 );
					population.erase( population.begin()+parent2, population.begin()+parent2+1 );
				}
				*/

				// update population
				population = newPopulation;

				// update fitness and best solution
				calculateAllFitness();
				saveBestSolution();
			}

		}
		
};

#endif