#include "King.h"
#include "Board.h"
#include <iostream>

using namespace std;

King::King(int row_index, int col_index, Color C, Board* board_ptr)
    : Piece(row_index, col_index, C, board_ptr) {}
void King::SetClr(int tcl, int bcl) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
bool King::isKing() const  {
    return true;
}
void King::move(int updated_row_index, int updated_col_index) {
    this->row_index = updated_row_index;
    this->col_index = updated_col_index;

}
void King::draw() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written = 0;

    if (C == WHITE) {
        SetClr(WHITE, 3);
        wchar_t whiteKing = L'\u2654';
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        WriteConsoleW(handle, &whiteKing, 1, &written, NULL);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
    }
    else {
        wchar_t blackKing = L'\u265A';
        SetClr(BLACK, 3);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        WriteConsoleW(handle, &blackKing, 1, &written, NULL);
        WriteConsoleW(handle, L" ", 1, &written, NULL);
        SetClr(WHITE, 3);
    }

    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
bool King::isLegalMove(Board* board_ptr, int S_row_i, int S_col_i, int D_row_index, int D_col_index) {
    int delta_row = abs(S_row_i - D_row_index);
    int delta_col = abs(S_col_i - D_col_index);

    if (delta_row <= 1 && delta_col <= 1) {
        if (board_ptr->get_piece_coordinates(D_row_index, D_col_index)!= nullptr) {
            if (board_ptr->get_piece_coordinates(D_row_index, D_col_index)->getCoOrdinateColor(board_ptr, D_row_index, D_col_index) != board_ptr->get_piece_coordinates(S_row_i, S_col_i)->getCoOrdinateColor(board_ptr, S_row_i, S_col_i)) {
              
                return true;
            }
            else {
                return false;
            }
        }
        return true;
    }
    else if (delta_row == 0 && delta_col == 2) {

        if (kingStepCount > 0) {
            return false;
        }
        else {
            int rookCol = (D_col_index > S_col_i) ? 7 : 0;
            Piece* rook = board_ptr->get_piece_coordinates(S_row_i, rookCol);
            if (rook == nullptr || !rook->isRook() || rook->hasMoved()) {
                return false;
            }
            int start = min(S_col_i, D_col_index);
            int end = max(S_col_i, D_col_index);
            for (int col = start + 1; col < end; ++col) {
                if (board_ptr->get_piece_coordinates(S_row_i, col) != nullptr) {
                    return false;
                }
            }
        }
        
    }
    else {
        return false;
    }

    return true;
}