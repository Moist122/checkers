#pragma once
#include"board.hh"

class Checkers::Pawn{
    //pawn in checkers
public:
    Pawn(const Color col, Square* sq, bool k=false)
        :_color(col), _square(sq), king(k) {}
    Pawn(Pawn& p)
        :_color(p._color), king(p.king) {}

    Color getColor() const //get color of a pawn
        {return _color;}
    Square* getSquare() const //get square on which pawn stands
        {return _square;}
    bool const isKing() //is pawn a king?
        {return king;}

    void putOnSquare(Square* sq); //put pawn on a square
    void promote() //make pawn a king
        {king=true;}
private:
    const Color _color; //color of a pawn
    Square* _square; //square on which pawn stands
    bool king; //true if pawn is king
};