
/* 
 * File:   AIGameState.h
 * Author: ysy
 *
 * Created on 2018/12/7
 */

#ifndef AITRAININGGAMESTATE_H
#define AITRAININGGAMESTATE_H

#include "../AI/AIBoardController.h"
#include "GameState.h"

#include "../AI/GeneticAlgorithm.h"

extern vector<Weight> list;

int maxScore;

class AITrainingGameState : public GameState{
public:
	AITrainingGameState();
	void tick();
	
protected:
	GeneticAlgorithm* geneticAlgorithm;
	std::vector<AIBoardController*> _opponentBoardcontollers;
	AIBoardController* temp;
	int count = 0;
	
private:

};

#endif /* AITRAININGGAMESTATE_H */
