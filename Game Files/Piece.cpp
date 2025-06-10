#include "Piece.h"
#include "Board.h"
#include "King.h"

Piece::Piece(int row_index, int col_index, Color C, Board* board_ptr) {
	this->row_index = row_index;
	this->col_index = col_index;
	this->C = C;
	this->board_ptr = board_ptr;
}
bool Piece::isKing() const {
	return false;
}
bool Piece::isRook() const {
	return false;
}
bool Piece::isPawn() const {
	return false;
}
void Piece::setMoved() {
	moved = true;
}
bool Piece::hasMoved() const {
	return moved;
}
void Piece::move(int updated_row_index, int updated_col_index) {
	this->row_index = updated_row_index;
	this->col_index = updated_col_index;
}
Color Piece::getColor() {
	return C;
}
bool Piece::isHorizontalPath(int S_row_index,int S_col_index,int D_row_index, int D_col_index) {
	return S_row_index == D_row_index;
}
bool Piece::isVerticalPath(int S_row_index, int S_col_index,int D_row_index, int D_col_index) {
	return S_col_index == D_col_index;
}
bool Piece::isDiagonalPath(int S_row_index, int S_col_index,int D_row_index, int D_col_index) {
	int delta_row = abs(S_row_index - D_row_index);
	int delta_col = abs(S_col_index - D_col_index);

	return delta_row == delta_col;
}
bool Piece::isHorizontalPathClear(Board* board_ptr,int S_row_index, int S_col_index,int D_row_index, int D_col_index) {

	if (S_row_index == D_row_index && S_col_index == D_col_index) {
		return true;
	}

	int col_incr_val;

	if (S_col_index < D_col_index) {
		col_incr_val = 1;
	}
	else {
		col_incr_val = -1;
	}

	for (int current_col = S_col_index + col_incr_val; current_col != D_col_index; current_col += col_incr_val) {

		if (board_ptr->get_piece_coordinates(S_row_index, current_col) != nullptr) {
			return false;
		}

	}
	return true;
}
bool Piece::isVerticalPathClear(Board* board_ptr, int S_row_index, int S_col_index,int D_row_index, int D_col_index) {

	if (S_row_index == D_row_index && S_col_index == D_col_index) {
		return true;
	}

	int row_incr_val;

	if (S_row_index < D_row_index) {
		row_incr_val = 1;
	}
	else {
		row_incr_val = -1;
	}

	for (int current_row = S_row_index + row_incr_val; current_row != D_row_index; current_row += row_incr_val) {

		if (board_ptr->get_piece_coordinates(current_row, S_col_index) != nullptr) {
			return false;
		}
	}
	return true;
}
bool Piece::isDiagonalPathClear(Board* board_ptr, int S_row_index, int S_col_index,int D_row_index, int D_col_index) {

	if (S_row_index == D_row_index && S_col_index == D_col_index) {
		return true;
	}

	int row_incr_val;
	if (S_row_index < D_row_index) {
		row_incr_val = 1;
	}
	else {
		row_incr_val = -1;
	}

	int col_incr_val;
	if (S_col_index < D_col_index) {
		col_incr_val = 1;
	}
	else {
		col_incr_val = -1;
	}

	for(int current_row = S_row_index + row_incr_val , current_col =S_col_index + col_incr_val;
		current_row != D_row_index; current_row += row_incr_val , current_col += col_incr_val)
	{
		if (board_ptr->get_piece_coordinates(current_row, current_col) != nullptr) {
			return false;
		}
	}
	return true;
}
bool Piece::isLegalMove(Board* board_ptr, int S_row_i,int S_col_i,int D_row_index, int D_col_index) {
	return false;
}
Color Piece::getCoOrdinateColor(Board* board_ptr, int row, int col) {

	return board_ptr->get_piece_coordinates(row, col)->getColor();

}
char Piece::getsym(int r,int c) {
	
	if (row_index == 7 && col_index == 4) {
		return 'k';
	}
	else if (row_index == 0 && col_index == 4) {
		return 'K';
	}
}