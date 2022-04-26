#include "Chromosome.h"

Chromosome::Chromosome() :
	genes() {};


Chromosome::Chromosome(int32_t size)
{
	genes.resize(size);
	for (size_t i = 0; i < size; i++) {
		genes[i] = Gene(size);
	}
}


size_t Chromosome::Size()
{
	return genes.size();
}