#pragma once
#include"board.hh"

class Checkers::Board::Square {
public:
    Square(const Color col, const char x, const char y)
        :_color(col), coordinate_x(x), coordinate_y(y), _pawn(nullptr) {}
    
    bool isOccupied() const
        {return _pawn;}
    Color getColor() const
        {return _color;}
    Pawn* getPawn() const
        {return _pawn;}
    const char getX() const
        {return coordinate_x;}
    const char getY() const
        {return coordinate_y;}
    
    bool putPawn(Pawn* p);
    bool removePawn();
private:
    const Color _color;
    const char coordinate_x;
    const char coordinate_y;
    Pawn* _pawn;
};