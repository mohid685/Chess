#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Chess.h"

#include <iostream>
using namespace std;

Board::Board() {
    Pieces = new Piece * *[8];

    for (int r = 0; r < 8; r++) {
        Pieces[r] = new Piece * [8];

        for (int c = 0; c < 8; c++) {
            if (r == 1) {
                Pieces[r][c] = new Pawn(r, c, WHITE, this);
            }
            else if (r == 6) {
                Pieces[r][c] = new Pawn(r, c, BLACK, this);
            }
            else if (r == 0) {
                if (c == 0 || c == 7) {
                    Pieces[r][c] = new Rook(r, c, WHITE, this);
                }
                else if (c == 1 || c == 6) {
                    Pieces[r][c] = new Knight(r, c, WHITE, this);
                }
                else if (c == 2 || c == 5) {
                    Pieces[r][c] = new Bishop(r, c, WHITE, this);
                }
                else if (c == 3) {
                    Pieces[r][c] = new Queen(r, c, WHITE, this);
                }
                else if (c == 4) {
                    Pieces[r][c] = new King(r, c, WHITE, this);
                }
            }
            else if (r == 7) {
                if (c == 0 || c == 7) {
                    Pieces[r][c] = new Rook(r, c, BLACK, this);
                }
                else if (c == 1 || c == 6) {
                    Pieces[r][c] = new Knight(r, c, BLACK, this);
                }
                else if (c == 2 || c == 5) {
                    Pieces[r][c] = new Bishop(r, c, BLACK, this);
                }
                else if (c == 3) {
                    Pieces[r][c] = new Queen(r, c, BLACK, this);
                }
                else if (c == 4) {
                    Pieces[r][c] = new King(r, c, BLACK, this);
                }
            }
            else {
                Pieces[r][c] = nullptr;
            }
        }
    }
}
Piece* Board::get_piece_coordinates(int r, int c) {
    return Pieces[r][c];
}
void Board::set_piece_coordinates(int r, int c, Piece* p) {
    if (r < 0 || r >= 8 || c < 0 || c >= 8) {
        SetClr(WHITE, BLACK);
        cout << "Invalid coordinates. Please enter values between 0 and 7." << endl;
        return;
    }
    SetClr(WHITE, BLACK);
    if (p != nullptr && Pieces[r][c] != nullptr) {
        return;
    }
    Pieces[r][c] = p;
}

#define YELLOW 14
#define WHITE 15
#define BLACK 0
#define GRAY 8
#define PINK 13
#define ORANGE 12
#define GREEN 10
#define BLUE 9
#define PURPLE 5

void Board::SetClr(int tcl, int bcl) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void Board::init_highlighted_path() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            highlighted_path[r][c] = false;
        }
    }
}
void Board::set_highlighted_path(Board* board_ptr, int base_row_i, int base_col_i) {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            highlighted_path[r][c] = board_ptr->get_piece_coordinates(base_row_i, base_col_i)->isLegalMove(board_ptr, base_row_i, base_col_i, r, c);
        }
    }
}
void Board::printBoard() {
    system("cls");
    SetClr(BLACK, BLACK);
    cout << "\t     CHESS\n";
    cout << "----------------------------------\n";
    cout << "  Current Status Of The Board: " << endl;
    cout << "----------------------------------\n";
    SetClr(WHITE, BLACK);

    SetClr(BLACK, BLACK);
    cout << "+---+---+---+---+---+---+---+---+" << endl;
    SetClr(WHITE, BLACK);

    for (int r = 0; r < 8; r++) {
        SetClr(BLACK, BLACK);
        cout << "|";
        SetClr(WHITE, BLACK);

        for (int c = 0; c < 8; c++) {
            if (highlighted_path[r][c]) {
                SetClr(BLACK, PURPLE);  
            }
            if (Pieces[r][c] == nullptr) {
                cout << "   ";
            }
            else {
                Pieces[r][c]->draw();
            }

            SetClr(BLACK, BLACK);
            cout << "|";
            SetClr(WHITE, BLACK);
        }

        cout << endl;
        SetClr(BLACK, BLACK);
        cout << "+---+---+---+---+---+---+---+---+" << endl;
        SetClr(WHITE, BLACK);
    }
}