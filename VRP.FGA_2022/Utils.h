#pragma once
#include <random>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <numeric>
#include "InputData.h"

using namespace std;

//for individuals classes
const int32_t NONE_FITNESS = -1;
const int32_t GAP_BETWEEN_OUTPUT = 100;


enum class InputFormat
{
	file,
	console
};


vector<vector<int>> SplitPaths(vector<int>& path, InputData& input);