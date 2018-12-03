#pragma once
/*
 * GeneticAlgorithm.h
 *
 *  Modified on: Dec 4, 2018
 *      Author: blue
 */

#ifndef AI_GENETICALGORITHM_H_
#define AI_GENETICALGORITHM_H_
#include "Weight.h"
#include <vector>
#include <string>
#include <map>

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
	// int poolsize;
	// pair of children which are selected
	map<int, int> pair;
	
public:

	// Constructor : Generating parent
	GeneticAlgorithm();
	// crossover children
	void crossOver(string * chromo1, string * chromo2);
	// Destructors
	~GeneticAlgorithm();
	// generate random number between upperLimit and lowLimit
	double random(int upperLimit, int lowerLimit);
	// write weights to file
	void writeWeightToFile();
	// running GA
	void runGA();
	// using roulette wheel selection
	int selection(int totalFitness, vector<Weight> list);
	// mutation
	void mutation(string * chromo);
	// convert double value weights to binary 
	string double2bin(double real);
	// convert binary bits to double value weights
	double bin2double(string ptr);
}
#endif /* AI_GENETICALGORITHM_H _ */
