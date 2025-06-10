#include <iostream>
#include <conio.h>
#include <windows.h> 
#include "Chess.h"

using namespace std;
void displayLoadingBar() {
    Chess c;

    system("cls");
    
    c.SetClr(WHITE, BLACK);
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177;
    int bar2 = 219;

    cout << "\n\n\n\t\t\t\tLoading...";
    cout << "\n\n\n\t\t\t\t";

    for (int i = 0; i < 25; i++) {
        cout << (char)bar1;
    }

    cout << "\r";
    cout << "\t\t\t\t";

    for (int i = 0; i < 25; i++) {
        cout << (char)bar2;
        Sleep(150);
    }

    cout << "\n\t\t\t\t" << (char)1 << "!";
}
int main() {
   

    Chess C;
    C.SetClr(WHITE, BLACK);
    cout << ":'######::'##::::'##:'########::'######:::'######::\n";
    cout << "'##... ##: ##:::: ##: ##.....::'##... ##:'##... ##:\n";
    cout << " ##:::..:: ##:::: ##: ##::::::: ##:::..:: ##:::..::\n";
    cout << " ##::::::: #########: ######:::. ######::. ######::\n";
    cout << " ##::::::: ##.... ##: ##...:::::..... ##::..... ##:\n";
    cout << " ##::: ##: ##:::: ##: ##:::::::'##::: ##:'##::: ##:\n";
    cout << ". ######:: ##:::: ##: ########:. ######::. ######::\n";
    cout << ":......:::..:::::..::........:::......::::......:::\n";
    cout << "\n\n";
    cout << "*************************\n";
    cout << "*                       *\n";
    cout << "*      MADE BY:         *\n";
    cout << "*MOHID FAISAL BSCS23092 *\n";
    cout << "*                       *\n";
    cout << "*************************\n";

    Sleep(2000);
    system("CLS");
    displayLoadingBar();

    Chess G;
    G.playChess();

    return _getch();
}