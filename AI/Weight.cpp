/*
 * GeneticAlgorithm.cpp
 *
 *  Modified on: Nov 19, 2018
 *      Author: limjuhee
 */
#include "Weight.h"
#include <String>

 //using namespace std;

 // Constructor : initialize fields of Weight class
Weight::Weight(int _ID, double _verticalBlockWeight, double _horizontalBlockWeight,
	double _isMeetGarbageWeight, double _isExHighWeight, double _isLT2) {
	verticalBlockWeight = _verticalBlockWeight;
	horizontalBlockWeight = _horizontalBlockWeight;
	isMeetGarbageWeight = _isMeetGarbageWeight;
	isExHighWeight = _isExHighWeight;
	isLT2 = _isLT2;
	ID = _ID;
}

double Weight::get_verticalBlockWeight() {
	return verticalBlockWeight;
}

double Weight::get_horizontalBlockWeight() {
	return horizontalBlockWeight;
}

double Weight::get_isMeetGarbageWeight() {
	return isMeetGarbageWeight;
}

double Weight::get_isExHighWeight() {
	return isExHighWeight;
}

double Weight::get_isLT2() {
	return isLT2;
}

int Weight::get_ID() {
	return ID;
}

int Weight::get_score() {
	return score;
}
