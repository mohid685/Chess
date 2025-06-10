#include "Knight.h"
#include "Board.h"
#include <iostream>

using namespace std;

Knight::Knight(int row_index, int col_index, Color C, Board* board_ptr)
    : Piece(row_index, col_index, C, board_ptr) {}
void Knight::SetClr(int tcl, int bcl) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void Knight::draw() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written = 0;

    if (C == WHITE) {
        wchar_t whiteknight = L'\u2658';
        SetClr(WHITE, 3);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        WriteConsoleW(handle, &whiteknight, 1, &written, NULL);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
    }
    else {
        wchar_t blackknight = L'\u265E';
        SetClr(BLACK, 3);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        WriteConsoleW(handle, &blackknight, 1, &written, NULL);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        SetClr(WHITE, 3);
    }

    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
bool Knight::isLegalMove(Board* board_ptr,int S_row_i, int S_col_i, int D_row_index, int D_col_index) {
    int delta_row = abs(S_row_i - D_row_index);
    int delta_col = abs(S_col_i - D_col_index);

    if((delta_row == 2 && delta_col == 1) || (delta_row == 1 && delta_col == 2)
        && (board_ptr->get_piece_coordinates(D_row_index, D_col_index) == nullptr || board_ptr->get_piece_coordinates(D_row_index, D_col_index)->getColor() != C)) {
        return true;
    }
    else {
        return false;
    }      
}