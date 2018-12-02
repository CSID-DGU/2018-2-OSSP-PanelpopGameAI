
#include <stdexcept>
#include<cmath>

#include "AIBoardController.h"

#include <array>
AIBoardController::AIBoardController(Board& board) :
BoardController(board),
_scanner(board) {
}

void AIBoardController::tick() {
    if (_board.getState() != Board::BoardState::RUNNING || _board.getTicksRun() % 5 != 0) return;
    if (!_inputQueue.empty()) {//커서움직이는거
        doInput(_inputQueue.front());
        _inputQueue.pop();
    } else if
        (!_cursorQueue.empty()) {//안쓰임
        CursorMoveAction move = _cursorQueue.front();
        doCursorMove(move.x, move.y);
        _cursorQueue.pop();
    } else if (!_blockMoveQueue.empty()) {
        BlockMoveAction move = _blockMoveQueue.front();
        doBlockMove(move.x, move.y, move.dx, move.dy);
        _blockMoveQueue.pop();
    } else {
        basicVerticalmatchStrat();
    }
}

void AIBoardController::doInput(InputAction action) {
    switch (action) {
        case (UP):
            _board.inputMoveCursor(Direction::UP);
            break;
        case (RIGHT):
            _board.inputMoveCursor(Direction::RIGHT);
            break;
        case (DOWN):
            _board.inputMoveCursor(Direction::DOWN);
            break;
        case (LEFT):
            _board.inputMoveCursor(Direction::LEFT);
            break;
        case (SWAP):
            _board.inputSwapBlocks();
            break;
        case (RAISE):
            _board.inputForceStackRaise();
            break;

        case (WAIT):
            break;
    }

}

void AIBoardController::doBlockMove(int x, int y, int dx, int dy) {



    if (dy > y) {
        throw std::invalid_argument("Can't move block upwards");
    }
    if (dx > x) { //move right
        doCursorMove(x, y); //x,y까지 커서를 옮김
        for (int i = 0; i < dx - x; i++) {
            _inputQueue.push(SWAP);
            //_inputQueue.push(WAIT);
            //_inputQueue.push(WAIT);
            _inputQueue.push(RIGHT);

        }
    }
    if (dx < x) { //move left
        doCursorMove(x - 1, y);
        for (int i = 0; i < x - dx; i++) {
            _inputQueue.push(SWAP);
            //_inputQueue.push(WAIT);
            //_inputQueue.push(WAIT);
            _inputQueue.push(LEFT);
        }
    }
}

void AIBoardController::doCursorMove(int x, int y) { //목표지점 (x,y)까지 커서를 옮기는 함수
    int curX = _board.getCursorX();//현재커서위치 x
    int curY = _board.getCursorY();//현재커서위치 y

    if (x > curX) {
        for (int i = 0; i < x - curX; i++) {
            _inputQueue.push(RIGHT);
        }
    }
    if (x < curX) {
        for (int i = 0; i < curX - x; i++) {
            _inputQueue.push(LEFT);
        }
    }
    if (y > curY) {
        for (int i = 0; i < y - curY; i++) {
            _inputQueue.push(UP);
        }
    }
    if (y < curY) {
        for (int i = 0; i < curY - y; i++) {
            _inputQueue.push(DOWN);
        }
    }

}

void AIBoardController::basicVerticalmatchStrat() { //수정

	


	double horizonfitness;
	double verticalfitness;

	int numOfBlock = 0;
	BoardScanner::BlockHeight blockheight=_scanner.countBlockHeight();
	double heightfitness = getFitness_Height(blockheight);//높이평균fitness-flatteness

	

	for (int i = 0; i < Board::BOARD_WIDTH; i++)
		numOfBlock += blockheight[i];
		
	double numofBlockfitness=getFitness_numOfBlock(numOfBlock);


	BoardScanner::HorizontalMatch horizMatch=_scanner.findHorizontalMatch();
	if(horizMatch.found)
		horizonfitness = getFitness_HorizonalBlock(horizMatch);//수평블록fitness
	else 
		horizonfitness = 0;



    BoardScanner::VerticalMatch vertMatch = _scanner.findVerticalMatch(); //수직찾는거
	
	if (vertMatch.found)
		verticalfitness = getFitness_Vertical(vertMatch);//수평블록fitness
	else
		verticalfitness = 0;
	

	fitnessarr fitarr = { verticalfitness ,horizonfitness, heightfitness ,numofBlockfitness };


	int temp=findmaxnum(fitarr);
	switch (temp) {
	
	case 0: //verticalfitness

		doVerticalMatch(vertMatch);
		break;
	
	case 1://horizonfitness
		doHorizonalBlockMatch(horizMatch);
		break;

	case 2:// heightfitness
		BlockMoveAction flatteningMove = _scanner.findStackFlatteningMove();
		_blockMoveQueue.push(flatteningMove);
		break;

	case 3://umofBlockfitness
		_inputQueue.push(RAISE);
		break;	
	
	}




	/****

	if (heightfitness >= horizonfitness) { // 3개중에 큰값
	
		if (heightfitness >= verticalfitness) {
			lockMoveAction flatteningMove = _scanner.findStackFlatteningMove();
			_blockMoveQueue.push(flatteningMove);
		
		}// heightfitness 가 클때
		else//verticalfitness가 클때
		{
			doVerticalMatch(vertMatch);
		}
	
	}
	else {
	
		if (horizonfitness >= verticalfitness) {
		
			doHorizonalBlockMatch(horizMatch);
		
		}//horizonfitness가 클때
		else//verticalfitness가 클때 
		{
			doVerticalMatch(vertMatch);
		}
	
	}
	***/
	
	/*
	
	BlockMoveAction flatteningMove = _scanner.findStackFlatteningMove();
    if (_board.isPanic() && flatteningMove.y != 0) //평평하게해야할부분이있으면 
	{
        _blockMoveQueue.push(flatteningMove);
        return;
    }

    if (!vertMatch.found) {//수직을 못찾으면
        _inputQueue.push(RAISE); //올리는거
        return;
    }
    doVerticalMatch(vertMatch);
	*/
}
int AIBoardController::findmaxnum(AIBoardController::fitnessarr arr ) {
	int max = 0;
	int maxnum = 0;
	for (int i = 0; i < arr.max_size(); i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			maxnum = i;
		}
	}
	
	return i;

}


