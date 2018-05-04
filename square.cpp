#include"square.hh"

bool Checkers::Square::putPawn(Checkers::Pawn* p) {
    if(!isOccupied()) {
        _pawn=p;
        return true;
    }
    return false;
}