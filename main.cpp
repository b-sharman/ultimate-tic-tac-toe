#include <bitset>
#include <iostream>
#include <string>

#include "Board.h"
#include "constants.h"

using namespace std;

int main() {
    Board board;
    board.print();

    int bn, sn;
    char v;
    while( true ) {
        cout << "Enter board number, square number, and player (X or O), separated by spaces: ";
        cin>>bn>>sn >> v;
        if( board.is_invalid_input( bn, sn ) ) {
            cout << "That is not a valid square." << endl;
        }
        else if( !CHAR_INT_MAP.count(v) ) {
            cout << "That is not a valid player." << endl;
        }
        else {
            board.setSquare( bn, sn, CHAR_INT_MAP.at(v) );
            board.print();
        }
    }

    return 0;
}
