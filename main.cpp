#include <bitset>
#include <iostream>
#include <string>

#include "Board.h"
#include "constants.h"
#include "outOfBounds.h"

using namespace std;

void promptBoardNumber( const string& prompt, int* result, const Board& board ) {
    *result = -1;
    while( outOfBounds( *result ) || board.isBoardWon( *result ) ) {
        cout << prompt;
        cin >> *result;
    }
}

void promptSquareNumber( const string& prompt, int* result, const int& boardNum, const Board& board ) {
    *result = -1;
    while( outOfBounds( *result ) || board.getSquare( boardNum, *result ) ) {
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
            promptBoardNumber(
                string("[") + INT_CHAR_MAP.at(currentPlayer) + "] Enter board number: ",
                &nextBoard,
                board
            );
        }
        promptSquareNumber(
            string("[") + INT_CHAR_MAP.at(currentPlayer) + " on board "
                        + to_string(nextBoard) + "] Enter square number: ",
            &sn,
            nextBoard,
            board
        );
        board.setSquare( nextBoard, sn, currentPlayer );
        board.print();
        currentPlayer = NEXT_PLAYER.at(currentPlayer);

        nextBoard = board.isBoardWon( sn ) ? -1 : sn;
    }
    cout << INT_CHAR_MAP.at( board.getWinner() ) << " won!" << endl;

    return 0;
}
