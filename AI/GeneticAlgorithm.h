#pragma once
/*
 * GeneticAlgorithm.h
 *
 *  Modified on: Dec 5, 2018
 *      Author: blue
 */

#ifndef AI_GENETICALGORITHM_H_
#define AI_GENETICALGORITHM_H_
#include "Weight.h"
// depend on which mode choose to training
//#include "AIGameState.h"
//#include "EndlessGameState.h"
//#include "VSGameState.h"
#include <vector>
#include <string>
#include <map>

using namespace std;
int Generation = 0;

class GeneticAlgorithm {

private:

	// list of weight
	vector <Weight> list;
	
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
	int selection(int index, vector<Weight> list);
	// mutation
	void mutation(string * chromo);
	// convert double value weights to binary 
	string double2bin(double real);
	// convert binary bits to double value weights
	double bin2double(string ptr);
}
#endif /* AI_GENETICALGORITHM_H _ */
