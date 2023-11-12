#include <array>
#include <bitset>
#include <string>
#include <unordered_map>

using namespace std;

constexpr bitset<162> SQUARE_ONES {0b11};  // for grabbing the last two bits of a number
constexpr bitset<162> BOARD_ONES {0b111111111111111111};  // for grabbing the last 18 bits of a number

constexpr int BLANK {0b00};
constexpr int O {0b10};
constexpr int X {0b11};
constexpr bitset<162> O_WON {0b101010101010101010};
constexpr bitset<162> X_WON {0b111111111111111111};
constexpr array<bitset<162>, 8> WIN_BITS
{{
    {0b111111000000000000},  // top row
    {0b000000111111000000},  // middle row
    {0b000000000000111111},  // bottom row
    {0b110000110000110000},  // left column
    {0b001100001100001100},  // middle column
    {0b000011000011000011},  // right column
    {0b110000001100000011},  // left-to-right diagonal
    {0b000011001100110000}   // right-to-left diagonal
}};

// cannot be constexpr because std::unordered_map is not literal
const unordered_map<int,char> INT_CHAR_MAP = {{X, 'X'}, {O, 'O'}, {BLANK, ' '}};
const unordered_map<char,int> CHAR_INT_MAP = {{'X', X}, {'O', O}};

// cannot be constexpr because std::string is not literal
const string BIG_O {"/`\\| |\\_/"};
const string BIG_X {"\\ / X / \\"};
