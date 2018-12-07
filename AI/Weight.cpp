#pragma once
/*
 * GeneticAlgorithm.cpp
 *
 *  Modified on: Dec 7, 2018
 *      Author: blue
 */
#include "Weight.h"
#include <String>

 //using namespace std;

 // Constructor : initialize fields of Weight class
Weight::Weight(int _ID, double _verticalBlockWeight, double _horizontalBlockWeight,
	double _isMeetGarbageWeight, double _isExHighWeight) {
	ID = _ID;
	verticalBlockWeight = _verticalBlockWeight;
	horizontalBlockWeight = _horizontalBlockWeight;
	isMeetGarbageWeight = _isMeetGarbageWeight;
	isExHighWeight = _isExHighWeight;
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

int Weight::get_ID() {
	return ID;
}

int Weight::get_score() {
	return score;
}

void Weight::set_verticalBlockWeight(double _verticalBlockWeight) {
	verticalBlockWeight = _verticalBlockWeight;
}

void Weight::set_horizontalBlockWeight(double _horizontalBlockWeight) {
	horizontalBlockWeight = _horizontalBlockWeight;
}

void Weight::set_isMeetGarbageWeight(double _isMeetGarbageWeight) {
	isMeetGarbageWeight = _isMeetGarbageWeight;
}

void Weight::set_isExHighWeight(double _isExHighWeight) {
	isExHighWeight = _isExHighWeight;
}

void Weight::set_score(int _score){
	score = _score;
}
