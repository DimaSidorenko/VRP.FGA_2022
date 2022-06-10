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


const int citySize = 100000;

int main(int argc, char** argv) {
	bool fast_generation_mode = true;
	bool special_test_cases_mode = true;

	if (special_test_cases_mode) {
		vector<int> sz = {10, 30, 45, 60, 80, 100};

		int countSpecialTests = 6;

		for (auto current_size : sz) {
			for (int i = 1; i <= countSpecialTests; i++) {
				string file_path = "tests\\" + to_string(current_size) + "\\" + "special_" + to_string(i) + ".txt";


				int groupSize = (current_size + 9) / 10;

				vector<int> groupSizes(current_size / groupSize, groupSize);

				InputData input(current_size, citySize, groupSizes);
				input.WriteInFile(file_path.c_str());
			}
		}

	}

	if (fast_generation_mode) {
		vector<int> sz = { 10, 30, 45, 60, 80, 100 };
		
		int countRandomTests = 6;

		for (auto current_size : sz) {
			for (int i = 1; i <= countRandomTests; i++) {
				string file_path = "tests\\" + to_string(current_size) + "\\" + "random_" + to_string(i) + ".txt";
				
				InputData input(current_size, citySize);
				input.WriteInFile(file_path.c_str());
			}
		}

		return 0;
	}

	if (argc < 2 || (string)argv[1] == "help") {
		cout << "Possible commands:" << endl;
		cout << "1) gen targetsCnt [fileName]" << endl;
		return 0;
	}

	if ((string)argv[1] == "gen") {
		if (argc == 3) {
			int targetsCnt = atoi(argv[2]);	
			string fileName = "tests/" + string("test") + to_string(targetsCnt) + ".txt";

			InputData input(targetsCnt, citySize);
			input.WriteInFile(fileName.c_str());

			cout << "Test successfully generated. Saved in " << fileName << endl;
			return 0;
		}
		if (argc == 4) {
			int targetsCnt = atoi(argv[2]);	
			string fileName = "tests/" + string(argv[3]) + ".txt";

			InputData input(targetsCnt, citySize);
			input.WriteInFile(fileName.c_str());

			cout << "Test successfully generated. Saved in " << fileName << endl;
			return 0;
		}
	}
	
	cout << "unknown function" << endl;
}



