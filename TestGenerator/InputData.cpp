#include "InputData.h"


//Calc Euclidean distance between points
vector<vector<double>> InputData::CalcDist(vector<Point>& vertex) {
	int n = vertex.size();
	vector<vector<double>> dist(n, vector<double>(n));
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			dist[i][j] = dist[j][i] = vertex[i].getDist(vertex[j]);
		}
	}

	return dist;
}


void InputData::ReadFromFile(const char* path) {
	ifstream fin(path);

	fin >> vertexCount;

	vertex.resize(vertexCount);
	dist.resize(vertexCount, vector<double>(vertexCount));

	vector<Point> graph(vertexCount);

	for (size_t i = 0; i < vertexCount; i++)
	{
		fin >> vertex[i].x >> vertex[i].y;
	}

	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			fin >> dist[i][j];
		}
	}

	fin.close();

	return;
}


InputData::InputData(int _vertexCount, int _maxCoord) :
	vertexCount(_vertexCount), maxCoord(_maxCoord)
{
	vertex = TestGenerator::generateVertex(_vertexCount, _maxCoord);
	dist = CalcDist(vertex);
}

InputData::InputData(const char* path) {
	ReadFromFile(path);
}

InputData::InputData(vector<Point>& graph) {
	vertexCount = graph.size();
	vertex = graph;
	dist = CalcDist(graph);
}

double InputData::Distance(int i, int j) {
	return dist[i][j];
}

void InputData::printGraph() {
	for (size_t i = 0; i < vertexCount; i++)
	{
		for (size_t j = 0; j < vertexCount; j++)
		{
			cout << dist[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

int InputData::Size() {
	return vertexCount;
}

void InputData::WriteInFile(const char* path) {
	ofstream fout(path);

	fout << vertexCount << '\n';

	for (auto& [x, y] : vertex) {
		fout << x << ' ' << y << '\n';
	}

	for (size_t i = 0; i < vertexCount; i++)
	{
		for (size_t j = 0; j < vertexCount; j++)
		{
			fout << dist[i][j] << ' ';
		}
		fout << '\n';
	}

	fout.close();
}