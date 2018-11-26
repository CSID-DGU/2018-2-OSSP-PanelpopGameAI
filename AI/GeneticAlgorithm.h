/*
 * GeneticAlgorithm.h
 *
 *  Modified on: Nov 13, 2018
 *      Author: limjuhee
 */

#ifndef AI_GENETICALGORITHM_H_
#define AI_GENETICALGORITHM_H_
#include "Weight.h"
#include <vector>

using namespace std;

class GeneticAlgorithm {

private:

	// list of weight
	vector <Weight> list;
	// iterator of the list
	// vector <Weight> it;
	// indicator of Generation
	int Generation;
	// size of superior children
	int poolsize;

public:

	// Constructor : Generating parent
	GeneticAlgorithm();
	// crossover children considering mutation
	void crossOver();
	// Destructors
	~GeneticAlgorithm();
	// generate random number between upperLimit and lowLimit
	double random(int upperLimit, int lowerLimit);
	// write weights to file
	void writeWeightToFile();
	// running GA
	void runGA();
	// using roulette wheel selection
	int selection(int totalFitness, Weight* ptr);
	// mutation
	void mutation();
	// convert double value weights to binary 
	vector<int> double2bin(double real);
	// convert binary bits to double value weights
	double bin2double(vector<int>* ptr);
}
#endif /* AI_GENETICALGORITHM_H _ */
