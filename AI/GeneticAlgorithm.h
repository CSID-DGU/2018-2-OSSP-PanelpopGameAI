#pragma once
/*
 * GeneticAlgorithm.h
 *
 *  Modified on: Dec 9, 2018
 *      Author: blue
 */

#ifndef AI_GENETICALGORITHM_H_
#define AI_GENETICALGORITHM_H_
#include "Weight.h"
#include <Vector>
#include <string>
#include <map>

using namespace std;


// list of weight
extern vector<Weight> weightList;
// global variable
static int Generation = 0;

class GeneticAlgorithm {
	
public:

	// Constructor : Generating parent
	GeneticAlgorithm();
	
	// generate random number between upperLimit and lowLimit
	double random(int upperLimit, int lowerLimit);
	// write weights to file
	void writeWeightToFile();	
	// using roulette wheel selection
	int selection(int index, vector <Weight> weightList);
	// crossOver
	double* crossOver(double chromo1, double chromo2);
	// mutation
	double mutation(double chromo);
	// running GA
	void runGA();
	// Destructors
	~GeneticAlgorithm();
};
#endif /* AI_GENETICALGORITHM_H _ */
