#pragma once
#include"board.hh"
//#include"square.hh"

class Checkers::Pawn{
public:
    Pawn(const Color col, Board::Square* sq)
        :_color(col), _square(sq) {}

    Color getColor() const
        {return _color;}
    Board::Square* getSquare() const
        {return _square;}
    bool const isKing()
        {return king;}

    bool putOnSquare(Board::Square* sq);
    void promote()
        {king=true;}
private:
    const Color _color;
    Board::Square* _square;
    bool king;
};