#include "Queen.h"
#include "Board.h"
#include <iostream>

using namespace std;

Queen::Queen(int row_index, int col_index, Color C, Board* board_ptr)
    : Piece(row_index, col_index, C, board_ptr) {}
void Queen::SetClr(int tcl, int bcl) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void Queen::draw()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written = 0;

    if (C == WHITE) {
        wchar_t whiteQueen = L'\u2655';
        SetClr(WHITE, 3);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        WriteConsoleW(handle, &whiteQueen, 1, &written, NULL);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
    }
    else {
        wchar_t blackQueen = L'\u265B';
        SetClr(BLACK, 3);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        WriteConsoleW(handle, &blackQueen, 1, &written, NULL);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        SetClr(WHITE, 3);
    }
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
bool Queen::isLegalMove(Board* board_ptr,int S_row_i, int S_col_i, int D_row_index, int D_col_index) {
    if((isHorizontalPath(S_row_i, S_col_i, D_row_index, D_col_index) && isHorizontalPathClear(board_ptr,S_row_i, S_col_i, D_row_index, D_col_index))
        || (isVerticalPath(S_row_i, S_col_i, D_row_index, D_col_index) && isVerticalPathClear(board_ptr,S_row_i, S_col_i, D_row_index, D_col_index))
        || (isDiagonalPath(S_row_i, S_col_i, D_row_index, D_col_index) && isDiagonalPathClear(board_ptr,S_row_i, S_col_i, D_row_index, D_col_index))
        && (board_ptr->get_piece_coordinates(D_row_index, D_col_index) == nullptr || board_ptr->get_piece_coordinates(D_row_index, D_col_index)->getColor() != C)) {
        return true;
    }
    else {
        return false;
    }
}