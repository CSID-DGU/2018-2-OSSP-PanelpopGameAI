
/* 
 * File:   AITraingingGameState.cpp
 * Author: ysy
 * 
 * Created on 8/12/2018
 */

#include "AITrainingGameState.h"


#include "../AI/AIBoardController.h"
#include <SDL2/SDL_scancode.h>


#include "../Game/BoardEventHandler.h"
#include "../Game/GameEventHandler.h"
#include "StateManager.h"

#include "../AI/Weight.h"
#include "EndlessGameState.h"




AITrainingGameState::AITrainingGameState() {//
	_game = new EndlessGame(new GameEventHandler());
	_gameRenderer = new EndlessGameRenderer((EndlessGame &)* _game);
	_game->getBoard(0).setEventHandler(new BoardEventHandler(*_gameRenderer, 0));
	temp = new AIBoardController(_game->getBoard(0));
	_opponentBoardcontollers.push_back(temp);
	
	
	geneticAlgorithm= new GeneticAlgorithm();

/* original code
	temp->set_horizontalBlockWeight(weightList.at(0).get_horizontalBlockWeight());//
        temp->set_isExHighWeight(weightList.at(0).get_isExHighWeight());
        temp->set_verticalBlockWeight(weightList.at(0).get_verticalBlockWeight());
*/


	temp->set_horizontalBlockWeight(10);//
        temp->set_isExHighWeight(2);
        temp->set_verticalBlockWeight(8);




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
		for (BoardController* controller : _opponentBoardcontollers) {
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
		int currentScore = _game->getBoard(0).getScore();
		weightList.at(count).set_score(currentScore); //sco
		if (maxScore <= currentScore) maxScore = currentScore;



		++count;
		
		
		if (count == weightList.size()) { //
			
			weightList.at(count-1).set_maxScore(maxScore);

			geneticAlgorithm->runGA(); 
			count = 0;
			temp->set_horizontalBlockWeight(weightList.at(count).get_horizontalBlockWeight());//
			temp->set_isExHighWeight(weightList.at(count).get_isExHighWeight());
			temp->set_verticalBlockWeight(weightList.at(count).get_verticalBlockWeight());
		//	temp->ID = weightList.at(count).get_ID;
			maxScore = 0;
		}
		else {
			temp->set_horizontalBlockWeight(weightList.at(count).get_horizontalBlockWeight());// 
			temp->set_isExHighWeight(weightList.at(count).get_isExHighWeight());
			temp->set_verticalBlockWeight(weightList.at(count).get_verticalBlockWeight());
		//	temp->ID =weightList.at(count).get_ID;
		}
		_game->reset();
	
	}
	_game->tick();
	_gameRenderer->tick();
}

