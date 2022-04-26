#pragma once
#include <vector>
#include "Gene.h"

class Chromosome
{
public:
	std::vector<Gene> genes; // probabilities for sequences

	Chromosome();
	Chromosome(int32_t size);
	size_t Size();
};


