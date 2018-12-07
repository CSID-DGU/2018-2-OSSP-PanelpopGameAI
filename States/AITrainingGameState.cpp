
/* 
 * File:   AIGameState.cpp
 * Author: ysy
 * 
 * Created on September 26, 2016, 11:18 PM
 */

#include "AITrainingGameState.h"
#include "../AI/GeneticAlgorithm.h"


#include "../AI/AIBoardController.h"
#include "../Game/BoardEventHandler.h"
#include "../Game/GameEventHandler.h"
#include "StateManager.h"
#include "../Game/KeyboardController.h"
#include "../Game/VsGame.h"
#include "../Rendering/VsGameRenderer.h"
#include "AITrainingGameState.h"

AITrainingGameState::AITrainingGameState() {
	_game = new EndlessGame(new GameEventHandler());
	_gameRenderer = new EndlessGameRenderer((EndlessGame &)* _game);
	_game->getBoard(0).setEventHandler(new BoardEventHandler(*_gameRenderer, 0));
	//    _playerBoardController = new KeyboardController(_game->getBoard(0),
	//            StateManager::getInstance().getP1keys());

	_opponentBoardcontollers.push_back(new AIBoardController(_game->getBoard(0)));
}


void AITrainingGameState::tick() {
	InputManager& input = InputManager::getInstance();


	GeneticAlgorithm geneticAlgorithm = new GeneticAlgorithm();
	AIBoardController* temp = _opponentBoardcontollers.at(0);
	temp->horizontalBlockWeight = geneticAlgorithm.list.at(0);// <- ÀÌºÎºÐ

	//geneticAlgorithm.



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
			geneticAlgorithm.crossOver();


		}
	
	
	}
	_game->tick();
	_gameRenderer->tick();
}

