#include "Rook.h"
#include "Board.h"
#include <iostream>

using namespace std;

Rook::Rook(int row_index, int col_index, Color C, Board* board_ptr)
    : Piece(row_index, col_index, C, board_ptr) {}
bool Rook::isRook() const {
    return true;
}
void Rook::SetClr(int tcl, int bcl) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void Rook::draw() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written = 0;

    if (C == WHITE) {
        SetClr(WHITE, 3);
        wchar_t whiteRook = L'\u2656';
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        WriteConsoleW(handle, &whiteRook, 1, &written, NULL);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
    }
    else {
        wchar_t blackRook = L'\u265C';
        SetClr(BLACK, 3);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        WriteConsoleW(handle, &blackRook, 1, &written, NULL);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        SetClr(WHITE, 3);
    }

    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
bool Rook::isLegalMove(Board* board_ptr,int S_row_i, int S_col_i, int D_row_index, int D_col_index) {
    
    if (((isHorizontalPath(S_row_i, S_col_i, D_row_index, D_col_index) && isHorizontalPathClear(board_ptr,S_row_i, S_col_i, D_row_index, D_col_index))
        || (isVerticalPath(S_row_i, S_col_i, D_row_index, D_col_index) && isVerticalPathClear(board_ptr,S_row_i, S_col_i, D_row_index, D_col_index)))
        && (board_ptr->get_piece_coordinates(D_row_index, D_col_index) == nullptr || board_ptr->get_piece_coordinates(D_row_index, D_col_index)->getColor() != C)) {
        return true;
    }
    else {
        return false;
    }
}