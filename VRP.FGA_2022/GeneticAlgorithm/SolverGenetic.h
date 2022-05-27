#pragma once
#include <map>
#include <algorithm>
#include "../Utility/Utils.h"
#include "Optimizations.h"

class SolverGenetic {
public:
	static vector<vector<int>> Solve(InputData &input, int populationSize);
};

