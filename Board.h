class Board {
public:
    bool is_invalid_input( const int boardNum, const int squareNum ) const;
    /* @brief return the index of the first bit of a certain square on the board
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
    int offset( const int boardNum, const int squareNum ) const;
    void print() const;
    unsigned long getSquare( const int& boardNum, const int& squareNum ) const;
    void setSquare( const int& boardNum, const int& squareNum, const int& value );
private:
    std::bitset<162> board;
};
