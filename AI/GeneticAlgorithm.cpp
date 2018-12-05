/*
 * GeneticAlgorithm.cpp
 *
 *  Modified on: Dec 5, 2018
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
			// lowLimit = 0, upperLimit = 10
			list.push_back(Weight(i, random(0, 10), random(0, 10), random(0, 10), random(0, 10), random(0, 10)));
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

	return range(sed);

}

// generate Weight text file for each generation
void GeneticAlgorithm::writeWeightToFile() {

	Generation++;

	ofstream fileout("Weights[%d].txt", Generation);

	// write weights to file
	if (fileout.is_open()) {

		for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
			fileout << i << "   " << list.at(i).get_verticalBlockWeight() << "   " <<
				list.at(i).get_horizontalBlockWeight() << "   " <<
				list.at(i).get_isMeetGarbageWeight() << "   " <<
				list.at(i).get_isExHighWeight() << "   " <<
				list.at(i).get_isLT2() << endl;
		}
	}

}

// most high-scored child, high-chance 
int GeneticAlgorithm::selection(int index, vector<Weight> list) {

	int score = 0;
	int maxScore = 0;

	// score = _game.getBoard(0).getScore();

	// piece < score 
	double piece = (double)(maxScore * random(0,1));

	// roulette wheel selection
	for (int i = index; i < MAX_GENERATION_SIZE; i++) {

		// return selected child's IDs
		if (score < piece) return i;
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

		int size1 = chromo1[i].size();
		int size2 = chromo2[i].size();

		if (random(0, 1) < CROSSOVER_RATE) {

			place = (int)(random(0, 1) * CHROMOSOME_LENGTH);

			// if random place > weight's size
			if (place > size1 || place > size2) {
				if (size1 > size2) place = size2 - 1;
				else place = size1 - 1;
			}

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

		int size1 = chromo[i].size();

		// how to mutate
		if (random(0, 1) < MUATATION_RATE) {
			num = (int)(random(0, 1) * CHROMOSOME_LENGTH);

			if (num > size1) num = size1-1;
			
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
// Assume (0 < weight < 10) => max_chromosome_size = 9
string GeneticAlgorithm::double2bin(double real) {

	// real value part
	int num = (int)real;
	// decimal point part
	double point = real - num;
	int size = 0;
	int index = 0;

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

		if (num == 1) { r += to_string(1); }
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
		if (index < 0) break;
	}
	
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
	int index = size - 1;

	for (int i = 0; i < size; i++) {

		// rightmost bit = 0 or 1
		num = ptr.at(index);

		if (num == '1') {
			w += pow(2, i);
		}
		// left <- right
		index--;
	}
	return w;
}

// running GeneticAlgorithm
void GeneticAlgorithm::runGA() {

	// totalFitness
	int totalfitness = 0;
	int c1 = 0;
	int c2 = 0;
	double num = 0;
	int cnt = 0;
	// child's id 
	int index = 0;
	int temp = 0;
	int new_id = 0;

	while (new_id < MAX_GENERATION_SIZE) {

		// performing selection 

		// select first candidate
		while (1) {
			temp = selection(index, list);
			index++;
			if (temp >= 0) break;
			else if (index == 49) index = 0;
		}
		c1 = temp;

		// select second candidate
		while (1) {
			temp = selection(index, list);
			index++;
			if (temp >= 0) break;
			else if (index == 49) index = 0;
		}
		c2 = temp;
		index = 0;

		// crossover two chromosomes

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
		// consider mutation
		mutation(temp1);
		mutation(temp2);

		// update New generation to vector<Weight> list
		new_id++;

		// new born baby 1
		num = bin2double(temp1[0]);
		list.at(new_id).set_verticalBlockWeight(num);

		num = bin2double(temp1[1]);
		list.at(new_id).set_horizontalBlockWeight(num);

		num = bin2double(temp1[2]);
		list.at(new_id).set_isMeetGarbageWeight(num);

		num = bin2double(temp1[3]);
		list.at(new_id).set_isExHighWeight(num);

		num = bin2double(temp1[4]);
		list.at(new_id).set_isLT2(num);

		new_id++;

		// new born baby 2
		num = bin2double(temp2[0]);
		list.at(new_id).set_verticalBlockWeight(num);

		num = bin2double(temp2[1]);
		list.at(new_id).set_horizontalBlockWeight(num);

		num = bin2double(temp2[2]);
		list.at(new_id).set_isMeetGarbageWeight(num);

		num = bin2double(temp2[3]);
		list.at(new_id).set_isExHighWeight(num);

		num = bin2double(temp2[4]);
		list.at(new_id).set_isLT2(num);

	}
	
	// write to file and store to new Weight list
	writeWeightToFile();
}

// Destructor
GeneticAlgorithm::~GeneticAlgorithm() {  }
