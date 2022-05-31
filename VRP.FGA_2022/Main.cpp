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


const int COUNT_ITERATION = 10000;
const int POPULATION_SIZE = 30;





void test() {
	InputData input(fileName);
	
	int vertexCount = input.Size();

	double individualLR = 1 / double(vertexCount);
	double diversityRate = 1 / double(vertexCount * vertexCount);
	double globalLR = 0.05;

	SolverSecond Solver2(diversityRate, individualLR, globalLR);
	Solver2.Solve(input, POPULATION_SIZE, COUNT_ITERATION, false);

	BruteAlgorithm Brute;
	Brute.Solve(input);
	
	//InputData input(VERTEX_COUNT);
	//input.WriteInFile(fileName);
	//
	////InputData input(fileName);

	//SolverFirst Solver1(diversityRate, individualLR, globalLR);
	//Solver1.Solve(input, POPULATION_SIZE, COUNT_ITERATION, true);

	//SolverSecond Solver2(diversityRate, individualLR, globalLR);
	//Solver2.Solve(input, POPULATION_SIZE, COUNT_ITERATION, false);

	//SolverGenetic Solver3;
	//Solver3.Solve(input, POPULATION_SIZE);
}


int main(int argc, char* argv[]) {
	srand(time(0));
	cout.setf(ios::fixed);
	cout.precision(8);
	//read();

	double startT = clock();

	bool test_mode = true;

	if (test_mode) {
		test();
	}

	cout << "All Time Work  = " << (clock() - startT) / CLOCKS_PER_SEC << '\n';
}




