#include "moves.h"

using namespace std;

Moves::Moves (tuple<int, int> initialPosition, tuple<int, int> finalPosition, Board* board)
    :  initialPosition{initialPosition}, finalPosition{finalPosition}, board{board} {}

Moves::~Moves () {}

tuple<int, int> Moves::getInitialPosition() {
    return initialPosition;
}

tuple<int, int> Moves::getFinalPosition() {
    return finalPosition;
}

Board *Moves::getBoard() {
    return board;
}

bool Moves::operator==(const Moves &rhs) {
    if (initialPosition != rhs.initialPosition || finalPosition != rhs.finalPosition ||board != rhs.board) {
        return false;
    }
    
    return true;
}