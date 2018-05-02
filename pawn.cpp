#include"pawn.hh"
#include"square.hh"
bool Checkers::Pawn::putOnSquare(Board::Square* sq) {
    if(!sq->isOccupied()) {
        _square=sq;
        return true;
    }
    return false;
}