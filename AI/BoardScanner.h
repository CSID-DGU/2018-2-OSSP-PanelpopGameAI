
/* 
 * File:   BoardScanner.h
 * Author: axel
 *
 * Created on September 30, 2016, 10:22 PM
 * edit on Dec 1st 2018
 */

#ifndef BOARDSCANNER_H
#define BOARDSCANNER_H

#include <map>
#include "../Game/Board.h"
#include"MoveActions.h"

class BoardScanner {
public:
    typedef std::map<BlockColor, unsigned int> ColorCounts;
    typedef std::array<ColorCounts, Board::BOARD_HEIGHT> RowColors;
	//추가구조체
	typedef std::array<int, Board::BOARD_WIDTH> BlockHeight; //int 형식으로 width만큼의 어레이

    struct VerticalMatch {
        bool found;
        BlockColor color;
        int bottomRow;
        int topRow;
    };

	//추가구조체
	struct HorizontalMatch {
		bool found;
		BlockColor color;
		int row;
		int howmanyBlock;
		int firstcol;
		int lastcol;
	};

    struct ChainOffsetArea {
        bool found;
        int col, row, //bottom left
        width, offset;
    };

    struct ChainMatch {
        bool found;
        BlockColor color;
        int row, //bottom of gap
        offsetRow, //above gap
        col; //next to gap
        Direction side; //side of gap
    };

    BoardScanner(Board &);

	BlockHeight countBlockHeight();
	bool isthereHole(int row);


    RowColors countRowColors();
    ColorCounts countColorsOn(int row, int startCol, int endCol);
    VerticalMatch findVerticalMatch();
	HorizontalMatch findHorizontalMatch();

    int findColorCol(BlockColor color, int row);
    int findColorOn(BlockColor color, int row, int startCol, int endCol);

	int findSecondColorCol(BlockColor color, int row);
	int findSecondColorOn(BlockColor color, int row, int startCol, int endCol);




    BlockMoveAction findStackFlatteningMove();
    ChainOffsetArea findChainOffsetArea();
    ChainMatch findChainMatch();
    virtual ~BoardScanner();
private:
    Board& _board;
};

#endif /* BOARDSCANNER_H */

