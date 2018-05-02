#pragma once
#include"checkers.hh"

class Checkers::Board {
public:
    Board();
    ~Board();
    class Square;

    Square* operator()(const char x, const char y);
    bool onBoard(char x, char y)
        {return comp(x_boundries[0],x,x_boundries[1])&&comp(y_boundries[0],y,y_boundries[1]);}
    bool areDiagonal(Square* a, Square* b);
    char distance(Square* a, Square* b);

private:
    Square* _squares[board_size][board_size];
    Between comp;
};