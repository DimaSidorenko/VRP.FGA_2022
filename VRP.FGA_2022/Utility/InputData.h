#pragma once
#include<vector>
#include <iostream>
#include <fstream>
#include "Math.h"

const long long LINF = 2000000000000000000;
const int INF = 1e9 + 10;


class TestGenerator {
public:
	//generate N vertex (points on 2D plane)
	static vector<Point> getData(int N = 100, int maxDist = 1e3) {	
		vector<Point> res(N);

		for (auto& [x, y] : res) {
			x = Math::GenDouble(-maxDist, maxDist);
			y = Math::GenDouble(-maxDist, maxDist);
			
		}

		return res;
	}
};


class InputData {
private:
	int N;
	vector<Point> Vertex;
	vector<vector<double>> Dist;

	//Calc Euclidean distance between points
	static vector<vector<double>> CalcDist(vector<Point> vertex) {
		int n = vertex.size();
		vector<vector<double>> dist(n, vector<double>(n));
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				dist[i][j] = dist[j][i] = vertex[i].getDist(vertex[j]);
			}
		}

		return dist;
	}


	void ReadFromFile(const char* path) {
		ifstream fin(path);

		int cnt_vehicles;
		fin >> cnt_vehicles;
		N = cnt_vehicles;

		Vertex.resize(cnt_vehicles);
		Dist.resize(cnt_vehicles, vector<double>(cnt_vehicles));

		vector<Point> graph(cnt_vehicles);

		for (size_t i = 0; i < cnt_vehicles; i++)
		{
			fin >> Vertex[i].x >> Vertex[i].y;
		}

		for (int i = 0; i < cnt_vehicles; i++) {
			for (int j = 0; j < cnt_vehicles; j++) {
				fin >> Dist[i][j];
			}
		}

		fin.close();

		return;
	}

public:

	InputData(int _N = 100, int maxDist = 1e3) {
		N = _N;
		Vertex = TestGenerator::getData(N, maxDist);
		Dist = CalcDist(Vertex);
	}

	InputData(const char* path) {
		ReadFromFile(path);
	}

	InputData(vector<Point> graph) {
		N = graph.size();
		Vertex = graph;
		Dist = CalcDist(graph);
	}

	double Distance(int i, int j) {
		return Dist[i][j];
	}

	void printGraph() {
		cout << "Input graph:\n";

		int cnt_vehicles = Vertex.size();
		for (size_t i = 0; i < cnt_vehicles; i++)
		{
			for (size_t j = 0; j < cnt_vehicles; j++)
			{
				cout << Dist[i][j] << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
	}

	int Size() {
		return N;
	}

	void WriteInFile(const char* path) {
		ofstream fout(path);

		fout << N << '\n';

		for (auto& [x, y] : Vertex) {
			fout << x << ' ' << y << '\n';
		}

		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				fout << Dist[i][j] << ' ';
			}
			fout << '\n';
		}

		fout.close();
	}
};



