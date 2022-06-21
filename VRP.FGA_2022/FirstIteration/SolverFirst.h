#pragma once
#include "../Utility/Utils.h"
#include "Chromosome.h"
#include "Individual.h"
#include "Gene.h"
#include <iomanip>

class SolverFirst
{
public:
	Chromosome blueprint;
	bool enable_blueprint;
	double diversityRate;
	double individualLR;
	double globalLR;

	SolverFirst(double diversityRate, double individualLR, double globalLR);

	bool Solve(InputData& input, int populationSize, int cntIteration, bool enable_blueprint);
	//bool fitness_comparator(const Individual& ind1, const Individual& ind2);

private:
	void updateBlueprint(vector<Chromosome>& population);
	void UpdateProbability(double& probability, double iLR, double DR);
	Chromosome Crossover(Chromosome& parent1, Chromosome& parent2);
	void printPopulation(vector<Chromosome>& chrs, InputData& input);
	void IncreaseGeneProbabilities(vector<double>& probabilities, int nextVertex);
	void DecreaseGeneProbabilities(vector<double>& probabilities, int nextVertex);
};

