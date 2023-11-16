#include <bitset>
#include <iostream>
#include <ostream>
#include <stdexcept>

#include "Board.h"
#include "constants.h"

using namespace std;

Board::Board() {
    winner = BLANK;
    // fill bitsets with zeros
    board.reset();
    wonBoards.reset();
}

int Board::offset( const int boardNum, const int squareNum ) const {
    return boardNum*18+squareNum*2;
}

void Board::print() const {
    int boardNum, squareNum;
    for( int i=0; i<81; i++ ) {
        boardNum = i/27*3+i/3%3;
        squareNum = i%3+i%27/9*3;
        unsigned long boardWinner = ((wonBoards >> boardNum*2) & SQUARE_ONES).to_ulong();
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

bool Board::isBoardWon( const int& boardNum ) const {
    return checkWon( (board >> boardNum*18) & BOARD_ONES );
}

unsigned long Board::getSquare( const int& boardNum, const int& squareNum ) const {
    // shift the board so that the desired square is at the rightmost two bits,
    // then bitwise AND with 11 to remove any other bits, then convert to
    // unsigned long
    return ((board >> offset( boardNum, squareNum )) & SQUARE_ONES).to_ulong();
}

unsigned long Board::getWinner() const {
    return winner;
}

void Board::setSquare( const int& boardNum, const int& squareNum, const int& value ) {
    int o = offset( boardNum, squareNum );
    // the first argument of set counts from the right, so the first digit has
    // an index 1 greater than the second
    board.set( o+1, value >> 1 );  // first digit
    board.set( o, value & 0b1 );   // second digit

    switch( checkWon( (board >> boardNum*18) & BOARD_ONES ) ) {
        case O:
            wonBoards |= (O << 2*boardNum);
            break;
        case X:
            wonBoards |= (X << 2*boardNum);
            break;
    }

    winner = checkWon( wonBoards );
}

// private member functions

unsigned long Board::checkWon( const std::bitset<162>& board ) const {
    for( const auto& wb: WIN_BITS ) {
        if( (board & wb) == (wb & O_WON) ) return O;
        if( (board & wb) == (wb & X_WON) ) return X;
    }
    return BLANK;
}
