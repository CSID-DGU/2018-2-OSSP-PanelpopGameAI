/*
 * GeneticAlgorithm.cpp
 *
 *  Modified on: Dec 8, 2018
 *      Author: blue
 */
#include "GeneticAlgorithm.h"
#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

// -RATE should be beween 0 to 1
#define MUATATION_RATE 0.001
// return double real number between 0 to 1
#define CROSSOVER_RATE 0.7
#define MAX_GENERATION_SIZE 50
// real value(4) + decimal point(5)
#define CHROMOSOME_LENGTH 9

// Constructor
GeneticAlgorithm::GeneticAlgorithm() {

	// generate parents only 1 times at the beginning
	if (Generation == 0) {
		// generate 50 initial parents by random()
		for (int i = 0; i < 50; i++) {
		    weightList.push_back(Weight(i, random(10, 0), random(10, 0), random(10, 0), random(10, 0), random(10, 0), 0));
		} 
		// write initial generation to file
		writeWeightToFile();
	}
}

// generate random number between upperLimit and lowLimit
double GeneticAlgorithm::random(int upperLimit, int lowerLimit) {

	random_device sd;
	mt19937_64 sed(sd());
	uniform_real_distribution<double> range(lowerLimit, upperLimit);
	
	// until 5th digits 
	return floor(range(sed)*100000.f + 0.5) / 100000.f;

}

// generate Weight text file for each generation
void GeneticAlgorithm::writeWeightToFile() {

	Generation++;
	char fileName[30];
	sprintf(fileName, "Weight[%d].txt", Generation);
	ofstream fileout(fileName);

	// write weights to file
	if (fileout.is_open()) {

		for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
			fileout << i << "   " << weightList.at(i).get_verticalBlockWeight() << "   " 
				<< weightList.at(i).get_horizontalBlockWeight() << "   " 
				<< weightList.at(i).get_isMeetGarbageWeight() << "   "
				<< weightList.at(i).get_isExHighWeight() << "   "
				<< weightList.at(i).get_numOfBlock()
				<< "\n";
		}
	}

}

// most high-scored child, high-chance 
int GeneticAlgorithm::selection(int index, vector<Weight> weightList) {

	int score = 0;

	// put maxscore of the generation into 49 chromosome's maxScore
	int maxScore = weightList.at(49).get_maxScore();
	
	score = weightList.at(index).get_score();

	// piece < score 
	double piece = (double)(maxScore * random(0,1));

	// roulette wheel selection
	for (int i = index; i < MAX_GENERATION_SIZE; i++) {

		// return selected child's IDs
		if (score > piece) return i;
	}
	// if the child is not selected, then returns -1
	return -1;
}

//using BLX-α algorithm
double* GeneticAlgorithm::crossOver(double chromo1, double chromo2) {

	double big;
	double small;
	double arr[2];

	if (random(1, 0) < CROSSOVER_RATE) {

		if (chromo1 > chromo2) {
			big = chromo1;
			small = chromo2;
		}
		else {
			big = chromo2;
			small = chromo1;
		}

		double num = random(1, 0);
		double min = small - num * (big - small);
		double max = big + num * (big - small);

		// test if min < 0
		if (min < 0) {
			while (1) {
				num = random(1, 0);
				min = small - num * (big - small);
				if (min > 0) break;
			}
		}

		// test if max > 10
		if (max > 10) {
			while (1) {
				num = random(1, 0);
				max = small - num * (big - small);
				if (max < 10) break;
			}
		}

		chromo1 = random(max, min);
		chromo2 = random(max, min);
	}
	
	arr[0] = chromo1;
	arr[1] = chromo2;

	return arr;
}

// mutate children 
double GeneticAlgorithm::mutation(double chromo) {
	
	int num = 0;

	if (random(1,0) < MUATATION_RATE) {
		
		num = random(1, 0);
		chromo + num;

		if (chromo > 10) {
			while (1) {
				num = random(1, 0);
				chromo + num;
				if (chromo < 10) break;
			}
		}

	}

	return chromo;

}


