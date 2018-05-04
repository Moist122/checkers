#pragma once
#include"board.hh"

class Checkers::Pawn{
public:
    Pawn(const Color col, Square* sq)
        :_color(col), _square(sq) {}

    Color getColor() const
        {return _color;}
    Square* getSquare() const
        {return _square;}
    bool const isKing()
        {return king;}

    void putOnSquare(Square* sq);
    void promote()
        {king=true;}
private:
    const Color _color;
    Square* _square;
    bool king;
};