#include "SolverSecond.h"


// update certain gene probability convert to some allel using individual LR and diversity rate 
void SolverSecond::UpdateProbability(double& probability, double iLR, double DR) {
	probability += iLR;
	probability = min(probability, 1.0 - DR);
	probability = max(probability, DR);
}

// default genetic algorithm operator, check notation
Chromosome SolverSecond::Crossover(Chromosome& parent1, Chromosome& parent2) {
	auto par1 = &parent1;
	auto par2 = &parent2;
	if (Math::GenInt(0, 1)) {
		swap(par1, par2);
	}

	int n = par1->Size();
	int crossoverPoint = Math::GenInt(0, n);

	Chromosome result(n);
	for (int i = 0; i < crossoverPoint; i++) {
		result.genes[i] = par1->genes[i];
	}

	for (int i = crossoverPoint; i < n; i++) {
		result.genes[i] = par1->genes[i];
	}

	return result;
}



// update blueprint using formula in notation
void SolverSecond::updateBlueprint(vector<Chromosome>& population) {
	int sizePopulation = population.size();

	//iterate on every Gene
	for (int itGene = 0; itGene < population[0].Size(); itGene++) {
		int cntAllelesInGene = population[0].genes[itGene].Size();
		vector<double> sumProbabilities(cntAllelesInGene, 0.0);

		for (int itChr = 0; itChr < sizePopulation; itChr++) {
			for (int itAlelle = 0; itAlelle < cntAllelesInGene; itAlelle++) {
				sumProbabilities[itAlelle] += population[itChr].genes[itGene].probabilities[itAlelle];
			}
		}

		//take mean
		for (auto& sum : sumProbabilities) {
			sum /= sizePopulation;
		}

		blueprint.genes[itGene].probabilities = sumProbabilities;
	}
}



void SolverSecond::printPopulation(vector<Chromosome>& chrs, InputData& input) {
	for (auto& chr : chrs) {
		IndividualSecond individual = IndividualSecond(chr, input, blueprint, globalLR, enable_blueprint);

		cout << "Seq : ";
		for (auto& to : individual.sequences) {
			cout << to << ' ';
		}
		cout << '\n';

		cout << "Fitness : ";
		cout << individual.fitness << '\n';


		return;

		//spliting on path for several vehicles
		auto path = SplitPaths(individual.sequences, input);

		cout << "Path : " << '\n';
		cout << path.size() << '\n';
		for (auto& p : path) {
			for (auto vert : p) {
				cout << vert << ' ';
			}
			cout << '\n';
		}
	}
}


SolverSecond::SolverSecond(double diversityRate, double individualLR, double globalLR) :
	diversityRate(diversityRate), individualLR(individualLR), globalLR(globalLR), enable_blueprint(false) {};


