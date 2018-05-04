#pragma once
#include"board.hh"

class Checkers::Square {
    //square as a part of the board
public:
    Square(const Color col, const char x, const char y)
        :_color(col), coordinate_x(x), coordinate_y(y), _pawn(nullptr) {}
    
    bool isOccupied() const //check if there is a pawn on a square
        {return _pawn;}
    Color getColor() const //get color of a square
        {return _color;}
    Pawn* getPawn() const //get pawn standing on a square
        {return _pawn;}
    const char getX() const //get x coordinate of a square A-...
        {return coordinate_x;}
    const char getY() const //get y coordinate of a square 1-...
        {return coordinate_y;}
    
    bool putPawn(Pawn* p); //put pawn on a square
    bool removePawn() //remove pawn standing on a square
        {_pawn=nullptr;}
private:
    const Color _color; //color of a square
    const char coordinate_x; //first coordinate of a square
    const char coordinate_y; //second coordinate of a square
    Pawn* _pawn; //pawn stending on a square (nullptr if square is empty)
};