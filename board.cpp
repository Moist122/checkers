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

Checkers::Square* Checkers::Board::operator()(const char x, const char y) {
    if(x>='A'&&x<'A'+board_size&&y>='1'&&y<'1'+board_size)
        return _squares[y-'1'][x-'A'];
    return nullptr;
}

bool Checkers::Board::areDiagonal(Checkers::Square* a, Checkers::Square* b)
    {return std::abs(a->getX()-b->getX())==std::abs(a->getY()-b->getY());}

char Checkers::Board::distance(Checkers::Square* a, Checkers::Square* b) {
    return std::max(std::abs(a->getX()-b->getX()),std::abs(a->getY()-b->getY()));}

char Checkers::Board::howManyPawnsBetween(Checkers::Square* a, Checkers::Square* b) {
    if(distance(a,b)<=1) return 0;
    char directionX= (b->getX()-a->getX()) / (distance(a,b));
    char directionY= (b->getY()-a->getY()) / (distance(a,b));
    char x=a->getX()+directionX;
    char y=a->getY()+directionY;
    char counter = 0;
    for(x,y;x!=b->getX()&&y!=b->getY();x+=directionX,y+=directionY)
        if((*this)(x,y)->isOccupied()) counter++;
    return counter;
}

Checkers::Pawn* Checkers::Board::pawnBetween(Checkers::Square* a, Checkers::Square* b) {
    char directionX= (b->getX()-a->getX()) / (distance(a,b));
    char directionY= (b->getY()-a->getY()) / (distance(a,b));
    char x=a->getX()+directionX;
    char y=a->getY()+directionY;
    for(x,y;x!=b->getX()&&y!=b->getY();x+=directionX,y+=directionY)
        if((*this)(x,y)->isOccupied()) return (*this)(x,y)->getPawn();
    return nullptr;
}