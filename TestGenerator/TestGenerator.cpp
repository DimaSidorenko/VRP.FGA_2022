#include "TestGenerator.h"

vector<Point> TestGenerator::generateVertex(int N, int maxDist)
{
	vector<Point> res(N);

	for (auto& [x, y] : res) {
		x = Math::GenInt(0, maxDist);
		y = Math::GenInt(0, maxDist);
	}

	return res;
}
