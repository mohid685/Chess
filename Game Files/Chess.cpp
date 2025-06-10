#include "Chess.h"
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "King.h"
#include <iostream>
#include<string>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

Chess::Chess() {
	no_players[0] = new Player("BLACK", BLACK);
	no_players[1] = new Player("WHITE", WHITE);

	board_ptr = new Board();

	//srand(time(0));
	turn = 1;
}
#define YELLOW 14
#define WHITE 15
#define BLACK 0
#define GRAY 8
void Chess::playChessSound()
{
	PlaySound(L"chessPiece.wav", NULL, SND_FILENAME | SND_ASYNC);	
}
void Chess::SetClr(int tcl, int bcl) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void Chess::print_turn_msg(Player* first_player) {

	SetClr(BLACK, WHITE);
	cout << "\n" << first_player->getName() << "'s Turn \n";
	SetClr(WHITE, BLACK);
}
void Chess::getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void Chess::gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void Chess::rangeFixer(int& x, int& y)
{
	int Sr = x, Sc = y;
	if (Sr <= 5)
		Sr = 0;
	else if (Sr <= 7)
		Sr = 1;
	else if (Sr <= 9)
		Sr = 2;
	else if (Sr <= 11)
		Sr = 3;
	else if (Sr <= 13)
		Sr = 4;
	else if (Sr <= 15)
		Sr = 5;
	else if (Sr <= 17)
		Sr = 6;
	else if (Sr <= 19)
		Sr = 7;
	x = Sr;
	if (Sc <= 4)
		Sc = 0;
	else if (Sc <= 9)
		Sc = 1;
	else if (Sc <= 13)
		Sc = 2;
	else if (Sc <= 17)
		Sc = 3;
	else if (Sc <= 21)
		Sc = 4;
	else if (Sc <= 25)
		Sc = 5;
	else if (Sc <= 29)
		Sc = 6;
	else if (Sc <= 33)
		Sc = 7;
	y = Sc;
}
void Chess::selectPiece() {
	do {
		getRowColbyLeftClick(base_row_i, base_col_i);
		rangeFixer(base_row_i, base_col_i);

		Piece* p = board_ptr->get_piece_coordinates(base_row_i, base_col_i);
		if (p != nullptr && p->getColor() == no_players[turn]->getColor()) {
			board_ptr->set_highlighted_path(board_ptr, base_row_i, base_col_i);
			break;
		}
		else {
			SetClr(WHITE, BLACK);
			cout << "\nSelect a valid piece of your color.\n";
			board_ptr->init_highlighted_path();
		}
	} while (true);
}
void Chess::selectDestination() {

	getRowColbyLeftClick(destination_row_i, destination_col_i);
	rangeFixer(destination_row_i, destination_col_i);
	board_ptr->init_highlighted_path();

	if (destination_row_i == 10 && destination_col_i == 45) {
	}
}
bool Chess::validBaseCoordinates(Player* first_player, int row_i, int col_i) {

	if (row_i < 0 || row_i >= 8 || col_i < 0 || col_i >= 8) {
		SetClr(WHITE, BLACK);
		cout << "\nEnter Valid Co Ordinates!!!\n";
		return false;
	}
	Piece* p = board_ptr->get_piece_coordinates(row_i, col_i);

	if (p != nullptr && p->getColor() == first_player->getColor()) {
		return true;
	}
}
bool Chess::validDestCoordinates(Player* first_player, int row_i, int col_i) {

	if (row_i < 0 || row_i >= 8 || col_i < 0 || col_i >= 8) {
		SetClr(WHITE, BLACK);
		cout << "\nEnter Valid Co Ordinates!!!\n";
		return false;
	}
	Piece* p = board_ptr->get_piece_coordinates(row_i, col_i);


	if (p == nullptr || p->getColor() != first_player->getColor()) {
		return true;
	}

	return false;
}
void Chess::Move(int base_row_i, int base_col_i, int destination_row_i, int destination_col_i) {

	history.push_back({ base_row_i, base_col_i, destination_row_i, destination_col_i, board_ptr->get_piece_coordinates(base_row_i, base_col_i), board_ptr->get_piece_coordinates(destination_row_i, destination_col_i) });

	Piece* killed_piece = board_ptr->get_piece_coordinates(destination_row_i, destination_col_i);
	Piece* moved_piece = board_ptr->get_piece_coordinates(base_row_i, base_col_i);
	moved_piece->setMoved();

	if (killed_piece != nullptr && killed_piece->isKing()) {
		cout << "You cannot capture the king!";
		return;
	}
	playChessSound();

	if (killed_piece != nullptr) {
		SetClr(WHITE, BLACK);
		cout << "\n\n\t\t " << no_players[turn]->getName() << " has killed ";

		if (killed_piece->getColor() == BLACK) {
			cout << "BLACKS's";
		}
		else {
			cout << "WHITE's ";
		}
		cout << " piece at (" << destination_row_i << ", " << destination_col_i << ")" << endl;

		playChessSound();
		Sleep(2000);
		SetClr(WHITE, BLACK);
	}
	board_ptr->set_piece_coordinates(destination_row_i, destination_col_i, nullptr);
	Piece* p = board_ptr->get_piece_coordinates(base_row_i, base_col_i);
	board_ptr->set_piece_coordinates(destination_row_i, destination_col_i, p);
	board_ptr->set_piece_coordinates(base_row_i, base_col_i, nullptr);
}
void Chess::replay() const {
	
	Chess C;

	Board replay_board;
	
	for (const MOVE_& move : history) {
		
		replay_board.set_piece_coordinates(move.destination_row_i, move.destination_col_i, move.moved_piece);
		replay_board.set_piece_coordinates(move.base_row_i, move.base_col_i, nullptr);

		
		replay_board.printBoard();

		C.SetClr(WHITE, BLACK);
		cout << "\n\nINSTANT REPLAY!!!\n\n";
		
		Sleep(1000); 
	}
}
void Chess::undoLastMove() {
	if (history.empty()) {
		SetClr(BLACK, WHITE);
		cout << "No moves to undo!" << std::endl;
		return;
	}
	MOVE_ last_move = history.back();
	history.pop_back();

	board_ptr->set_piece_coordinates(last_move.base_row_i, last_move.base_col_i, last_move.moved_piece);

	if (last_move.killed_piece != nullptr) {
		board_ptr->set_piece_coordinates(last_move.destination_row_i, last_move.destination_col_i, last_move.killed_piece);
	}
	else {
		board_ptr->set_piece_coordinates(last_move.destination_row_i, last_move.destination_col_i, nullptr);
	}
	playChessSound();

	turnChange(turn);
}
void Chess::turnChange(int& turn) {

	if (turn == 0) {
		turn = 1;
	}
	else if (turn == 1) {
		turn = 0;
	}

}
void Chess::findKing(Board* board_ptr, int turn, int& kr, int& kc) {
	bool found = false;
	//turnChange(turn);
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece* piece = board_ptr->get_piece_coordinates(r, c);
			if (turn == 0) {
				if ((piece != nullptr) && (piece->getColor() == BLACK) && (piece->isKing())) {
					kr = r;
					kc = c;

					found = true;
					break;
				}
			}
			else if (turn == 1) {
				if ((piece != nullptr) && (piece->getColor() == WHITE) && (piece->isKing())) {
					kr = r;
					kc = c;

					found = true;
					break;
				}
			}
		}
		if (found == true) {
			return;
		}

	}
}
void Chess::findRook(Board* board_ptr, int turn, int& rr, int& rc) {

	bool found = false;

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece* piece = board_ptr->get_piece_coordinates(r, c);
			if (turn == 0) {
				if ((piece != nullptr) && (piece->getColor() == BLACK) && (piece->isRook())) {
					rr = r;
					rc = c;

					found = true;
					break;
				}
			}
			else if (turn == 1) {
				if ((piece != nullptr) && (piece->getColor() == WHITE) && (piece->isRook())) {
					rr = r;
					rr = r;
					rc = c;

					found = true;
					break;
				}
			}
		}
		if (found == true) {
			return;
		}
	}
}
bool Chess::isCheck(Board* board_ptr, int _turn) {

	int kr, kc;
	turnChange(_turn);
	findKing(board_ptr, _turn, kr, kc);
	turnChange(_turn);

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {

			if (board_ptr->get_piece_coordinates(r, c) != nullptr && (board_ptr->get_piece_coordinates(r, c)->isLegalMove(board_ptr, r, c, kr, kc)
				&& board_ptr->get_piece_coordinates(r, c)->getCoOrdinateColor(board_ptr, r, c) != board_ptr->get_piece_coordinates(kr, kc)->getCoOrdinateColor(board_ptr, kr, kc)))
			{
				return true;
			}
		}
	}
	return false;
}
bool Chess::selfCheck(Board* board_ptr, int turn, int base_row_i, int base_col_i, int destination_row_i, int destination_col_i) {

	bool iswin = false;

	Piece* movingPiece = board_ptr->get_piece_coordinates(base_row_i, base_col_i);
	Piece* capturedPiece = board_ptr->get_piece_coordinates(destination_row_i, destination_col_i);

	board_ptr->set_piece_coordinates(destination_row_i, destination_col_i, movingPiece);
	board_ptr->set_piece_coordinates(base_row_i, base_col_i, nullptr);
	board_ptr->printBoard();

	turnChange(turn);
	bool selfCheck = isCheck(board_ptr, turn);
	turnChange(turn);

	board_ptr->set_piece_coordinates(base_row_i, base_col_i, movingPiece);
	if (capturedPiece != nullptr) {
		board_ptr->set_piece_coordinates(destination_row_i, destination_col_i, capturedPiece);
	}
	else {
		board_ptr->set_piece_coordinates(destination_row_i, destination_col_i, nullptr);
	}

	return selfCheck;
}
bool Chess::isCheckMate(Board* board_ptr, int turn) {
	if (!isCheck(board_ptr, turn)) {
		return false;
	}
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece* piece = board_ptr->get_piece_coordinates(r, c);
			if (piece != nullptr && piece->getColor() == turn) {
				for (int r_dest = 0; r_dest < 8; r_dest++) {
					for (int c_dest = 0; c_dest < 8; c_dest++) {
						if (piece->isLegalMove(board_ptr, r, c, r_dest, c_dest)) {
							if (!selfCheck(board_ptr, turn, r, c, r_dest, c_dest)) {
								return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}
bool Chess::isStalemate(Board* board_ptr, int turn) {
	if (isCheck(board_ptr, turn)) {
		return false;
	}
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece* piece = board_ptr->get_piece_coordinates(r, c);
			if (piece != nullptr && piece->getColor() == turn) {
				for (int r_dest = 0; r_dest < 8; r_dest++) {
					for (int c_dest = 0; c_dest < 8; c_dest++) {
						if (piece->isLegalMove(board_ptr, r, c, r_dest, c_dest)) {
							if (!selfCheck(board_ptr, turn, r, c, r_dest, c_dest)) {
								return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}
bool Chess::canCastle(Board* board_ptr, int turn, bool kingSide) {

	int kingRow;
	if (turn == 0) {
		kingRow = 0;
	}
	else {
		kingRow = 7;
	}
	int kingCol = 4;
	Piece* king = board_ptr->get_piece_coordinates(kingRow, kingCol);

	if (king == nullptr) {
		return false;
	}
	else if (king->hasMoved()) {
		return false;
	}

	int rookCol;
	if (kingSide) {
		rookCol = 7;
	}
	else {
		rookCol = 0;
	}
	Piece* rook = board_ptr->get_piece_coordinates(kingRow, rookCol);


	if (rook == nullptr) {
		return false;
	}
	else if (rook->hasMoved()) {
		return false;
	}

	int start;
	int end;
	if (kingCol < rookCol) {
		start = kingCol;
		end = rookCol;
	}
	else {
		start = rookCol;
		end = kingCol;
	}
	for (int col = start + 1; col < end; ++col) {
		if (board_ptr->get_piece_coordinates(kingRow, col) != nullptr) {
			return false;
		}
	}

	return true;
}
void Chess::saveToFile(const std::string& filename) const {
	ofstream file(filename);
	if (!file) {
		cout << "Unable to open file " << filename << endl;
		return;
	}
	file << turn << endl;

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece* piece = board_ptr->get_piece_coordinates(r, c);
			if (piece != nullptr) {
				file << typeid(*piece).name() << " "
					<< piece->getColor() << " "
					<< r << " " << c << endl;
			}
		}
	}

	file.close();
}
void Chess::restartGame(const string& filename) {
	ifstream file(filename);
	if (!file) {
		cout << "Unable to open file " << filename << endl;
		return;
	}

	
	file >> turn;

	
	delete board_ptr;
	board_ptr = new Board();

	
	string pieceType;
	int color, r, c;
	while (file >> pieceType >> color >> r >> c) {
		
		Piece* piece = nullptr;
		if (pieceType == "P") {
			piece = new Pawn(r, c, static_cast<Color>(color), board_ptr);
		}
		else if (pieceType == "R") {
			piece = new Rook(r, c, static_cast<Color>(color), board_ptr);
		} 
		else if (pieceType == "Q") {
			piece = new Queen(r, c, static_cast<Color>(color), board_ptr);
		}
		else if (pieceType == "K") {
			piece = new King(r, c, static_cast<Color>(color), board_ptr);
		}
		else if (pieceType == "N") {
			piece = new Knight(r, c, static_cast<Color>(color), board_ptr);
		}
		else if (pieceType == "B") {
			piece = new Bishop(r, c, static_cast<Color>(color), board_ptr);
		}

		
		board_ptr->set_piece_coordinates(r, c, piece);
	}

	file.close();
}
void Chess::playChess() {
	while (true) {
		board_ptr->printBoard();
		print_turn_msg(no_players[turn]);

		
		gotoRowCol(25, 0);
		SetClr(BLACK, WHITE);
		cout << "-UNDO-";
		gotoRowCol(27, 0);
		cout << "-SAVE-";
		gotoRowCol(29, 0);
		cout << "-RESTART-";
		

		
		int click_r = 25, click_c = 0;
		getRowColbyLeftClick(click_r, click_c);
		if (click_r == 25 && click_c >= 0 && click_c <= 4) {
			undoLastMove();
			board_ptr->printBoard();
			continue;
		}
		else if (click_r == 27 && click_c >= 0 && click_c <= 4) {
			
			saveToFile("chess.txt");
			continue;
		}
		else if (click_r == 29 && click_c >= 0 && click_c <= 4) {
			
			restartGame("chess.txt");
			board_ptr->printBoard();
			continue;
		}

		do {
			do {
				SetClr(WHITE, BLACK);
				cout << "\nSelect Piece(row_index,col_index) ";

				selectPiece();
				board_ptr->get_piece_coordinates(base_row_i, base_col_i);

				if (board_ptr->get_piece_coordinates(base_row_i, base_col_i) != nullptr && board_ptr->get_piece_coordinates(base_row_i, base_col_i)->getColor() == no_players[turn]->getColor()) {
					board_ptr->set_highlighted_path(board_ptr, base_row_i, base_col_i);
					board_ptr->printBoard();
				}

			} while (!validBaseCoordinates(no_players[turn], base_row_i, base_col_i));

			cout << "\nSelect Destination(row_index,col_index)";
			selectDestination();

			SetClr(WHITE, BLACK);
		} while (!validDestCoordinates(no_players[turn], destination_row_i, destination_col_i)
			|| !board_ptr->get_piece_coordinates(base_row_i, base_col_i)->isLegalMove(board_ptr, base_row_i, base_col_i, destination_row_i, destination_col_i));

		if (selfCheck(board_ptr, turn, base_row_i, base_col_i, destination_row_i, destination_col_i)) {
			SetClr(WHITE, BLACK);
			cout << "\nSelf-Check!!\n";
			Sleep(2000);
			continue;
		}

		Move(base_row_i, base_col_i, destination_row_i, destination_col_i);

		Piece* movedPiece = board_ptr->get_piece_coordinates(destination_row_i, destination_col_i);
		if (movedPiece->isPawn() && (destination_row_i == 0 || destination_row_i == 7)) {
			char choice;
			cout << "Pawn promotion! Choose a piece to promote to (Q/R/B/N): ";
			cin >> choice;
			board_ptr->set_piece_coordinates(destination_row_i, destination_col_i, nullptr);

			switch (toupper(choice)) {
			case 'Q':
				board_ptr->set_piece_coordinates(destination_row_i, destination_col_i, new Queen(destination_row_i, destination_col_i, movedPiece->getColor(), board_ptr));
				break;
			case 'R':
				board_ptr->set_piece_coordinates(destination_row_i, destination_col_i, new Rook(destination_row_i, destination_col_i, movedPiece->getColor(), board_ptr));
				break;
			case 'B':
				board_ptr->set_piece_coordinates(destination_row_i, destination_col_i, new Bishop(destination_row_i, destination_col_i, movedPiece->getColor(), board_ptr));
				break;
			case 'N':
				board_ptr->set_piece_coordinates(destination_row_i, destination_col_i, new Knight(destination_row_i, destination_col_i, movedPiece->getColor(), board_ptr));
				break;
			default:
				cout << "Invalid choice. Promoting to Queen by default.";
				board_ptr->set_piece_coordinates(destination_row_i, destination_col_i, new Queen(destination_row_i, destination_col_i, movedPiece->getColor(), board_ptr));
				break;
			}
		}

		board_ptr->init_highlighted_path();

		SetClr(WHITE, BLACK);
		if (isCheckMate(board_ptr, turn)) {
			cout << "\nCheckmate\n";
			Sleep(2000);
			replay();
			break;
		}
		else if (isCheck(board_ptr, turn)) {
			SetClr(WHITE, BLACK);
			cout << "\nCheck!\n";
			Sleep(2000);
		}
		turnChange(turn);
	}
	SetClr(WHITE, BLACK);
	if (no_players[turn]->getName() == "Mohid") {
		cout << "\nBLACK Wins!!\n";
	}
	else {
		SetClr(WHITE, BLACK);
		cout << "\WHITE Wins!!\n";
	}
	SetClr(WHITE, BLACK);
	Sleep(2000);
}