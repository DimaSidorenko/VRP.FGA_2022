#pragma once
#include <vector>
#include "../Utility/Utils.h"


class Gene {
public:
	vector<double> probabilities; // probabilities for gene to become corresponding allel 

	Gene() = default;
	Gene(int size);
	int GenerateValue();
	size_t Size();
};

