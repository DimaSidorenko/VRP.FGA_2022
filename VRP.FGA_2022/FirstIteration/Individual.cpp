#include "Individual.h"


Individual::Individual() :
	chromosome(), sequences(), fitness(NONE_FITNESS) {};

Individual::Individual(Chromosome& chromosome, InputData& input, Chromosome& blueprint, double globalLR, bool enable_blueprint) : chromosome(chromosome)
{
	sequences = BornAnIndividual(blueprint, globalLR, enable_blueprint);
	fitness = CalculateFitness(input);
}

bool Individual::operator<(const Individual& ind) const
{
	return fitness > ind.fitness;
}


double Individual::CalculateFitness(InputData& input) {
	if (sequences.size() + 1 != input.Size()) {
		return -1;
	}
	
	sequences.insert(sequences.begin(), { 0 });

	long double answer = 0;
	for (int i = 1; i < sequences.size(); i++) {
		answer += input.Distance(sequences[i - 1], sequences[i]);
	}

	answer += input.Distance(sequences.back(), 0);

	sequences.erase(sequences.begin());

	return answer;

	//sequences.insert(sequences.begin(), { 0 });
	//int n = (int)(sequences.size());

	//vector<double> prefLen(n, 0);

	//for (int i = 1; i < n; ++i) {
	//	prefLen[i] = prefLen[i - 1] + input.Distance(sequences[i - 1], sequences[i]);
	//}
	//
	//vector<double> dp(n, INF);

	//dp[0] = 0;
	//for (int v = 0; v + 1 < n; ++v) {
	//	if (dp[v] == INF) {
	//		continue;
	//	}
	//	double len = 0;
	//	for (int u = v + 1; u < n; ++u) {
	//		// relaxing using edge (v, u)
	//		len = prefLen[u] - prefLen[v + 1] + input.Distance(0, sequences[v + 1]) + input.Distance(sequences[u], 0);
	//		dp[u] = min(dp[u], dp[v] + len);
	//	}
	//}

	//auto answer = dp[n - 1];
	//sequences.erase(sequences.begin());
	//return answer;
}


vector<int32_t> Individual::BornAnIndividual(Chromosome& blueprint, double globalLR, bool enable_blueprint)
{
	int n = chromosome.Size();
	vector<int> seq(n);
	vector<int> used(n + 1, false);

	double gLR = globalLR;

	for (int i = 0; i < n; i++) {
		if (enable_blueprint) {
			for (int j = 0; j < chromosome.genes[i].Size(); j++) {
				chromosome.genes[i].probabilities[j] = gLR * blueprint.genes[i].probabilities[j] + (1 - gLR) * chromosome.genes[i].probabilities[j];
			}
		}

		vector<double> prob;
		vector<int> key;

		for (int j = 0; j < chromosome.genes[i].Size(); j++) {
			if (!used[j + 1]) {
				key.push_back(j + 1);
				prob.push_back(chromosome.genes[i].probabilities[j]);
			}
		}

		int randVal = Math::GenRandom(prob);
		seq[i] = key[randVal];
		used[key[randVal]] = true;
	}

	return seq;
}
