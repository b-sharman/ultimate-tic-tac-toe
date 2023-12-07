#ifndef BOARD
#define BOARD

class Board {
public:
    Board();

    /* @brief return the index of the rightmost bit of a certain square
     *
     * boardNum and squareNum, each of which must be in the interval [0, 8],
     * inclusive, specify which board number and square number, respectively,
     * to access. Each are numbered in row-major order. This function silently
     * fails if the indices are not in that range.
     *
     * The offset is from the right, not the left, for convenience with
     * bitset.set() and bitset.test().
     */
    int offset( const int, const int ) const;

    /* @brief print the board with std::cout */
    void print() const;

    /* @brief return if a certain board [0-8] has been won
     *
     * returns true if the board number is outside the interval [0, 8]
     */
    bool isBoardWon( const int& ) const;

    /* @brief return the value of any square on the board
     *
     * returns true if either argument is outside the interval [0, 8]
     */
    unsigned long getSquare( const int&, const int& ) const;

    /* @brief getter for winner private variable */
    unsigned long getWinner() const;

    /* @brief set the value of any square on the board */
    void setSquare( const int&, const int&, const int& );

private:
    // 9*9 = 81 squares, 81 * 2 bits per square = 162 bits
    std::bitset<162> board;
    // the winner of each board, or BLANK if no one has won
    // only the first 18 bits are used, but it must be size 162 for checkWon
    std::bitset<162> wonBoards;
    // player who has won, or BLANK if neither player has won
    unsigned long winner;

    /* @brief return the winner of the first (rightmost) 18 bits of the argument
     *
     * Returns X, O, or BLANK for no winner. The argument is bitset<162> and not
     * bitset<18> because of the difficulty of downsizing a bitset.
     *
     * If both X and O have three-in-a-row combinations, this function's output
     * is not predictabe aside from the fact that it will return either X or O.
     */
    unsigned long checkWon( const std::bitset<162>& ) const;
};

#endif
