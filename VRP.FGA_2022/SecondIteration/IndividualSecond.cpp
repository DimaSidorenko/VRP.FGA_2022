#include "IndividualSecond.h"


IndividualSecond::IndividualSecond() :
	chromosome(), sequences(), fitness(NONE_FITNESS) {};

IndividualSecond::IndividualSecond(Chromosome& chromosome, InputData& input, Chromosome& blueprint, double globalLR, bool enable_blueprint) : chromosome(chromosome)
{
	sequences = BornAnIndividual(blueprint, globalLR, enable_blueprint);
	fitness = CalculateFitness(input);
}

bool IndividualSecond::operator<(const IndividualSecond& ind) const
{
	return fitness > ind.fitness;
}


double IndividualSecond::CalculateFitness(InputData& input) {
	if (sequences.size() != input.Size()) {
		assert(sequences.size() == input.Size());
		return -1;
	}

	int n = (int)(sequences.size());

	vector<double> prefLen(n, 0);

	for (int i = 1; i < n; ++i) {
		prefLen[i] = prefLen[i - 1] + input.Distance(sequences[i - 1], sequences[i]);
	}

	//int* dp = new int[n];
	//fill(dp, dp + n, INF);

	vector<double> dp(n, INF);


	dp[0] = 0;
	for (int v = 0; v + 1 < n; ++v) {
		if (dp[v] == INF) {
			continue;
		}
		double len = 0;
		for (int u = v + 1; u < n; ++u) {
			// relaxing using edge (v, u)
			len = prefLen[u] - prefLen[v + 1] + input.Distance(0, sequences[v + 1]) + input.Distance(sequences[u], 0);
			dp[u] = min(dp[u], dp[v] + len);
		}
	}

	auto answer = dp[n - 1];
	//delete[] dp;
	//sequences.erase(sequences.begin());
	return answer;
}


vector<int32_t> IndividualSecond::BornAnIndividual(Chromosome& blueprint, double globalLR, bool enable_blueprint)
{
	int n = chromosome.Size();
	vector<int> seq(n);
	vector<int> used(n, false);

	double gLR = globalLR;

	//start with depot	
	seq[0] = 0;
	used[0] = true;

	for (int i = 1; i < n; i++) {
		int32_t prev_vertex = seq[i - 1];


		if (enable_blueprint) {
			for (int j = 0; j < chromosome.genes[prev_vertex].Size(); j++) {
				chromosome.genes[prev_vertex].probabilities[j] = 
					gLR * blueprint.genes[prev_vertex].probabilities[j] + (1 - gLR) * chromosome.genes[prev_vertex].probabilities[j];
			}
		}


		vector<double> prob;
		vector<int> key;

		for (int j = 0; j < chromosome.genes[prev_vertex].Size(); j++) {
			if (!used[j]) {
				key.push_back(j);
				prob.push_back(chromosome.genes[prev_vertex].probabilities[j]);
			}
		}

		int randVal = Math::GenRandom(prob);
		seq[i] = key[randVal];
		used[key[randVal]] = true;
	}

	return seq;
}
