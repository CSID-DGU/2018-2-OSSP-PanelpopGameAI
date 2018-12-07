
/* 
 * File:   AIGameState.h
 * Author: axel
 *
 * Created on September 26, 2016, 11:18 PM
 */

#ifndef AIGAMESTATE_H
#define AIGAMESTATE_H

#include "../AI/AIBoardController.h"
#include "GameState.h"


class AITrainingGameState : public GameState{
public:
	AITrainingGameState();
	void tick();

protected:
	std::vector<AIBoardController*> _opponentBoardcontollers;
private:

};

#endif /* AIGAMESTATE_H */

