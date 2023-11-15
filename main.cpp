#include <bitset>
#include <iostream>
#include <string>

#include "board.h"
#include "constants.h"

using namespace std;

int main() {
    Board board;
    board.print();

    int bn, sn;  // board number, square number
    int currentPlayer {X};
    while( board.getWinner() == BLANK ) {
        cout << '[' << INT_CHAR_MAP.at(currentPlayer)
            << "] Enter board number and square number, separated by spaces: ";
        cin >> bn >> sn;
        if( board.is_invalid_input( bn, sn ) ) {
            cout << "That is not a valid square." << endl;
        }
        else {
            board.setSquare( bn, sn, currentPlayer );
            board.print();
            currentPlayer = NEXT_PLAYER.at(currentPlayer);
        }
    }
    cout << INT_CHAR_MAP.at( board.getWinner() ) << " won!" << endl;

    return 0;
}
