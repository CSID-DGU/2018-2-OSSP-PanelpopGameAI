
/* 
 * File:   AITrainingGameState.h
 * Author: ysy
 *
 * Created on 2018/12/7
 */

#ifndef STATES_AITRAININGGAMESTATE_H
#define STATES_AITRAININGGAMESTATE_H

#include "../Game/EndlessGame.h"
#include "../Rendering/EndlessGameRenderer.h"
#include "State.h"
#include "GameState.h"

#include "../AI/AIBoardController.h"

#include "../AI/GeneticAlgorithm.h"




extern vector<Weight> weightList;


class AITrainingGameState : public GameState{
public:
	AITrainingGameState();
	void tick() override;
	
protected:
	GeneticAlgorithm* geneticAlgorithm;
//	std::vector<AIBoardController*> _opponentBoardcontollers;
	AIBoardController* temp;
	int count = 0;
	int maxScore;

	
private:

};

#endif /* STATES_AITRAININGGAMESTATE_H */
