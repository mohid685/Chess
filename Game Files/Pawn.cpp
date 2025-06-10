#include "Pawn.h"
#include "Board.h"
#include <iostream>
using namespace std;

Pawn::Pawn(int row_index, int col_index, Color C, Board* board_ptr)
	:	Piece{row_index,col_index,C,board_ptr}	{}
void Pawn::SetClr(int tcl, int bcl) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
bool Pawn::isPawn() const {
    return true;
}
void Pawn::draw() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written = 0;

    if (C == WHITE) {
        wchar_t whitePawn = L'\u2659';
        SetClr(WHITE, 3);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        WriteConsoleW(handle, &whitePawn, 1, &written, NULL);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
    }
    else {
        wchar_t blackPawn = L'\u2659';
        SetClr(BLACK, 3);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        WriteConsoleW(handle, &blackPawn, 1, &written, NULL);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        SetClr(WHITE, 3);
    }

    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
bool Pawn::isLegalMove(Board* board_ptr,int S_row_i, int S_col_i, int D_row_index, int D_col_index) {
    
    int row_diff = abs(S_row_i - D_row_index);
    int row_decline = S_row_i - D_row_index;
    if (C == BLACK) {
        if (row_decline < 0) {
            return false;
        }
    }
    else if (C == WHITE) {
        if (row_decline > 0) {
            return false;
        }
    }
    if (S_row_i == 6 || S_row_i == 1) {
        if ((row_diff == 2) || row_diff == 1) {
            isFirstMove = true;
        }
        else {
            isFirstMove = false;
        }
    }
    else {
        isFirstMove = false;
    }
    switch (isFirstMove)
    {
    case true:
        if ((S_col_i == D_col_index)) {
            return board_ptr->get_piece_coordinates(D_row_index, D_col_index) == nullptr;
        }
        else if (abs(S_col_i - D_col_index) == 1) {
            return board_ptr->get_piece_coordinates(D_row_index, D_col_index) != nullptr && board_ptr->get_piece_coordinates(D_row_index, D_col_index)->getColor() != C;
        }
        else {
            return false;
        }
    case false:
        if (S_col_i == D_col_index && C == BLACK && D_row_index == S_row_i - 1) {
            return board_ptr->get_piece_coordinates(D_row_index, D_col_index) == nullptr;
        }
        else if (S_col_i == D_col_index && C == WHITE && D_row_index == S_row_i + 1) {
            return board_ptr->get_piece_coordinates(D_row_index, D_col_index) == nullptr;
        }
        else if (abs(S_col_i - D_col_index) == 1 && C == BLACK && D_row_index == S_row_i - 1) {
            return board_ptr->get_piece_coordinates(D_row_index, D_col_index) != nullptr && board_ptr->get_piece_coordinates(D_row_index, D_col_index)->getColor() != C;
        }
        else if (abs(S_col_i - D_col_index) == 1 && C == WHITE && D_row_index == S_row_i + 1) {
            return board_ptr->get_piece_coordinates(D_row_index, D_col_index) != nullptr && board_ptr->get_piece_coordinates(D_row_index, D_col_index)->getColor() != C;
        }
    default:
        break;
    }
    return false;
}