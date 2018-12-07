#pragma once
/*
 * Weight.h
 *
 *  Modified on: Dec 7, 2018
 *      Author: blue
 */

#ifndef AI_WEIGHT_H_
#define AI_WEIGHT_H_
#include <string>

using namespace std;

class Weight {

private:
	// weight of the number of vertical block
	double verticalBlockWeight;
	// weight of the number of horizontal block
	double horizontalBlockWeight;
	// weight of the condition that is meet the Garbage block or not
	double isMeetGarbageWeight;
	// weight of the condition that is there a especially high line (vertical)
	double isExHighWeight;
	// name of each child
	int ID;
	// game score of each child
	int score;

public:
	// Constructor
	Weight(int _ID, double _verticalBlockWeight, double _horizontalBlockWeight,
		double _isMeetGarbageWeight, double _isExHighWeight);
	
	//getter
	double get_verticalBlockWeight();
	double get_horizontalBlockWeight();
	double get_isMeetGarbageWeight();
	double get_isExHighWeight();

	//setter
	void set_verticalBlockWeight(double _verticalBlockWeight);
	void set_horizontalBlockWeight(double _horizontalBlockWeight);
	void set_isMeetGarbageWeight(double _isMeetGarbageWeight);
	void set_isExHighWeight(double _isExHighWeight);
	void set_score(int _score);

	int get_ID();
	int get_score();
}

#endif /* AI_WEIGHT_H_ */
