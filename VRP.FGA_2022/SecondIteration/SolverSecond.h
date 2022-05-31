#pragma once
#include "../Utility/Utils.h"
#include "../FirstIteration/Chromosome.h"
#include "../SecondIteration/IndividualSecond.h"
#include "../FirstIteration/Gene.h"



class SolverSecond
{
public:
	Chromosome blueprint;
	bool enable_blueprint;
	// the border for probability from bottom, the border from top is equal to (1 - diversityRate)
	double diversityRate;
	double individualLR;
	double globalLR;

	SolverSecond(double diversityRate, double individualLR, double globalLR);

	bool Solve(InputData& input, int populationSize, int cntIteration, bool enable_blueprint);
	//bool fitness_comparator(const Individual& ind1, const Individual& ind2);

private:
	void updateBlueprint(vector<Chromosome>& population);
	void UpdateProbability(double& probability, double iLR, double DR);

	void IncreaseGeneProbabilities(vector<double>& probabilities, int nextVertex);
	void DecreaseGeneProbabilities(vector<double>& probabilities, int nextVertex);

	Chromosome Crossover(Chromosome& parent1, Chromosome& parent2);
	void printPopulation(vector<Chromosome>& chrs, InputData& input);
};

