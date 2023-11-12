#include <bitset>
#include <string>
#include <unordered_map>

using namespace std;

constexpr int BLANK {0b00};
constexpr int O {0b10};
constexpr int X {0b11};
constexpr bitset<6> O_WON {(O << 2 | O) << 2 | O};
constexpr bitset<6> X_WON {(X << 2 | X) << 2 | X};
// cannot be constexpr because X and O are not literals
const unordered_map<int,char> INT_CHAR_MAP = {{X, 'X'}, {O, 'O'}, {BLANK, ' '}};
const unordered_map<char,int> CHAR_INT_MAP = {{'X', X}, {'O', O}};

// cannot be constexpr because std::string is not literal
const string BIG_O {"/`\\| |\\_/"};
const string BIG_X {"\\ / X / \\"};
