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

vector<Point> TestGenerator::generateSpecialTests(int _vertexCount, int maxDist, vector<int>& _groupSizes)
{
	vector<Point> res;
	res.reserve(_vertexCount);

	for	(auto currentGroupSize : _groupSizes) {	
		auto middle_x = Math::GenInt(0, maxDist);
		auto middle_y = Math::GenInt(0, maxDist);

		res.emplace_back(middle_x, middle_y);
		
		int boundingBoxSize = maxDist / _vertexCount / int(log10(maxDist));
		
		auto bot_border = max(0, middle_y - (boundingBoxSize / 2));
		auto top_border = min(maxDist, middle_y + (boundingBoxSize / 2));
		
		auto left_border = max(0, middle_x - (boundingBoxSize / 2));
		auto right_border = min(maxDist, middle_x + (boundingBoxSize / 2));
	
		for (int i = 1; i < currentGroupSize; i++) {
			auto x = Math::GenInt(left_border, right_border);
			auto y = Math::GenInt(bot_border, top_border);

			res.emplace_back(x, y);
		}
	}

	return res;
}
