#include <iostream>
#include <string>
#include "Utility/Utils.h"
#include "FirstIteration/SolverFirst.h"
#include "BruteAlgorithm/BruteAlgorithm.h"
#include "SecondIteration/SolverSecond.h"
#include "GeneticAlgorithm/SolverGenetic.h"

#pragma warning(disable : 4996)

using namespace std;

const char* fileName = "../TestGenerator/tests/test10_100.txt";
//InputFormat inputFormat = InputFormat::file;


const int COUNT_ITERATION = 1000;
const int POPULATION_SIZE = 30;


void run_algo(const char* fileName, double individualLR, double diversityRate, double globalLR) {
	InputData input(fileName);
	int vertexCount = input.Size();
	
	//cout << vertexCount << endl;	

	SolverSecond Solver2(diversityRate, individualLR, globalLR);
	Solver2.Solve(input, POPULATION_SIZE, COUNT_ITERATION, false);
}


int main(int argc, char* argv[]) {
	srand(time(0));
	cout.setf(ios::fixed);
	cout.precision(8);

	double startT = clock();

	if (argc < 2 || (string)argv[1] == "help") {
		cout << "Possible commands:" << endl;
		cout << "1) solve testFilePath individualLR diversityRate globalLR" << endl;
		return 0;
	}


	if ((string)argv[1] == "solve") {
		if (argc == 6) {
			const char* path = argv[2];
			double iLR = stod(argv[3]);
			double DR = stod(argv[4]);
			double gLR = stod(argv[5]);

			run_algo(path, iLR, DR, gLR);
			
			//cout << "All Time Work  = " << (clock() - startT) / CLOCKS_PER_SEC << '\n';
		}
		else
		{
			cout << "wrong parameters number\n";
		}

		return 0;
	}

	cout << "unknown command\n";
}




