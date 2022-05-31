#pragma once
#include <random>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

struct Point {
	double x, y;

	Point(double x = 0, double y = 0) : x(x), y(y) {};

	//distance between 2 points = dot product for them
	double getDist(const Point& p) {
		return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
	}
};


class Math {
public:
	int static GenInt(int l, int r);
	double static GenDouble(int l, int r);
	double static GenAllele();
	int static GenAllele(vector<double>& probabilities);
	int static GenRandom(vector<double>& probabilities);
};