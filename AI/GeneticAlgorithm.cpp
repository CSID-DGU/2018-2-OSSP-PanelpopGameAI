/*
 * GeneticAlgorithm.cpp
 *
 *  Modified on: Dec 18, 2018
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
#define MAX_GENERATION_SIZE 25
//vector<Weight> weightList;

GeneticAlgorithm::GeneticAlgorithm() {

	// parents
	if (Generation == 0) {
		for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
			Weight w(i, random(10, 0), random(10, 0), random(10, 0), random(10, 0), 0, 0);
			weightList.push_back(w);
		}
	}
	
	// for debugging
	/*for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
		weightList.at(i).set_score(random(10, 0));
	}
	weightList.at(MAX_GENERATION_SIZE - 1).set_maxScore(7);
	*/

}

double GeneticAlgorithm::random(int upperLimit, int lowerLimit) {
	random_device sd;
	mt19937_64 sed(sd());
	uniform_real_distribution<double> range(lowerLimit, upperLimit);

	// return real value until 5th digits 
	return floor(range(sed)*100000.f + 0.5) / 100000.f;
}

// generate Weight text file for each generation
void GeneticAlgorithm::writeWeightToFile() {

	char fileName[30];
	sprintf(fileName, "Weight[%d].txt", Generation);
	ofstream fileout(fileName);

	// write weights to file
	if (fileout.is_open()) {

		for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
			fileout << i << "   " << weightList.at(i).get_verticalBlockWeight() << "   "
				<< weightList.at(i).get_horizontalBlockWeight() << "   "
				<< weightList.at(i).get_isExHighWeight() << "   "
				<< weightList.at(i).get_numOfBlock() << "   "
				<< weightList.at(i).get_score() << "   "
				<< weightList.at(i).get_maxScore()
				<< "\n";
		}
	}
	Generation++;
}

//using roulette wheel selection methods
// choose 2 parents
void GeneticAlgorithm::selection() {

	double temp = 0;
	double piece = random(totalScore, 0);
	//cout << piece << endl;

	// choose first parent
	for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
		temp += weightList.at(i).get_score();
		if (temp > piece) {
			c1 = i;
			break;
		}
	}
	
	//cout << c1 << endl;

	while (1) {
		temp = 0;
		piece = random(totalScore, 0);
		// choose second parent
		for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
			temp += weightList.at(i).get_score();
			if (temp > piece) {
				// if the child is already selected choose another 
				if (c1 == i) break;
				else {
					c2 = i;
					//cout << c2 << endl;
					return;
				}
			}
		}
	}
}

double GeneticAlgorithm::mutation(double w) {

	if (random(1, 0) < MUATATION_RATE) {
		w += random(1, 0);
		return w;
	}
	return w;

}

void GeneticAlgorithm::crossOver() {

	double temp1 = 0;
	double temp2 = 0;
	double r = 0;

	// verticalBlockWeight
	r = random(1, 0);
	temp1 = weightList.at(c1).get_verticalBlockWeight();
	temp2 = weightList.at(c2).get_verticalBlockWeight();
	temp1 = temp1 * r + (1 - r)*temp2;
	r = random(1, 0);
	temp2 = temp1 * r + (1 - r)*temp2;
	weightList.at(c1).set_verticalBlockWeight(mutation(temp1));
	weightList.at(c2).set_verticalBlockWeight(mutation(temp2));

	// horizontalBlockWeight
	r = random(1, 0);
	temp1 = weightList.at(c1).get_horizontalBlockWeight();
	temp2 = weightList.at(c2).get_horizontalBlockWeight();
	temp1 = temp1 * r + (1 - r)*temp2;
	r = random(1, 0);
	temp2 = temp1 * r + (1 - r)*temp2;
	weightList.at(c1).set_horizontalBlockWeight(mutation(temp1));
	weightList.at(c2).set_horizontalBlockWeight(mutation(temp2));

	// isExHighWeight
	r = random(1, 0);
	temp1 = weightList.at(c1).get_isExHighWeight();
	temp2 = weightList.at(c2).get_isExHighWeight();
	temp1 = temp1 * r + (1 - r)*temp2;
	r = random(1, 0);
	weightList.at(c1).set_isExHighWeight(mutation(temp1));
	weightList.at(c2).set_isExHighWeight(mutation(temp2));

	// numOfBlock
	r = random(1, 0);
	temp1 = weightList.at(c1).get_numOfBlock();
	temp2 = weightList.at(c2).get_numOfBlock();
	temp1 = temp1 * r + (1 - r)*temp2;
	r = random(1, 0);
	weightList.at(c1).set_numOfBlock(mutation(temp1));
	weightList.at(c2).set_numOfBlock(mutation(temp2));
}

void GeneticAlgorithm::runGA() {

	writeWeightToFile();

	//calculate total score
	double total = 0;
	for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
		total += weightList.at(i).get_score();
	}

	totalScore = total;

	for (int i = 0; i < MAX_GENERATION_SIZE / 2; i++) {
		selection();
		crossOver();
	}

	// initializing score
	for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
		weightList.at(i).set_score(0);
	}
	weightList.at(MAX_GENERATION_SIZE - 1).set_maxScore(0);
}

GeneticAlgorithm::~GeneticAlgorithm() {}
