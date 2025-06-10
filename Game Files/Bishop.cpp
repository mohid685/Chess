#include "Bishop.h"
#include "Board.h"
#include <iostream>

using namespace std;

Bishop::Bishop(int row_index, int col_index, Color C, Board* board_ptr)
    : Piece(row_index, col_index, C, board_ptr) {}
void Bishop::SetClr(int tcl, int bcl) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void Bishop::draw() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written = 0;

    if (C == WHITE) {
        wchar_t whiteBishop = L'\u2657';
        SetClr(WHITE, 3);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        WriteConsoleW(handle, &whiteBishop, 1, &written, NULL);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
    }
    else {
        wchar_t blackBishop = L'\u265D';
        SetClr(BLACK, 3);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        WriteConsoleW(handle, &blackBishop, 1, &written, NULL);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        SetClr(WHITE, 3);
    }

    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
bool Bishop::isLegalMove(Board* board_ptr, int S_row_i, int S_col_i, int D_row_index, int D_col_index) {
    if(isDiagonalPath(S_row_i, S_col_i, D_row_index, D_col_index)
        && isDiagonalPathClear(board_ptr, S_row_i, S_col_i, D_row_index, D_col_index)
        && (board_ptr->get_piece_coordinates(D_row_index,D_col_index)==nullptr || board_ptr->get_piece_coordinates(D_row_index,D_col_index)->getColor()!= C)) {
        return true;
    }
    else {
        return false;
    }
}