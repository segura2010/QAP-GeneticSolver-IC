
#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

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

using namespace std;


class LocalSearch
{
	private:
		// VARS
		QAP problem;

	public:

		LocalSearch()
		{
		}

		LocalSearch(string probName)
		{	// read the problem and prepare all to solve the problem
			problem.readFile(probName);
		}

		int improveSolution(vector<int> &s)
		{	// Apply local search to the solution to improve it

			bool improved = true;
			int savedFitness = problem.fitness(s);

			// while i improve the solution, keep exploring the neighborhood (and trying to improve)
			while( improved )
			{
				improved = false;
				for(int i=0;i<s.size() && !improved;i++)
				{	// for each location, i will try to exchange with otherlocation
					for(int j=0;j<s.size() && !improved;j++)
					{
						improved = false;
						if(s[i] != s[j])
						{	// do not exchange by the same value!!
							// exchange values and check new solution cost
							int tmp = s[i];
							s[i] = s[j];
							s[j] = tmp;
							int f = problem.fitness(s);

							if(f < savedFitness)
							{	// it's better, update&move
								improved = true;
								savedFitness = f;
							}
							else
							{	// recover the solution
								s[j] = s[i];
								s[i] = tmp;
							}
						}
					}
				}
			}

			return savedFitness;

		}
		
};

#endif