#pragma once

#include "Chromosome.h"
#include "Gene.h"
#include <vector>
#include "../InputData.h"


class Individual
{
public:
	Chromosome chromosome; // on the basis of which chromosome the individual is generated
	std::vector<int32_t> sequences; // sequences of vertex
	int64_t fitness;

	Individual(); // null individual
	Individual(Chromosome& chromosome, InputData& input, Chromosome& blueprint, double globalLR, bool enable_blueprint);

	bool operator < (const Individual& str) const;

private:
	int64_t CalculateFitness(InputData& input);

	//generate sequences based on a chromosome
	vector<int32_t> BornAnIndividual(Chromosome blueprint, double globalLR, bool enable_blueprint);
};
