#pragma once
#include"checkers.hh"

class Checkers::Board {
    //board as an array of squares with coordinates
public:
    Board();
    ~Board();

    Square* operator()(const char x, const char y); //get square with coordinates x y
    bool onBoard(char x, char y) //check if coordinates represent a square
        {return comp(x_boundries[0],x,x_boundries[1])&&comp(y_boundries[0],y,y_boundries[1]);}
    bool areDiagonal(Square* a, Square* b); //check if squares are diagonal
    char distance(Square* a, Square* b); //check distance between diagonal squares
    Pawn* pawnBetween(Square* a, Square* b); //get pawn between 2 squares
    char howManyPawnsBetween(Square* a,Square* b);
        //count pawns between 2 squares (exluding these squares)

private:
    Square* _squares[board_size][board_size]; //array of squares forming a board
    Between comp; // to check if coordinates are part of the board
};