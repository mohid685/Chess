#pragma once
#include "Piece.h"
using namespace std;

//class Piece;
//class Board;

class Pawn:public Piece
{
private:
	bool isFirstMove = false;
public:
	Pawn(int row_index, int col_index,Color C, Board* board_ptr);
	virtual void draw();
	bool isLegalMove(Board* board_ptr,int S_row_i,int S_col_i,int D_row_index, int D_col_index);
	void SetClr(int tcl, int bcl);
	bool isPawn() const override;
};

