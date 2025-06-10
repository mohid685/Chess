#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(int row_index, int col_index, Color C, Board* board_ptr);
    virtual void draw();
    bool isLegalMove(Board* board_ptr,int S_row_i,int s_col_i,int D_row_index, int D_col_index);
    void SetClr(int tcl, int bcl);    
};