// running GeneticAlgorithm
void GeneticAlgorithm::runGA() {

	// for debugging
	/*
	for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
		weightList.at(i).set_score(random(100, 0));
	}

	weightList.at(49).set_maxScore(88);
	*/
	// debuggging code ends



	// candidate child's ID
	int c1 = 0;
	int c2 = 0;
	double num = 0;
	// child's ID for loop
	int index = 0;

	int temp = 0;
	// count for loop 
	int new_id = 0;
	// temp1
	double k;
	double p;
	// temp2
	double x;
	double y;
	double *ptr;
	
	while (new_id < MAX_GENERATION_SIZE) {

		// performing selection 

		// select first candidate
		while (1) {
			temp = selection(index, weightList);
			index++;
			// if selected 
			if (temp >= 0) break;
			else if (index == 49) index = 0;
		}
		c1 = temp;

		// select second candidate
		while (1) {
			temp = selection(index, weightList);
			index++;
			// if selected
			if (temp >= 0) break;
			else if (index == 49) index = 0;
		}
		c2 = temp;

		index = 0;

		/** 1. horizontalBlockWeight **/

		// performing crossover 
		k = weightList.at(c1).get_horizontalBlockWeight();
		p = weightList.at(c2).get_horizontalBlockWeight();
		ptr = crossOver(k, p);
		x = ptr[0];
		y = ptr[1];

		weightList.at(c1).set_horizontalBlockWeight(x);
		weightList.at(c2).set_horizontalBlockWeight(y);

		// performing muatation
		k = mutation(weightList.at(c1).get_horizontalBlockWeight());
		p = mutation(weightList.at(c2).get_horizontalBlockWeight());

		weightList.at(c1).set_horizontalBlockWeight(k);
		weightList.at(c2).set_horizontalBlockWeight(p);

		/** 2. verticalBlockWeight **/

		// performing crossover 
		k = weightList.at(c1).get_verticalBlockWeight();
		p = weightList.at(c2).get_verticalBlockWeight();
		ptr = crossOver(k, p);
		x = ptr[0];
		y = ptr[1];

		weightList.at(c1).set_verticalBlockWeight(x);
		weightList.at(c2).set_verticalBlockWeight(y);

		// performing muatation
		k = mutation(weightList.at(c1).get_verticalBlockWeight());
		p = mutation(weightList.at(c2).get_verticalBlockWeight());

		weightList.at(c1).set_verticalBlockWeight(k);
		weightList.at(c2).set_verticalBlockWeight(p);
		
		/** 3. isExHighWeight **/

		// performing crossover 
		k = weightList.at(c1).get_isExHighWeight();
		p = weightList.at(c2).get_isExHighWeight();
		ptr = crossOver(k, p);
		x = ptr[0];
		y = ptr[1];

		weightList.at(c1).set_isExHighWeight(x);
		weightList.at(c2).set_isExHighWeight(y);

		// performing muatation
		k = mutation(weightList.at(c1).get_isExHighWeight());
		p = mutation(weightList.at(c2).get_isExHighWeight());

		weightList.at(c1).set_isExHighWeight(k);
		weightList.at(c2).set_isExHighWeight(p);

		/** 4. numOfBlock **/

		// performing crossover 
		k = weightList.at(c1).get_numOfBlock();
		p = weightList.at(c2).get_numOfBlock();
		ptr = crossOver(k, p);
		x = ptr[0];
		y = ptr[1];

		weightList.at(c1).set_numOfBlock(x);
		weightList.at(c2).set_numOfBlock(y);

		// performing muatation
		k = mutation(weightList.at(c1).get_numOfBlock());
		p = mutation(weightList.at(c2).get_numOfBlock());

		weightList.at(c1).set_numOfBlock(k);
		weightList.at(c2).set_numOfBlock(p);

		
		/** 5. **/

		// performing crossover 
		k = weightList.at(c1).get_isMeetGarbageWeight();
		p = weightList.at(c2).get_isMeetGarbageWeight();
		ptr = crossOver(k, p);
		x = ptr[0];
		y = ptr[1];

		weightList.at(c1).set_isMeetGarbageWeight(x);
		weightList.at(c2).set_isMeetGarbageWeight(y);

		// performing muatation
		k = mutation(weightList.at(c1).get_isMeetGarbageWeight());
		p = mutation(weightList.at(c2).get_isMeetGarbageWeight());

		weightList.at(c1).set_isMeetGarbageWeight(k);
		weightList.at(c2).set_isMeetGarbageWeight(p);
		
		new_id++;
		new_id++;

	}
	
	// write to file and store to new Weight list
	writeWeightToFile();

	// set maxScore to 0
	for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
		weightList.at(i).set_maxScore(0);
	}

}

// Destructor
GeneticAlgorithm::~GeneticAlgorithm() {  }
