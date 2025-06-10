#pragma once
#include "Piece.h"
#include <string>

class King : public Piece {
private:
    int kingStepCount = 0;
public:
    King(int row_index, int col_index, Color C, Board* board_ptr);
    virtual void draw();
    bool isLegalMove(Board* board_ptr, int S_row_i, int S_col_i, int D_row_index, int D_col_index);
    void SetClr(int tcl, int bcl);
    bool isKing() const override;
    void move(int updates_row, int updated_col);   
};