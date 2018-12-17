#pragma once
/*
 * GeneticAlgorithm.cpp
 *
 *  Modified on: Dec 18, 2018
 *      Author: blue
 */
#include "Weight.h"
#include <string>

 //using namespace std;

 // Constructor : initialize fields of Weight class
Weight::Weight(int _ID, double _verticalBlockWeight, double _horizontalBlockWeight,
	double _isExHighWeight, double _numOfBlock, int _maxScore, int _score) {
	ID = _ID;
	verticalBlockWeight = _verticalBlockWeight;
	horizontalBlockWeight = _horizontalBlockWeight;
	isExHighWeight = _isExHighWeight;
	numOfBlock = _numOfBlock;
	maxScore = _maxScore;
	score = _score;
}

//getter

double Weight::get_verticalBlockWeight() {
	return verticalBlockWeight;
}

double Weight::get_horizontalBlockWeight() {
	return horizontalBlockWeight;
}

double Weight::get_isExHighWeight() {
	return isExHighWeight;
}

double Weight::get_numOfBlock() {
	return numOfBlock;
}

int Weight::get_ID() {
	return ID;
}

int Weight::get_score() {
	return score;
}

int Weight::get_maxScore() {
	return maxScore;
}

//setter

void Weight::set_verticalBlockWeight(double _verticalBlockWeight) {
	verticalBlockWeight = _verticalBlockWeight;
}

void Weight::set_horizontalBlockWeight(double _horizontalBlockWeight) {
	horizontalBlockWeight = _horizontalBlockWeight;
}

void Weight::set_isExHighWeight(double _isExHighWeight) {
	isExHighWeight = _isExHighWeight;
}

void Weight::set_numOfBlock(double _numOfBlock) {
	numOfBlock = _numOfBlock;
}

void Weight::set_score(int _score) {
	score = _score;
}

void Weight::set_maxScore(int _maxscore) {
	maxScore = _maxscore;
}

Weight::~Weight() {}
