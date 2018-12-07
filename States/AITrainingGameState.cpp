
/* 
 * File:   AIGameState.cpp
 * Author: ysy
 * 
 * Created on September 26, 2016, 11:18 PM
 */

#include "AITrainingGameState.h"


#include "../AI/AIBoardController.h"



#include "../Game/BoardEventHandler.h"
#include "../Game/GameEventHandler.h"
#include "StateManager.h"
#include "../Game/KeyboardController.h"
#include "../Game/VsGame.h"
#include "../Rendering/VsGameRenderer.h"
#include "AITrainingGameState.h"
#include "../AI/Weight.h"
#include "EndlessGameState.h"



AITrainingGameState::AITrainingGameState() {//
	_game = new EndlessGame(new GameEventHandler());
	_gameRenderer = new EndlessGameRenderer((EndlessGame &)* _game);
	_game->getBoard(0).setEventHandler(new BoardEventHandler(*_gameRenderer, 0));
	//    _playerBoardController = new KeyboardController(_game->getBoard(0),
	//            StateManager::getInstance().getP1keys());
	temp = new AIBoardController(_game->getBoard(0));
	_opponentBoardcontollers.push_back(temp);
	
	
	geneticAlgorithm= new GeneticAlgorithm();
//	temp->horizontalBlockWeight = list.at(0).get_horizontalBlockWeight;// <
//	temp->isExHighWeight = list.at(0).get_isExHighWeight;
//	temp->verticalBlockWeight = list.at(0).get_verticalBlockWeight;
	temp->set_horizontalBlockWeight(list.at(count).get_horizontalBlockWeight);//
                        temp->set_isExHighWeight(list.at(count).get_isExHighWeight);
                        temp->set_verticalBlockWeight(list.at(count).get_verticalBlockWeight);



	temp->ID = list.at(0).get_ID;


}


void AITrainingGameState::tick() {
	InputManager& input = InputManager::getInstance();

	

	if (input.keyDown(SDL_SCANCODE_5)) {
		_game->inputTogglePause();
	}
	if (input.keyDown(SDL_SCANCODE_ESCAPE)) {
		_game->reset();
	}
	if (_game->getState() == Game::State::RUNNING) {
		//  _playerBoardController->tick();
		for (AIBoardController* controller : _opponentBoardcontollers) {
			controller->tick();
		}
	}
	else if (_game->getState() == Game::State::PAUSED) {
		//send input to pause menu instead
		PauseMenu& menu = _game->getPauseMenu();
		menu.handleInput();
	}
	else if (_game->getState() == Game::State::ENDED) {
		//TODO: change to any key and add timeout..?
		if (input.keyDown(SDL_SCANCODE_5)) {
		
			
		}
		int currentScore = _game->getBoard(0).getScore;
		list.at(count).set_score = currentScore; //sco
		if (maxScore <= currentScore) maxScore = currentScore;



		++count;
		
		
		if (count == list.size()) { //
			geneticAlgorithm->runGA(); 
			count = 0;
			temp->set_horizontalBlockWeight(list.at(count).get_horizontalBlockWeight);//
			temp->set_isExHighWeight(list.at(count).get_isExHighWeight);
			temp->set_verticalBlockWeight(list.at(count).get_verticalBlockWeight);
			temp->ID = list.at(count).get_ID;
			maxScore = 0;
		}
		else {
			temp->set_horizontalBlockWeight(list.at(count).get_horizontalBlockWeight);// 
			temp->set_isExHighWeight(list.at(count).get_isExHighWeight);
			temp->set_verticalBlockWeight(list.at(count).get_verticalBlockWeight);
			temp->ID = list.at(count).get_ID;
		}
		_game->reset();
	
	}
	_game->tick();
	_gameRenderer->tick();
}
