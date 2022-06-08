#pragma once
#include <vector>
#include "Math.h"


class TestGenerator {
public:
	//generate N vertex (points on 2D plane)
	static vector<Point> generateVertex(int N = 100, int maxDist = 1e3);

	static vector<Point> generateSpecialTests(int _vertexCount, int _maxCoord, vector<int>& _groupSizes);
};
