
#ifndef QAP_H
#define QAP_H

#include <omp.h>
#include <stdio.h>
#include <iostream>

#include <vector>

// To read files
#include <fstream>

// LOGS
#include "LOG.h"

using namespace std;


class QAP
{
	private:
		vector< vector<int> > distances;
		vector< vector<int> > weights;

		int dimension;

	public:

		void readFile(string filename)
		{
			fstream file(filename.c_str(), std::ios_base::in);

			if(!file)
			{
				throw std::runtime_error("Error: Invalid filename");
			}

			// read problem dimension
			file >> dimension;

			// read first matrix (distances)
			for(int i=0;i<dimension;i++)
			{
				distances.push_back(vector<int>());
				for(int j=0;j<dimension;j++)
				{
					int k; file >> k;
					distances[i].push_back(k);
				}
			}

			// read second matrix (weights)
			for(int i=0;i<dimension;i++)
			{
				weights.push_back(vector<int>());
				for(int j=0;j<dimension;j++)
				{
					int k; file >> k;
					weights[i].push_back(k);
				}
			}

			char buffer[140]; sprintf(buffer, "W: %dx%d , D: %dx%d", distances.size(), distances[0].size(), weights.size(), weights[0].size());
			string l = buffer;
			LOG(l);
		}

		void simpleSolutionInit(vector<int> &solution)
		{
			solution = vector<int>();
			for(int i=0;i<dimension;i++)
			{
				solution.push_back(i);
			}
		}

		int fitness(const vector<int> &solution)
		{
			int f = 0;

			for(int i=0;i<dimension;i++)
			{
				for(int j=0;j<dimension;j++)
				{
					f += weights[i][j] * distances[ solution[i] ][ solution[j] ];
				}
			}

			return f;
		}
};

#endif
