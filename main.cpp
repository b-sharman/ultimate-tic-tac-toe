#include <bitset>
#include <iostream>
#include <string>

#include "Board.h"
#include "constants.h"

using namespace std;

int main() {
    Board board;
    board.print();

    int bn, sn;  // board number, square number
    char p;  // player
    while( board.getWinner() == BLANK ) {
        cout << "Enter board number, square number, and player (X or O), separated by spaces: ";
        cin >> bn >> sn >> p;
        if( board.is_invalid_input( bn, sn ) ) {
            cout << "That is not a valid square." << endl;
        }
        else if( !CHAR_INT_MAP.count( p ) ) {
            cout << "That is not a valid player." << endl;
        }
        else {
            board.setSquare( bn, sn, CHAR_INT_MAP.at( p ) );
            board.print();
        }
    }
    cout << INT_CHAR_MAP.at( board.getWinner() ) << " won!" << endl;

    return 0;
}