void AIBoardController::doVerticalMatch(BoardScanner::VerticalMatch match) {
	/**********
	수직찾으면 알아서 큐로 동작
	
	************/
	

    int firstCol = _scanner.findColorCol(match.color, match.topRow);//왼쪽부터시작해서 처음만나는 color블록.x
    int firstRow = match.topRow - 1;
    int alt = 0;
    for (int i = 0; i <= firstRow - match.bottomRow; ++i) {
        int altRow = (i % 2 == 0 ? firstRow - alt : match.bottomRow + alt++);
        int col = _scanner.findColorCol(match.color, altRow);
        BlockMoveAction action = {col, altRow, firstCol, altRow};
        _blockMoveQueue.push(action);
    }
}

void AIBoardController::doChainMatch(BoardScanner::ChainMatch match) { //안씀
    //doesn't quite work yet, blocks cannot be moved over incomplete rows (duh)
    //also it tries to accomplish too mush in too little time (maybe just look for specific cases then)

    //upper (offset)
    int col = _scanner.findColorCol(match.color, match.offsetRow);
    BlockMoveAction action = {col, match.offsetRow, match.col + (match.side == Direction::LEFT ? 1 : -1), match.offsetRow};
    _blockMoveQueue.push(action);
    //lower
    if (match.side == Direction::LEFT) {
        col = _scanner.findColorOn(match.color, match.row, 0, match.col);
    } else {
        col = _scanner.findColorOn(match.color, match.row, match.col, Board::BOARD_WIDTH - 1);
    }
    action = {col, match.row, match.col, match.row};
    _blockMoveQueue.push(action);

}

void AIBoardController::doHorizonalBlockMatch(BoardScanner::HorizontalMatch match)
{// 3개밖에 못맞춤

	int firstcol = match.firstcol;
	int lastcol = match.lastcol;
	int secondcol = _scanner.findSecondColorCol(match.color, match.topRow);
	int matchrow = match.row;


	BlockMoveAction action = { firstcol,matchrow , secondcol, matchrow };
	_blockMoveQueue.push(action);
	
	action = { lastcol,matchrow , secondcol, matchrow };
	_blockMoveQueue.push(action);

}

AIBoardController::~AIBoardController() {
}

double AIBoardController::getFitness_Height(BoardScanner::BlockHeight blockheight)
{
	/******
	fitness=높이의 표준편차 * 가중치
	******/

	double fitness;
	double sum = 0;
	double AVG;//평균
	double STD;//표준편차
	double variance;//분산

	for (int i = 0; i < blockheight.size(); i++) {
		
		sum += blockheight[i];
	
	}
	AVG = sum / 5;                            // 평균계산
	

	sum = 0;

	for (int i = 0; i < blockheight.size(); i++)
	{
		sum += pow(blockheight[i] - AVG, 2);                  // pow 함수를이용해서제곱계산

	}
	variance = sum / 5;                                //  분산계산
	STD = sqrt(variance);
	fitness=STD*isExHighWeight; //표준편차에 가중치곱해서 fitness 계산

	return fitness;
}

double AIBoardController::getFitness_HorizonalBlock(BoardScanner::HorizontalMatch horizmatch)
{/********

fitness=수평블록갯수 *  가중치
 ************/
	double fitness = (double)horizmatch.howmanyBlock*horizontalBlockWeight;

	return fitness;
}

double AIBoardController::getFitness_Vertical(BoardScanner::VerticalMatch verticalmatch)
{

	/*******
	fitness = 수직불록갯수 * 가중치
	********/

	double fitness = (double)(verticalmatch.topRow - verticalmatch.bottomRow + 1)*verticalBlockWeight;

	return fitness;
}

double AIBoardController::getFitness_numOfBlock(int num)
{

	double fitness = num * numblockWeight;
	return fitness;
}


