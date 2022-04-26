#pragma once
#include <random>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

class Math {
public:
	int static GenInt(int l, int r);
	double static GenDouble(int l, int r);
	double static GenAllele();
	int static GenAllele(vector<double>& probabilities);
	int static GenRandom(vector<double>& probabilities);
};


