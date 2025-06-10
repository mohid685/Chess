#pragma once
#include "Utility.h"

using namespace std;

class Board;
class Piece
{
protected:
	int row_index;
	int col_index;
	Color C;
	Board* board_ptr;
	bool moved;
public:
	Piece(int row_index, int col_index, Color C,Board* board_ptr);
	virtual void draw() = 0;
	void move(int updated_row_index,int updated_col_index);
	Color getColor();
	bool isHorizontalPath(int S_row_index,int S_col_index,int D_row_index,int D_col_index);
	bool isVerticalPath(int S_row_index, int S_col_index,int D_row_index, int D_col_index);
	bool isDiagonalPath(int S_row_index, int S_col_index,int D_row_index, int D_col_index);
	bool isHorizontalPathClear(Board* board_ptr,int S_row_index, int S_col_index,int D_row_index, int D_col_index);
	bool isVerticalPathClear(Board* board_ptr, int S_row_index, int S_col_index,int D_row_index, int D_col_index);
	bool isDiagonalPathClear(Board* board_ptr, int S_row_index, int S_col_index,int D_row_index, int D_col_index);
	virtual bool isLegalMove(Board* board_ptr, int S_row_i,int S_col_i,int D_row_index, int D_col_index);
	virtual bool isKing() const;
	virtual bool isRook() const;
	virtual bool isPawn() const;
	Color getCoOrdinateColor(Board* board_ptr, int row, int col);
	char getsym(int r,int c);
	void setMoved();
	bool hasMoved()const;
};

