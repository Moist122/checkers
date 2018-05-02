#include"square.hh"

bool Checkers::Board::Square::putPawn(Checkers::Pawn* p) {
    if(!isOccupied()) {
        _pawn=p;
        return true;
    }
    return false;
}