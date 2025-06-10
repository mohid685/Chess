#pragma once
#include "Utility.h"
class Piece;
class Board
{
private:
	Piece*** Pieces;
	bool highlighted_path[8][8];
public:
	Board();
	void printBoard();
	Piece* get_piece_coordinates(int r, int c);
	void set_piece_coordinates(int r, int c,Piece* p);
	void SetClr(int tcl, int bcl);
	void init_highlighted_path();
	void set_highlighted_path(Board* board_ptr, int base_row_i, int base_col_i);
};