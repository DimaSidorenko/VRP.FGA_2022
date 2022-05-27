#pragma once

#include "InputData.h"
#include "Utils.h"


class BruteAlgorithm
{
public:
	BruteAlgorithm() = default;

	bool Solve(InputData& input);
private:
	double CalcFitness(vector<int>& seq, InputData& input);
};
