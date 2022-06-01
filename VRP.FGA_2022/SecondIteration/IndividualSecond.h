#pragma once

#include <vector>
#include "../FirstIteration/Chromosome.h"
#include "../FirstIteration/Gene.h"
#include "../Utility/Utils.h"

class IndividualSecond
{
public:
	Chromosome chromosome; // on the basis of which chromosome the individual is generated
	std::vector<int32_t> sequences; // sequences of vertex
	double fitness;

	IndividualSecond(); // null individual
	IndividualSecond(Chromosome& chromosome, InputData& input, Chromosome& blueprint, double globalLR, bool enable_blueprint);

	bool operator < (const IndividualSecond& str) const;

private:
	double CalculateFitness(InputData& input);

	//generate sequences based on a chromosome
	vector<int32_t> BornAnIndividual(Chromosome& blueprint, double globalLR, bool enable_blueprint);
};
