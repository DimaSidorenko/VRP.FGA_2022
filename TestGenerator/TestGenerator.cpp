#include "TestGenerator.h"

vector<Point> TestGenerator::generateVertex(int N, int maxDist)
{
	vector<Point> res(N);

	for (auto& [x, y] : res) {
		x = Math::GenDouble(-maxDist, maxDist);
		y = Math::GenDouble(-maxDist, maxDist);

	}

	return res;
}
