#pragma once
#include<vector>
#include <iostream>
#include <fstream>

using namespace std;

const long long LINF = 2000000000000000000;
const int INF = 1e9 + 10;

class TestGenerator {
public:
	static vector<vector<int>> getData(int N = 100, int maxDist = 1e3) {
		vector<vector<int>> res(N, vector<int>(N, -1));

		for (int i = 0; i < N; i++) {
			res[i][i] = 0;
			for (int j = i + 1; j < N; j++) {
				res[i][j] = res[j][i] = rand() % maxDist + 100;
			}
		}

		return res;
	}
};


class InputDataOld {
private:
	int N;
	vector<vector<int>> Graph;
	vector<vector<long long>> Dist;

	//Calc minimal distances using Floyd - Warshall
	static vector<vector<long long>> CalcDist(vector<vector<int>> graph) {
		int n = graph.size();
		vector<vector<long long>> d(n, vector<long long>(n, LINF));
	
		for (int i = 0; i < n; i++) {
			d[i][i] = 0;
			for (int j = 0; j < n; j++) {
				if (graph[i][j] != LINF) {
					d[i][j] = graph[i][j];
				}
			}
		}

		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					if (d[i][k] < LINF && d[k][j] < LINF && d[i][k] + d[k][j] < d[i][j]) {
						d[i][j] = d[i][k] + d[k][j];
					}

		return d;
	}

	static vector<vector<int>> ReadFromFile(const char* path) {
		ifstream fin(path);

		int cnt_vehicles;
		fin >> cnt_vehicles;

		vector<vector<int>> graph(cnt_vehicles, vector<int>(cnt_vehicles));

		for (size_t i = 0; i < cnt_vehicles; i++)
		{
			for (size_t j = 0; j < cnt_vehicles; j++)
			{
				fin >> graph[i][j];
				if (graph[i][j] == -1) {
					graph[i][j] = LINF;
				}
			}
		}

		fin.close();
		
		return graph;
	}

public:

	InputData(int _N = 100, int maxDist = 1e3) {
		N = _N;
		Graph = TestGenerator::getData(N, maxDist);
		Dist = CalcDist(Graph);
	}

	InputData(const char* path) {
		vector<vector<int>> graph = ReadFromFile(path);
		N = graph.size();
		Graph = graph;
		Dist = CalcDist(graph);
	}

	InputData(vector<vector<int>> graph) {
		N = graph.size();
		Graph = graph;
		Dist = CalcDist(graph);
	}

	int Distance(int i, int j) {
		return Dist[i][j];
	}

	void printGraph() {
		cout << "Input graph:\n";

		int cnt_vehicles = Graph.size();
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



