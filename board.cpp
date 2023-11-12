#include <bitset>
#include <iostream>
#include <ostream>
#include <stdexcept>

#include "Board.h"
#include "constants.h"

using namespace std;

bool Board::is_invalid_input( const int boardNum, const int squareNum ) const {
    return boardNum < 0 || boardNum > 8 || squareNum < 0 || squareNum > 8;
}

int Board::offset( const int boardNum, const int squareNum ) const {
    if( is_invalid_input( boardNum, squareNum ) ) {
        throw out_of_range( "square reference out of bounds" );
    }
    return 160 - boardNum*18+squareNum*2;
}

void Board::print() const {
    for( int i=0; i<81; i++ ) {
        cout << ' ' << INT_CHAR_MAP.at(
            getSquare(
                i/27*3+i/3%3, // board number
                i%3+i%27/9*3  // square number
            )
        );
        if( i%9==2 || i%9 == 5 ) cout << " |";
        if( i%9==8 ) cout << '\n';
        if( i==26 || i==53 ) cout << "-----------------------\n";
    }
    cout << flush;
}

unsigned long Board::getSquare( const int& boardNum, const int& squareNum ) const {
    // shift the board so that the desired square is at the rightmost two bits,
    // then bitwise AND with 11 to remove any other bits, then convert to
    // unsigned long
    return ((board >> offset( boardNum, squareNum )) & THREE).to_ulong();
}

void Board::setSquare( const int& boardNum, const int& squareNum, const int& value ) {
    int o = offset( boardNum, squareNum );
    // the first argument of set counts from the right, so the first digit has
    // an index 1 greater than the second
    board.set( o+1, value >> 1 );  // first digit
    board.set( o, value & 0b1 );   // second digit
}
