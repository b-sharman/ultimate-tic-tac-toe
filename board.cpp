#include <bitset>
#include <iostream>
#include <ostream>
#include <stdexcept>

#include "Board.h"
#include "constants.h"

using namespace std;

Board::Board() {
    // fill bitsets with zeros
    board.reset();
    wonBoards.reset();
}

bool Board::is_invalid_input( const int boardNum, const int squareNum ) const {
    return boardNum < 0 || boardNum > 8 || squareNum < 0 || squareNum > 8;
}

int Board::offset( const int boardNum, const int squareNum ) const {
    if( is_invalid_input( boardNum, squareNum ) ) {
        throw out_of_range( "square reference out of bounds" );
    }
    return boardNum*18+squareNum*2;
}

void Board::print() const {
    int boardNum, squareNum;
    for( int i=0; i<81; i++ ) {
        boardNum = i/27*3+i/3%3;
        squareNum = i%3+i%27/9*3;
        unsigned long boardWinner = ((wonBoards >> boardNum*2) & SQUARE_ONES_18).to_ulong();
        cout << ' ';
        if( boardWinner == BLANK ) {
            cout << INT_CHAR_MAP.at( getSquare( boardNum, squareNum ) );
        }
        else if( boardWinner == O ) {
            cout << BIG_O.at( squareNum );
        }
        else if( boardWinner == X ) {
            cout << BIG_X.at( squareNum );
        }
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
    return ((board >> offset( boardNum, squareNum )) & SQUARE_ONES_162).to_ulong();
}

void Board::setSquare( const int& boardNum, const int& squareNum, const int& value ) {
    int o = offset( boardNum, squareNum );
    // the first argument of set counts from the right, so the first digit has
    // an index 1 greater than the second
    board.set( o+1, value >> 1 );  // first digit
    board.set( o, value & 0b1 );   // second digit

    auto this_board = (board >> boardNum*18) & BOARD_ONES;
    for( const auto& wb: WIN_BITS ) {
        if( (this_board & wb) == (wb & O_WON) ) {
            wonBoards |= (O << 2*boardNum);
            break;
        }
        if( (this_board & wb) == (wb & X_WON) ) {
            wonBoards |= (X << 2*boardNum);
            break;
        }
    }
}
