#include<cmath>
#include <algorithm>

#include"board.hh"
#include"square.hh"

Checkers::Board::Board() {
    for(char i=0;i<board_size;++i)
        for(char j=0;j<board_size;++j) {
            char x = 'A'+j;
            char y = '1'+i;
            if((i+j)%2) _squares[i][j] = new Square(BLACK,x,y);
            else _squares[i][j] = new Square(WHITE,x,y);
        }
}

Checkers::Board::~Board() {
    for(char i=0;i<board_size;++i)
        for(char j=0;j<board_size;++j)
            delete _squares[i][j];
}

Checkers::Board::Square* Checkers::Board::operator()(const char x, const char y) {
    if(x>='A'&&x<'A'+board_size&&y>='1'&&y<'1'+board_size)
        return _squares[y-'1'][x-'A'];
    return nullptr;
}

bool Checkers::Board::areDiagonal(Checkers::Board::Square* a, Checkers::Board::Square* b)
    {return std::abs(a->getX()-b->getX())==std::abs(a->getY()-b->getY());}

char Checkers::Board::distance(Checkers::Board::Square* a, Checkers::Board::Square* b)
    {return std::max(a->getX()-b->getX(),a->getY()-b->getY());}