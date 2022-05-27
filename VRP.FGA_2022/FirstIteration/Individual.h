#pragma once

#include <vector>
#include "Chromosome.h"
#include "Gene.h"
#include "../Utility/InputData.h"


class Individual
{
public:
	Chromosome chromosome; // on the basis of which chromosome the individual is generated
	std::vector<int32_t> sequences; // sequences of vertex
	double fitness;

	Individual(); // null individual
	Individual(Chromosome& chromosome, InputData& input, Chromosome& blueprint, double globalLR, bool enable_blueprint);

	bool operator < (const Individual& str) const;

private:
	double CalculateFitness(InputData& input);

	//generate sequences based on a chromosome
	vector<int32_t> BornAnIndividual(Chromosome blueprint, double globalLR, bool enable_blueprint);
};
