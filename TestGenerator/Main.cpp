#include <ctime>
#include <chrono>
#include <random>


using namespace std;

void genInput(int cnt_vehicles, int size_km, int cnt_targets) {
	unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
	mt19937 gen(seed);


}


