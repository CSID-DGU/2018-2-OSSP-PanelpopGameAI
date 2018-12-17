#pragma once
/*
 * GeneticAlgorithm.h
 *
 *  Modified on: Dec 18, 2018
 *      Author: blue
 */

#ifndef AI_GENETICALGORITHM_H_
#define AI_GENETICALGORITHM_H_
#include "Weight.h"
#include <vector>
#include <string>
#include <map>

using namespace std;


// list of weight
extern vector<Weight> weightList;
// global variable
static int Generation = 10;

class GeneticAlgorithm {

public:

	int c1 = 0;
	int c2 = 0;
	double totalScore = 0;
	// Constructor : Generating parent
	GeneticAlgorithm();

	// generate random number between upperLimit and lowLimit
	double random(int upperLimit, int lowerLimit);
	// write weights to file
	void writeWeightToFile();
	// using roulette wheel selection
	void selection();
	// crossOver
	void crossOver();
	// mutation
	double mutation(double w);
	// running GA
	void runGA();
	// Destructors
	~GeneticAlgorithm();
};
#endif /* AI_GENETICALGORITHM_H _ */
