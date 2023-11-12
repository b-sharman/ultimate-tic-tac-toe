class Board {
public:
    Board();

    /* @brief return whether a board number and square number are out of bounds
     *
     * "out of bounds" means not in the interval [0, 8]
     */
    bool is_invalid_input( const int boardNum, const int squareNum ) const;

    /* @brief return the index of the rightmost bit of a certain square
     *
     * boardNum and squareNum, each of which must be in the interval [0, 8],
     * inclusive, specify which board number and square number, respectively,
     * to access. Each are numbered in row-major order. Throws
     * std::out_of_range if either boardNum or squareNum are outside the
     * interval [0, 8].
     *
     * The offset is from the right, not the left, for convenience with
     * bitset.set() and bitset.test().
     */
    int offset( const int, const int ) const;

    /* @brief print the board with std::cout */
    void print() const;

    /* @brief return the value of any square on the board
     *
     * throws an error if boardNum or squareNum do not pass is_invalid_input
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
