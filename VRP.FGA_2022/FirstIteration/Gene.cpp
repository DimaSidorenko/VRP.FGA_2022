#include "Gene.h"

Gene::Gene(int size)
{
	probabilities.resize(size, 1 / double(size));
}

int Gene::GenerateValue()
{
	return Math::GenAllele(probabilities);
}

size_t Gene::Size()
{
	return probabilities.size();
}
