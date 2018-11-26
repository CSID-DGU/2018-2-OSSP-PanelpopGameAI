
/* 
 * File:   BoardScanner.cpp
 * Author: axel
 * 
 * Created on September 30, 2016, 10:22 PM
 */

#include "BoardScanner.h"
#include <iostream>

BoardScanner::BoardScanner(Board& board) :
_board(board) {
}

BoardScanner::BlockHeight BoardScanner::countBlockHeight()
{
	/********
	블럭의 높이를 array로 반환 
	array<int, int>
	*******/
	BoardScanner::BlockHeight counts;
	
	for (int col = 0; col < Board::BOARD_WIDTH; ++col) {

		for (int row = Board::BOARD_HEIGHT - 1; row >= 0; --row) {

			Board::Tile tile = _board.getTile(row, col);
			if (tile.type == TileType::BLOCK && tile.b._state == BlockState::NORMAL) {//blockstate 노멀?
				
				counts[col] = row;
				break;
			}
		}
	}
	return counts;

}



BoardScanner::RowColors BoardScanner::countRowColors() {//

    BoardScanner::RowColors counts;//반환형태

		/*******
	반환값 : RowColors
	[row][색]
	*******/

    for (int row = 0; row < Board::BOARD_HEIGHT; ++row) {
        for (int col = 0; col < Board::BOARD_WIDTH; ++col) {
            Board::Tile tile = _board.getTile(row, col);
            if (tile.type == TileType::BLOCK && tile.b._state == BlockState::NORMAL) {
                BlockColor color = tile.b._color;
                counts[row][color] = counts[row][color] + 1;
            }
        }
    }
    return counts;
}

BoardScanner::ColorCounts BoardScanner::countColorsOn(int row, int startCol, int endCol) {
    BoardScanner::ColorCounts counts;
    for (int col = startCol; col <= endCol; ++col) {
        Board::Tile tile = _board.getTile(row, col);
        if (tile.type == TileType::BLOCK && tile.b._state == BlockState::NORMAL) {
            BlockColor color = tile.b._color;
            counts[color] = counts[color] + 1;
        }
    }
    return counts;
}

BoardScanner::HorizontalMatch BoardScanner::findHorizontalMatch()
{/***********
	반환값 : HorizontalMatch 구조체
	찾으면 {true, 색깔, row ,수평블럭의시작x값,수평블럭의마지막x값}
	없으면 {false} 반환
	********/
	RowColors rowColors = countRowColors();
	for (int colorInt = 0; colorInt < BlockColor::COUNT; ++colorInt) {//0~4 색깔별로 읽는다
		BlockColor color = static_cast<BlockColor> (colorInt);

		for (int row = Board::BOARD_HEIGHT - 1; row >= 0; --row) {
			//std::cout << "Color " << color << " on row " << row << " " << rowColors[row][color] << " times\n";
			if (rowColors[row][color] >= 3) {//3개이상일시
				//밑이 평평한지 보고 return
				int startcol=5, lastcol=0;
				for (int col = 0; col < Board::BOARD_WIDTH; ++col) {
					Board::Tile tile = _board.getTile(row, col);
					if (tile.type == TileType::BLOCK && tile.b._state == BlockState::NORMAL&&colorInt == tile.b._color) {
						if (col < startcol)
							startcol = col;
						if (col > lastcol)
							lastcol = col;
						/*****
						

						
						************/
					}
				}

				if (row == 0)// 맨 땅바닥이면 구멍확인필요없음
					return HorizontalMatch mathch = { true,color,row,rowColors[row][color],startcol,lastcol };

				
				if (row>0 && !isthereHole(row - 1))//row가 땅바닥이아니고 구멍이 없을때

				{
					HorizontalMatch match = { true, color, row,rowColors[row][color],startcol,lastcol };
					return match;
				}

			}
		}


	}

	HorizontalMatch match = {false};//못찾음
	return match;
}


bool BoardScanner::isthereHole(int row)
{
	/******
	빈공간이 있으면 true
	꽉 채워져있으면 false 
	******/

	for (int startcol = 0; startcol < Board::BOARD_WIDTH; ++startcol)
	{
		
		if (_board.getTile(row, startcol).type == AIR)
			return true;

	}
	return false;
}

BoardScanner::VerticalMatch BoardScanner::findVerticalMatch() {
	/***********
	반환값 : VerticalMatch 구조체
	찾으면 {true, 색깔, 수직블럭의시작y값,수직블럭의최상단y값}
	없으면 {false} 반환
	********/

    RowColors rowColors = countRowColors();//가로로 같은색이 몇개있나 반환  counts[row][color]
    for (int colorInt = 0; colorInt < BlockColor::COUNT; ++colorInt) {//0~4 색깔별로 읽는다
        BlockColor color = static_cast<BlockColor> (colorInt);
        int topRow = Board::BOARD_HEIGHT - 1;
        int sameColorFound = 0;
        for (int row = Board::BOARD_HEIGHT - 1; row >= 0; --row) {
            //std::cout << "Color " << color << " on row " << row << " " << rowColors[row][color] << " times\n";
            if (rowColors[row][color] > 0) {
                sameColorFound++;
            }
			else {
                if (sameColorFound >= 3) {
                    //TODO: maybe find max...
                    VerticalMatch match = {true, color, row + 1, topRow};
                    return match;
                }
                topRow = row - 1;
                sameColorFound = 0;
            }
        }
        if (sameColorFound >= 3) {
            VerticalMatch match = {true, color, 0, topRow};
            return match;
        }
    }
    VerticalMatch match = {false};
    return match;
}

