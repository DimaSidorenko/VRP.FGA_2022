#pragma once
#include<vector>
#include <iostream>
#include <fstream>
#include "Math.h"
#include "TestGenerator.h"

const long long LINF = 2000000000000000000;
const int INF = 1e9 + 10;


class InputData {
private:
	int vertexCount;
	vector<Point> vertex;
	vector<vector<double>> dist;
	long long maxCoord;

	//Calc Euclidean distance between points
	static vector<vector<double>> CalcDist(vector<Point>& vertex);

	void ReadFromFile(const char* path);

public:

	InputData(int _vertexCount, int _maxCoord);
	InputData(const char* path);
	InputData(vector<Point>& graph);

	//get Distance between two verteces
	double Distance(int i, int j);

	void printGraph();

	int Size();

	void WriteInFile(const char* path);
};



