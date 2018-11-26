/*
 * GeneticAlgorithm.cpp
 *
 *  Modified on: Nov 17, 2018
 *      Author: limjuhee
 */
#include "GeneticAlgorithm.h"
#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MUATATION_RATE 0.000
// return double real number between 0 to 1
#define RANDOM rand()/(double)(RAND_MAX+1)
#define CROSSOVER_RATE 0.000
#define MAX_GENERATION_SIZE 0

// Constructor
GeneticAlgorithm::GeneticAlgorithm() {
	// generate parent by random()

	//random(0, 10);

}

// generate random number between upperLimit and lowLimit
// use random() one-time when generating parents
double GeneticAlgorithm::random(int upperLimit, int lowerLimit) {

	random_device sd;
	mt19937_64 sed(sd());
	uniform_real_distribution<double> range(lowerLimit, upperLimit);

	for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
		Weight wg(i + 1, range(sed), range(sed), range(sed), range(sed), range(sed));
		list.push_back(wg);
	}
}

// choose using Roulette wheel and crossOver considering mutation 
// how to crossover 
void GeneticAlgorithm::crossOver() {

}

void GeneticAlgorithm::writeWeightToFile() {

	ofstream fileout("Weights.txt");

	// write weights to file
	if (fileout.is_open()) {
		for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
			fileout << list[i].getAttribute() << endl;
		}
	}
}


void GeneticAlgorithm::runGA() {

}

// totalFitness : sum of every children in the Generation 
// ptr : pointer of Weight list
int GeneticAlgorithm::selection(int totalFitness, Weight* ptr) {

	// sum of fitnesses to current fitness 
	double sumFitness = 0;
	// generate random point which decides choice
	// 0 < RANDOM < 1
	// why error?
	double piece = (double)(totalFitness * RANDOM);
	// roulette wheel selection
	for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
		for (int j = 0; j < 5; j++) {
			sumFitness += ptr[i].get_verticalBlockWeight();
			sumFitness += ptr[i].get_horizontalBlockWeight();
			sumFitness += ptr[i].get_isMeetGarbageWeight();
			sumFitness += ptr[i].get_isExHighWeight();
			sumFitness += ptr[i].get_isLT2();
		}
		// return selected child's ID
		if (sumFitness < piece) return i;
	}
}

// mutate children 
void GeneticAlgorithm::mutation() {

	// consider mutation on every 5 Weights 
	for (int i = 0; i < 5; i++) {
		// how to mutate
		if (RANDOM < MUATATION_RATE) {
		}
	}
}

// convert real value weights to binary
// 5 digits from rightmost are decimal point part
// rest of digits are real value
vector<int> GeneticAlgorithm::double2bin(double real) {


	return binary;
}

// convert binary bits to double value weights
double GeneticAlgorithm::bin2double(vector<int>* ptr) {
	// size of vector
	int size = ptr->size();
	int num = 0;
	// weight 
	double w = 0;
	// calculating point decimal part
	// repeat 5 times
	for (int i = 5; i > 0; i--) {
		// 0 or 1
		num = ptr->at(size - 1);
		if (num) {
			for (int j = 0; j < i; j++) {
				num *= 2;
			}
			w = 1 % num;
		}
		size--;
	}

	// calculating real value part
	for (int i = size; size >= 0; i--) {
		if (ptr->at(size - 1)) {

		}
	}
	return w;
}
GeneticAlgorithm::~GeneticAlgorithm() {  }