int BoardScanner::findColorCol(BlockColor color, int row) {
    return findColorOn(color, row, 0, Board::BOARD_WIDTH - 1);
}

int BoardScanner::findColorOn(BlockColor color, int row, int startCol, int endCol) {
	/**
	반환값 : 왼쪽부터시작해서 처음만나는 color블록.x
	****/

    for (int col = startCol; col <= endCol; ++col) {
        Board::Tile tile = _board.getTile(row, col);
        if (tile.type == TileType::BLOCK && tile.b._color == color) {
            return col;
        }
    }
    return -1;
}

BlockMoveAction BoardScanner::findStackFlatteningMove() { //평평하게 만드는동작
	/**************
	반환값 BlockMoveAction
	옆이 Air면 {현위치x,현위치y,AIr인 부분 x, 현위치y(=Air인부분y)}
	
	못찾으면 {0,0,0,0}
	****************/


    for (int row = Board::BOARD_HEIGHT - 1; row >= 1; --row) {
        for (int col = 0; col < Board::BOARD_WIDTH; ++col) {
            //can be moved left
            if (col > 0 && _board.getTile(row, col).type == BLOCK) {
                for (int dcol = col - 1; dcol >= 0; --dcol) {
                    if (_board.getTile(row, dcol).type != AIR) break;
                    if (_board.getTile(row - 1, dcol).type == AIR) {
                        BlockMoveAction action = {col, row, dcol, row};
                        return action; //(row,col) : 블럭 (row,dcol) : AiR
                    }
                }
            }
            //can be moved right
            if (col < Board::BOARD_WIDTH - 1 && _board.getTile(row, col).type == BLOCK) {
                for (int dcol = col + 1; dcol < Board::BOARD_WIDTH; ++dcol) {
                    if (_board.getTile(row, dcol).type != AIR) break;
                    if (_board.getTile(row - 1, dcol).type == AIR) {
                        BlockMoveAction action = {col, row, dcol, row};
                        return action;
                    }
                }
            }
        }
    }
    BlockMoveAction action = {0, 0, 0, 0};
    return action;
}



//////////////////////////////////////
BoardScanner::ChainOffsetArea BoardScanner::findChainOffsetArea() {//안씀
    ChainOffsetArea area;
    area = {false, 0, 0, 0, 0};

    for (int row = 0; row < Board::BOARD_HEIGHT; ++row) {
        for (int col = 0; col < Board::BOARD_WIDTH; ++col) {
            Board::Tile tile = _board.getTile(row, col);
            if (tile.type == TileType::BLOCK
                    && tile.b._state == BlockState::EXPLODING) {
                area.found = true;
                area.col = col;
                area.row = row;
                goto findSize;
            }
        }
    }
    if (!area.found) {
        return area;
    }
findSize:
    for (int row = area.row; row < Board::BOARD_HEIGHT; ++row) {
        Board::Tile tile = _board.getTile(row, area.col);
        if (tile.type == TileType::BLOCK
                && tile.b._state == BlockState::EXPLODING) {
            ++area.offset;
        } else {
            break;
        }
    }
    for (int col = 0; area.col < Board::BOARD_WIDTH; ++col) {
        Board::Tile tile = _board.getTile(area.row, col);
        if (tile.type == TileType::BLOCK
                && tile.b._state == BlockState::EXPLODING) {
            ++area.width;
        } else {
            break;
        }
    }
    return area;
}




BoardScanner::ChainMatch BoardScanner::findChainMatch() {//안씀
    ChainMatch match;
    ChainOffsetArea area = findChainOffsetArea();
    if (!area.found) {
        match.found = false;
        return match;
    }

    int row = 0;
    BoardScanner::ColorCounts lowerCount;
    BoardScanner::ColorCounts offsetCount = countColorsOn(row + area.offset, 0, Board::BOARD_WIDTH - 1);
    ;

    auto countColors = [&](int matchCol, Direction side) {
        for (int colorInt = 0; colorInt < BlockColor::COUNT; ++colorInt) {
            BlockColor color = static_cast<BlockColor> (colorInt);
            if ((area.width == 1 && lowerCount[color] >= 2 && offsetCount[color] > 0)
                    || (area.width > 1 && lowerCount[color] > 0 && offsetCount[color] >= 2)) {
                match.found = true;
                match.color = color;
                match.side = side;
                match.col = matchCol;
                match.row = row;
                match.offsetRow = row + area.offset;
                return match;
            }
        }

        match.found = false;
        return match;
    };

    if (area.col > 0) {
        for (row = area.row; row + area.offset < Board::BOARD_HEIGHT; ++row) {
            lowerCount = countColorsOn(row, 0, area.col - 1);
            return countColors(area.col - 1, LEFT);
        }
    }
    if (area.col + area.width - 1 < Board::BOARD_WIDTH) {
        for (row = area.row; row + area.offset < Board::BOARD_HEIGHT; ++row) {
            lowerCount = countColorsOn(row, area.col + area.width - 1, Board::BOARD_WIDTH - 1);
            return countColors(area.col + area.width - 1, RIGHT);
        }
    }

    match.found = false;
    return match;
}

BoardScanner::~BoardScanner() {
}