bool SolverSecond::Solve(InputData& input, int populationSize, int cntIteration, bool _enable_blueprint) {
	enable_blueprint = _enable_blueprint;
	int N = populationSize;
	int cnt_vertices = input.Size();

	//inizialization
	vector<Chromosome> chrs(N, Chromosome(cnt_vertices));
	blueprint = Chromosome(cnt_vertices);

	int currentIteration = 0;

	//ofstream mean_second("mean_second.txt");
	//ofstream best_second("best_second.txt");

	IndividualSecond bestIndividual;

	while (currentIteration < cntIteration) {
		currentIteration++;

		//calc population
		vector<IndividualSecond> population;
		for (int i = 0; i < N; i++) {
			population.push_back(IndividualSecond(chrs[i], input, blueprint, globalLR, enable_blueprint));
		}

		// sorting population, population[i] has more fitness than population[i + 1], it means that i-th worse than (i + 1)-th
		sort(population.begin(), population.end());

		// vertex count
		int n = population[0].chromosome.Size();

		// increase probablity to make individual like the greatest 1/4 of population
		for (int itInd = population.size() - population.size() / 4; itInd < population.size(); itInd++) {
			for (int itGene = 1; itGene < n; itGene++) {
				int prevSeqValue = population[itInd].sequences[itGene - 1]; // previous vertex 
				int curSeqValue = population[itInd].sequences[itGene]; // current vertex

				//increase probability
				UpdateProbability(population[itInd].chromosome.genes[prevSeqValue].probabilities[curSeqValue], individualLR, diversityRate);

				//recalc other genes probability
				double decreaseValue = -individualLR / double(n - 1);
				for (int j = 0; j < n; j++) {
					if (j != curSeqValue) {
						UpdateProbability(population[itInd].chromosome.genes[prevSeqValue].probabilities[j], decreaseValue, diversityRate);
					}
				}
			}
		}

		// decrease probablity to make individual like the worst 1/4 of population
		for (int itInd = 0; itInd < population.size() / 4; itInd++) {
			for (int itGene = 1; itGene < n; itGene++) {
				int prevSeqValue = population[itInd].sequences[itGene - 1]; // previous vertex 
				int curSeqValue = population[itInd].sequences[itGene]; // current vertex

				//decrease porbability
				UpdateProbability(population[itInd].chromosome.genes[prevSeqValue].probabilities[curSeqValue], -individualLR, diversityRate);

				//recalc other genes probability
				double increaseValue = individualLR / double(n - 1);
				for (int j = 0; j < n; j++) {
					if (j != curSeqValue) {
						UpdateProbability(population[itInd].chromosome.genes[prevSeqValue].probabilities[j], increaseValue, diversityRate);
					}
				}
			}
		}

		//calc probability for every individuals to particapate in replication
		//using inverse coefficients because we need to minimize individuals fitnesses
		double meanFitness = 0.0;
		IndividualSecond tempIndividual;

		for (int i = 0; i < N; i++) {
			IndividualSecond ind = population[i];

			// calculate iteration mean fitness
			meanFitness += 1.0 / double(ind.fitness);

			if (tempIndividual.fitness == NONE_FITNESS || ind.fitness < tempIndividual.fitness) {
				tempIndividual = ind;
			}
		}

		//calculate answer
		if (bestIndividual.fitness == NONE_FITNESS || tempIndividual.fitness < bestIndividual.fitness) {
			bestIndividual = tempIndividual;
		}

		if (currentIteration % GAP_BETWEEN_OUTPUT == 0) {
			cout << currentIteration << ' ' << meanFitness << ' ' << tempIndividual.fitness << '\n';
		}

		//mean_second << currentIteration << ' ' << meanFitness << '\n';
		//best_second << currentIteration << ' ' << bestIndividual.fitness << '\n';


		//probabilities to become a parent
		//depends on individual's fitness
		vector<double> probabilities(N);
		for (int i = 0; i < N; i++) {
			probabilities[i] = (1.0 / double(population[i].fitness)) / meanFitness;
		}

		chrs.clear();
		//make chromosome for new population
		while (chrs.size() < N) {
			int it_par1 = Math::GenRandom(probabilities);
			//probabilities[it_par1] = max(0.01, probabilities[it_par1] - 1.0);

			int it_par2 = Math::GenRandom(probabilities);
			//probabilities[it_par2] = max(0.01, probabilities[it_par2] - 1.0);

			chrs.push_back(Crossover(population[it_par1].chromosome, population[it_par2].chromosome));
		}

		if (enable_blueprint) {
			updateBlueprint(chrs);
		}
	}

	//Printing results of algorithm
	cout << "****************************************************************" << '\n';
	cout << "Fluid Genetic SECOND RESULTS:\n";
	cout << "Best individual fitness = " << bestIndividual.fitness << '\n';

	for (auto to : bestIndividual.sequences) {
		cout << to << ' ';
	}
	cout << '\n';

	cout << "Number of iteration = " << currentIteration << "\n\n";
	cout << "****************************************************************" << '\n';

	//mean_second.close();
	//best_second.close();

	return true;
}
