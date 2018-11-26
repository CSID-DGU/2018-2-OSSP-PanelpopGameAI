
#ifndef AIBOARDCONTROLLER_H
#define AIBOARDCONTROLLER_H

#include<queue>
#include"../Game/BoardController.h"
#include"MoveActions.h"

#include "BoardScanner.h"


class AIBoardController : public BoardController {

public:

    enum InputAction {
        UP, RIGHT, DOWN, LEFT, SWAP, RAISE, WAIT
    };

    AIBoardController(Board&);

    void tick() override;

    virtual ~AIBoardController();

    double getFitness_Height(BoardScanner::BlockHeight blockheight);
	double getFitness_HorizonalBlock(BoardScanner::HorizontalMatch horizontalmatch);
	double getFitness_Vertical(BoardScanner::VerticalMatch verticalmatch);

private:
    BoardScanner _scanner;

    std::queue<InputAction> _inputQueue;
    std::queue<CursorMoveAction> _cursorQueue;
    std::queue<BlockMoveAction> _blockMoveQueue;

    double verticalBlockWeight = 0; //수직블록
	double horizontalBlockWeight = 0; //수평블록
    bool isMeetGarbageWeight = 0; //쓰레기와 만나는가
	double isExHighWeight = 0;
    int variance = 0; //분산
    int averageHeight = 0; //평균높이

    void doInput(InputAction);
    void doCursorMove(int x, int y);
    void doBlockMove(int x, int y, int dx, int dy);
    void doVerticalMatch(BoardScanner::VerticalMatch match);
    void doChainMatch(BoardScanner::ChainMatch match);



    void basicVerticalmatchStrat();

};

#endif /* AIBOARDCONTROLLER_H */

