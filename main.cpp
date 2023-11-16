#include <bitset>
#include <iostream>
#include <string>

#include "board.h"
#include "constants.h"

using namespace std;

void promptNumber( const string& prompt, int* result ) {
    *result = -1;
    while( *result < 0 || *result > 8 ) {
        cout << prompt;
        cin >> *result;
    }
}

int main() {
    Board board;
    board.print();

    // board number or -1 if any board is legal
    int nextBoard {-1};
    int sn;  // square number
    int currentPlayer {X};
    while( board.getWinner() == BLANK ) {
        if( nextBoard == -1 ) {
            promptNumber(
                string("[") + INT_CHAR_MAP.at(currentPlayer) + "] Enter board number: ",
                &nextBoard
            );
        }
        promptNumber(
            string("[") + INT_CHAR_MAP.at(currentPlayer) + " on board "
                        + to_string(nextBoard) + "] Enter square number: ",
            &sn
        );
        board.setSquare( nextBoard, sn, currentPlayer );
        board.print();
        currentPlayer = NEXT_PLAYER.at(currentPlayer);

        nextBoard = board.isBoardWon( sn ) ? -1 : sn;
    }
    cout << INT_CHAR_MAP.at( board.getWinner() ) << " won!" << endl;

    return 0;
}
