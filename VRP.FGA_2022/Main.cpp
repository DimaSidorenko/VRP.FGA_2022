#include <iostream>
#include <string>
#include "Utility/Utils.h"
#include "FirstIteration/SolverFirst.h"
#include "BruteAlgorithm/BruteAlgorithm.h"
#include "SecondIteration/SolverSecond.h"
#include "GeneticAlgorithm/SolverGenetic.h"

#pragma warning(disable : 4996)

using namespace std;

//const char* fileName = "../TestGenerator/tests/test10_100.txt";
//InputFormat inputFormat = InputFormat::file;


const int COUNT_ITERATION = 2000;
const int POPULATION_SIZE = 50;


//needed to use freopen
#pragma warning(disable : 4996)


void run_elastic_before_tuning(const char* fileName, int countIteration) {
	//freopen("elastic_before_tuning.txt", "w", stdout);

	InputData input(fileName);
	int vertexCount = input.Size();

	double individualLR = 1 / long double(vertexCount);
	double diversityRate = long double(vertexCount) / long double(vertexCount);
	double globalLR = 0.1;

	SolverSecond Solver2(diversityRate, individualLR, globalLR);
	Solver2.Solve(input, POPULATION_SIZE, countIteration, false);
}


void run_static_before_tuning(const char* fileName, int countIteration) {
	//freopen("static_before_tuning.txt", "w", stdout);
	
	InputData input(fileName);
	int vertexCount = input.Size();


	double individualLR = 1 / long double(vertexCount);
	double diversityRate = 1 / long double(vertexCount) / long double(vertexCount);
	double globalLR = 0.1;


	SolverFirst Solver1(diversityRate, individualLR, globalLR);
	Solver1.Solve(input, POPULATION_SIZE, countIteration, false);
}


void run_elastic_after_tuning(const char* fileName, int countIteration) {
	freopen("elastic_after_tuning.txt", "w", stdout);

	InputData input(fileName);
	int vertexCount = input.Size();


	auto individualLR = (0.025 * vertexCount + 3.45) / long double(70);
	auto diversityRate = 0.003903 * exp(-0.036642 * vertexCount);
	auto globalLR = 0.1;

	SolverSecond Solver2(diversityRate, individualLR, globalLR);
	Solver2.Solve(input, POPULATION_SIZE, countIteration, false);
}


void run_static_after_tuning(const char* fileName, int countIteration) {
	freopen("static_after_tuning.txt", "w", stdout);
	InputData input(fileName);
	int vertexCount = input.Size();


	auto individualLR = (0.025 * vertexCount + 3.45) / long double(70);
	auto diversityRate = 0.003903 * exp(-0.036642 * vertexCount);
	auto globalLR = 0.1;

	SolverFirst Solver1(diversityRate, individualLR, globalLR);
	Solver1.Solve(input, POPULATION_SIZE, countIteration, false);
}



void run_reference_solution(const char* fileName, int countIteration) {
	InputData input(fileName);
	int vertexCount = input.Size();

	SolverGenetic::Solve(input, 50);
}


int main(int argc, char* argv[]) {
	srand(time(0));
	cout.setf(ios::fixed);
	cout.precision(8);

	
	{
		const char* fileName = "..\\TestGenerator\\tests\\10\\random_4.txt";

		run_elastic_before_tuning(fileName, COUNT_ITERATION);
		run_static_before_tuning(fileName, COUNT_ITERATION);
		run_reference_solution(fileName, COUNT_ITERATION);
	}
	
	//double startT = clock();

	//bool special_test_results_check = true;
	//
	//if (special_test_results_check) {
	//	const char* fileName = "..\\TestGenerator\\tests\\30\\special_1.txt";

	//	InputData input(fileName);
	//	int vertexCount = input.Size();

	//	double diversityRate = 0.0001;
	//	double individualLR = 0.047;
	//	double globalLR = 0.01;

	//	int countIteration = 500;

	//	SolverSecond Solver2(diversityRate, individualLR, globalLR);
	//	Solver2.Solve(input, POPULATION_SIZE, countIteration, false);

	//	return 0;
	//}

	//if (argc < 2 || (string)argv[1] == "help") {
	//	cout << "Possible commands:" << endl;
	//	cout << "1) solve testFilePath individualLR diversityRate globalLR" << endl;
	//	return 0;
	//}


	//if ((string)argv[1] == "solve") {
	//	if (argc == 7) {
	//		const char* path = argv[2];
	//		double iLR = stod(argv[3]);
	//		double DR = stod(argv[4]);
	//		double gLR = stod(argv[5]);
	//		int countIteration = stoi(argv[6]);

	//		run_algo(path, iLR, DR, gLR, countIteration);
	//		
	//		//cout << "All Time Work  = " << (clock() - startT) / CLOCKS_PER_SEC << '\n';
	//	}
	//	else
	//	{
	//		cout << "wrong parameters number\n";
	//	}

	//	return 0;
	//}

	//cout << "unknown command\n";
}




