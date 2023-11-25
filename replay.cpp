#include <bitset>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Board.h"
#include "constants.h"

using namespace std;

int main() {
    // load file for reading
    ifstream fileReader ("game.txt");

    Board board;
    board.print();

    // board number or -1 if any board is legal
    int nextBoard {-1};
    int sn;  // square number
    int currentPlayer {X};
    while( board.getWinner() == BLANK ) {
        fileReader >> currentPlayer >> nextBoard >> sn;
        cout << endl << INT_CHAR_MAP.at(currentPlayer) << " goes on board " << nextBoard << ", square " << sn << endl;
        board.setSquare( nextBoard, sn, currentPlayer );
        board.print();
    }
    cout << INT_CHAR_MAP.at( board.getWinner() ) << " won!" << endl;

    fileReader.close();

    return 0;
}
