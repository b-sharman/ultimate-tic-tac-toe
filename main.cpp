#include <bitset>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Board.h"
#include "constants.h"
#include "outOfBounds.h"

using namespace std;

/* @brief prompts user for an integer with custom bounds checking
 *
 * if boundsChecker returns true, the user's input will not be accepted.
 */
template<typename F>
void promptNumber( const string& prompt, int* result, const F& boundsChecker ) {
    *result = -1;
    string input;
    while( boundsChecker() ) {
        cout << prompt;
        cin >> input;
        try { *result = stoi( input ); }
        catch( const invalid_argument& ) {}
        catch( const out_of_range& ) {}
    }
}

void promptBoardNumber( const string& prompt, int* result, const Board& board ) {
    promptNumber(
        prompt,
        result,
        [result, board]() {
            return outOfBounds( *result ) || board.isBoardWon( *result );
        }
    );
}

void promptSquareNumber( const string& prompt, int* result, const int& boardNum, const Board& board ) {
    promptNumber(
        prompt,
        result,
        [result, board, boardNum]() {
            return outOfBounds( *result ) || board.getSquare( boardNum, *result );
        }
    );
}

int main(int argc, char* argv[]) {
    ifstream fileReader;
    ofstream fileWriter;
    if (argc < 2) {
        cout << "A record of this game will be written to 'game.txt'.\n"
             << "To replay a previous game, put its filename as a command line argument." << endl;
        fileWriter.open("game.txt");
    } else {
        cout << "Reading from " << argv[1] << endl;
        fileReader.open(argv[1]);
    }

    Board board;
    board.print();

    // board number or -1 if any board is legal
    int nextBoard {-1};
    int sn;  // square number
    int currentPlayer {X};
    while( board.getWinner() == BLANK ) {
        if (argc < 2) {
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
            fileWriter << currentPlayer << ' ' << nextBoard << ' ' << sn << '\n';
        }
        else {
            // TODO: throw an error if game.txt is empty
            fileReader >> currentPlayer >> nextBoard >> sn;
            cout << endl << INT_CHAR_MAP.at(currentPlayer) << " goes on board " << nextBoard << ", square " << sn << endl;
        }

        board.setSquare( nextBoard, sn, currentPlayer );
        board.print();

        if (argc < 2) {
            currentPlayer = NEXT_PLAYER.at(currentPlayer);
            nextBoard = board.isBoardWon( sn ) ? -1 : sn;
        }
    }
    cout << INT_CHAR_MAP.at( board.getWinner() ) << " won!" << endl;

    fileWriter.close();

    return 0;
}
