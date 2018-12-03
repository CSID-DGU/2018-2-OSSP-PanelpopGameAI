/*
 * GeneticAlgorithm.cpp
 *
 *  Modified on: Dec 4, 2018
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

#define MUATATION_RATE 0.000
// return double real number between 0 to 1
#define RANDOM rand()/(double)(RAND_MAX+1)
#define CROSSOVER_RATE 0.000
#define MAX_GENERATION_SIZE 0
// real value(4) + decimal point(5)
#define CHROMOSOME_LENGTH 9 

// Constructor
GeneticAlgorithm::GeneticAlgorithm() {

	// generate 50 initial parents by random()
	for (int i = 0; i < 50; i++) {

		list.push_back(Weight(i, random(0, 10), random(0, 10), random(0, 10), random(0, 10), random(0, 10)));
		// first Generation
		Generation = 1;

	}
}

// generate random number between upperLimit and lowLimit
// use random() one-time when generating parents
double GeneticAlgorithm::random(int upperLimit, int lowerLimit) {

	random_device sd;
	mt19937_64 sed(sd());
	uniform_real_distribution<double> range(lowerLimit, upperLimit);

	for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
		Weight wg(i, range(sed), range(sed), range(sed), range(sed), range(sed));
		list.push_back(wg);
	}
}

// generate Weight text file for each generation
void GeneticAlgorithm::writeWeightToFile() {

	Generation++;

	ofstream fileout("Weights[%d].txt", Generation);

	// write weights to file
	if (fileout.is_open()) {

		for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
			fileout << list.at(i).get_verticalBlockWeight() << "   " <<
				list.at(i).get_horizontalBlockWeight() << "   " <<
				list.at(i).get_isMeetGarbageWeight() << "   " <<
				list.at(i).get_isExHighWeight() << "   " <<
				list.at(i).get_isLT2() << endl;
		}

	}
}

// totalFitness : sum of every children in the Generation 
/* 
 * choose randomly considering probability 
 */
int GeneticAlgorithm::selection(int totalFitness, vector<Weight> list) {

	// sum of fitnesses to current fitness 
	double sumFitness = 0;

	// generate random point which decides choice
	// 0 < RANDOM < 1
	// need scale(range) manupulating
	double piece = (double)(totalFitness * RANDOM);

	// roulette wheel selection
	for (int i = 0; i < MAX_GENERATION_SIZE; i++) {

		sumFitness += list.at(i).get_verticalBlockWeight();
		sumFitness += list.at(i).get_horizontalBlockWeight();
		sumFitness += list.at(i).get_isMeetGarbageWeight();
		sumFitness += list.at(i).get_isExHighWeight();
		sumFitness += list.at(i).get_isLT2();

		// return selected child's ID
		if (sumFitness < piece) return i;
	}

	// if the child is not selected, then returns -1
	return -1;
}

// choose using Roulette wheel and crossOver considering mutation 
// get parameters as a pointer of weight string array
void GeneticAlgorithm::crossOver(string * chromo1, string * chromo2) {

	int place = 0;

	// crossover randomly
	// 0 < RANDOM < 1
	for (int i = 0; i < 5; i++) {

		string g1 = "";
		string g2 = "";

		if (RANDOM < CROSSOVER_RATE) {

			place = (int)(RANDOM * CHROMOSOME_LENGTH);
			// crossover
			g1 = chromo1[i].substr(0, place) + chromo2[i].substr(place);
			g2 = chromo2[i].substr(0, place) + chromo1[i].substr(place);

			chromo1[i] = g1;
			chromo2[i] = g2;

		}

	}

}

// mutate children 
void GeneticAlgorithm::mutation(string * chromo) {

	int num = 0;
	string temp = "";

	// consider mutation on every 5 Weights 
	for (int i = 0; i < 5; i++) {

		// how to mutate
		if (RANDOM < MUATATION_RATE) {
			num = (int)(RANDOM * CHROMOSOME_LENGTH);
			temp = chromo->at(num);

			// if randomly picked string is 1 
			// convert to 0
			if (temp.compare("1") == 0) {
				chromo->replace(num, 1, "0");
			}

			else
				chromo->replace(num, 1, "1");
		}
	}
}

