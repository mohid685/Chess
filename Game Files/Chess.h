#pragma once
#include "Board.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

class Board;
class Player;
class Piece;

struct MOVE_ {
	int base_row_i, base_col_i;
	int destination_row_i, destination_col_i;
	Piece* moved_piece;
	Piece* killed_piece;
};


class Chess
{
private:
	vector<MOVE_> history;
	MOVE_ last_move;
	int base_row_i;
	int base_col_i;
	int turn=0;
	int destination_row_i;
	int destination_col_i;
	int kingStepCount = 0;
	Player* no_players[2];
	Board* board_ptr;
	int last_base_row_i, last_base_col_i, last_destination_row_i, last_destination_col_i;
	Piece* last_captured_piece = nullptr;
	
public:
	Chess();
	void playChess();
	void print_turn_msg(Player* first_player);
	void selectPiece();
	void selectDestination();
	bool validBaseCoordinates(Player* first_player, int row_i, int col_i);
	bool validDestCoordinates(Player* first_player, int row_i, int col_i);
	void turnChange(int &turn);
	void Move(int base_row_i, int base_col_i, int destination_row_i, int destination_col_i);
	void getRowColbyLeftClick(int& rpos, int& cpos);
	void gotoRowCol(int rpos, int cpos);
	void playChessSound();
	void SetClr(int tcl, int bcl);
	void rangeFixer(int& x, int& y);
	bool isCheck(Board* board_ptr, int turn);
	void findKing(Board* board_ptr,int turn,int &kr,int &kc);
	void findRook(Board* board_ptr, int turn, int& rr, int& rc);
	bool selfCheck(Board *board_ptr,int turn, int base_row_i, int base_col_i, int destination_row_i, int destination_col_i);
	bool isCheckMate(Board* board_ptr,int turn);
	bool isStalemate(Board* board_ptr, int turn);
	bool canCastle(Board* board_ptr, int turn, bool kingSide);
	void undoLastMove();
	void saveToFile(const std::string& filename) const;
	void restartGame(const std::string& filename);
	void replay() const;
};

