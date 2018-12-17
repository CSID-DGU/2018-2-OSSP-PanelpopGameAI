#pragma once
/*
 * Weight.h
 *
 *  Modified on: Dec 18, 2018
 *      Author: blue
 */

#ifndef AI_WEIGHT_H_
#define AI_WEIGHT_H_
#include <string>

using namespace std;

class Weight {

private:
	// name of each child
	int ID;
	// weight of the number of vertical block
	double verticalBlockWeight;
	// weight of the number of horizontal block
	double horizontalBlockWeight;
	// weight of the condition that is there a especially high line (vertical)
	double isExHighWeight;
	// num of block
	double numOfBlock;
	// only use 49's 
	int maxScore;
	// game score of each child
	int score;

public:
	// Constructor
	Weight(int _ID, double _verticalBlockWeight, double _horizontalBlockWeight,
		 double _isExHighWeight, double _numOfBlock, int _maxScore, int _score);

	//getter
	double get_verticalBlockWeight();
	double get_horizontalBlockWeight();
	double get_isExHighWeight();
	double get_numOfBlock();

	int get_score();
	int get_maxScore();
	int get_ID();

	//setter
	void set_verticalBlockWeight(double _verticalBlockWeight);
	void set_horizontalBlockWeight(double _horizontalBlockWeight);
	void set_isExHighWeight(double _isExHighWeight);
	void set_numOfBlock(double _numOfBlock);

	void set_score(int _score);
	void set_maxScore(int _maxscore);

	// Destructor
	~Weight();

};

#endif /* AI_WEIGHT_H_ */
