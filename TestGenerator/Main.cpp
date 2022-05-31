#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <iomanip>
#include <string>
#include <chrono>
#include "InputData.h"

using namespace std;


int main(int argc, char** argv) {
	if (argc < 2 || (string)argv[1] == "help") {
		cout << "Possible commands:" << endl;
		cout << "1) gen targetsCnt citySizeKm [fileName]" << endl;
		return 0;
	}

	if ((string)argv[1] == "gen") {
		if (argc == 4) {
			int targetsCnt = atoi(argv[2]);	
			int citySize = atoi(argv[3]);

			string fileName = "tests/" + string("test") + to_string(targetsCnt) + "_" + to_string(citySize) + ".txt";

			InputData input(targetsCnt, citySize);
			input.WriteInFile(fileName.c_str());

			cout << "Test successfully generated. Saved in " << fileName << endl;
			return 0;
		}
		if (argc == 5) {
			int targetsCnt = atoi(argv[2]);	
			int citySize = atoi(argv[3]);

			string fileName = "tests/" + string(argv[4]) + ".txt";

			InputData input(targetsCnt, citySize);
			input.WriteInFile(fileName.c_str());

			cout << "Test successfully generated. Saved in " << fileName << endl;
			return 0;
		}
	}
	
	cout << "unknown function" << endl;
}