// convert real value weights to binary
// 5 digits from rightmost are decimal point part
// rest of digits are real value
// considering notation of decimal point 
// Assume (0 < weight < 10) => max_chromosome_size = 9
string GeneticAlgorithm::double2bin(double real) {

	// real value part
	int num = (int)real;
	int size = 0;
	int index = 0;

	// decimal point part
	int point = real - num;

	// reversed real value weight bits
	string r;
	// reversed decimal point weight bits
	string p;
	// destination of reversing
	string binary;

	// real value part 
	while (1) {

		// store remainder to temp
		r += to_string(num % 2);
		num /= 2;

		if (num == 1) { r += to_string(num); }
		else if (num == 0) break;

	}

	// decimal point part
	for (int i = 0; i < 5; i++) {

		point *= 2;

		if (point > 1) {
			p += to_string(1);
			point -= 1;
		}

		else p += to_string(0);

	}

	/*
	 * binary bits = real value(unknown, 1 to 3) + decimal point(5bits)
	 */

	 // index of reversing bits process
	index = r.size() - 1;

	while (1) {
		// reverse stored remainder 
		binary += r.at(index);
		index--;
	}

	// size of p -1
	index = 4;

	for (int i = 0; i < 5; i++) {
		binary += p.at(index);
		index--;
	}

	return binary;

}

// convert binary bits to double value weights
// considering notation of decimal point 
// parameter is string array
double GeneticAlgorithm::bin2double(string ptr) {

	// size of vector
	int size = 0;
	int num = 0;

	// weight 
	double w = 0;

	// size of the weight binary
	size = ptr.size();

	// calculating point decimal part
	for (int i = 0; i < size; i++) {

		// rightmost bit = 0 or 1
		num = ptr.at(size - 1);

		if (num == 1) {
			w += pow(2, i);
		}
		// left <- right
		size--;

	}
	return w;
}

// running GeneticAlgorithm
void GeneticAlgorithm::runGA() {

	// totalFitness
	int totalfitness = 0;
	int IDs[50];
	int c1 = 0;
	int c2 = 0;
	double num = 0;
	int cnt = 0;

	// performing selection 	
	// totalFitness problem
	for (int i = 0; i < 50; i++) {
		//IDs[i] = selection(totalfitness, &(list.at(i)));
	}
	
	for (int i = 0; i < 50; i++) {

		// if the child is selected
		if (IDs[i] >= 0) {
			c1 = i;
		}

		// crossover two chromosomes
		if (c1 >= 0 && c2 >= 0) {

			string temp1[5];
			string temp2[5];
			// convert weight from double to string
			temp1[0] = double2bin(list.at(c1).get_verticalBlockWeight());
			temp1[1] = double2bin(list.at(c1).get_horizontalBlockWeight());
			temp1[2] = double2bin(list.at(c1).get_isMeetGarbageWeight());
			temp1[3] = double2bin(list.at(c1).get_isExHighWeight());
			temp1[4] = double2bin(list.at(c1).get_isLT2());

			temp2[0] = double2bin(list.at(c2).get_verticalBlockWeight());
			temp2[1] = double2bin(list.at(c2).get_horizontalBlockWeight());
			temp2[2] = double2bin(list.at(c2).get_isMeetGarbageWeight());
			temp2[3] = double2bin(list.at(c2).get_isExHighWeight());
			temp2[4] = double2bin(list.at(c2).get_isLT2());

			// give parameters as a selected chromosome's string weight array
			crossOver(temp1, temp2);

			// generate new generation with new weights
			// write to file and store to new Weight class
			// update New generation to vector<Weight> list
			// what about poolsize?
			// size doesn't match
			num = bin2double(temp1[0]);
			list.at(c1).set_verticalBlockWeight(num);

			num = bin2double(temp1[1]);
			list.at(c1).set_horizontalBlockWeight(num);

			num = bin2double(temp1[2]);
			list.at(c1).set_isMeetGarbageWeight(num);

			num = bin2double(temp1[3]);
			list.at(c1).set_isExHighWeight(num);

			num = bin2double(temp1[4]);
			list.at(c1).set_isLT2(num);

			cnt++;

			num = bin2double(temp2[0]);
			list.at(c2).set_verticalBlockWeight(num);

			num = bin2double(temp2[1]);
			list.at(c2).set_horizontalBlockWeight(num);

			num = bin2double(temp2[2]);
			list.at(c2).set_isMeetGarbageWeight(num);

			num = bin2double(temp2[3]);
			list.at(c2).set_isExHighWeight(num);

			num = bin2double(temp2[4]);
			list.at(c2).set_isLT2(num);

			cnt++;

			// stop generating new generation
			// break loop 
			if (cnt == 49) {}
		}
	}
}

// Destructor
GeneticAlgorithm::~GeneticAlgorithm() {  }

// how to generate 50 children from selected parents
// calculate binary to real value (in bin2double)
