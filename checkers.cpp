#include"checkers.hh"
#include"board.hh"
#include"square.hh"
#include"pawn.hh"

#include<iostream>

Checkers::Checkers()
:_board(new Board), move(WHITE), chosenPawn(nullptr){
    Board& b=*_board;
    //create white pawns
    for(char i=y_boundries[0];comp(y_boundries[0],i,y_boundries[0]+2);++i)
        for(char j=x_boundries[0];comp(x_boundries[0],j,x_boundries[1]);++j)
            if(b(j,i)->getColor()==WHITE){
                Pawn* p=new Pawn(WHITE,b(j,i));
                b(j,i)->putPawn(p);
                white_pawns.push_back(p);
            }

    for(char i=y_boundries[1];comp(y_boundries[1]-2,i,y_boundries[1]);--i)
        for(char j=x_boundries[0];comp(x_boundries[0],j,x_boundries[1]);++j)
            if(b(j,i)->getColor()==WHITE){
                Pawn* p=new Pawn(BLACK,b(j,i));
                b(j,i)->putPawn(p);
                black_pawns.push_back(p);
            }
        
}
Checkers::~Checkers() {
    delete _board;
}

void Checkers::showBoard(char board[board_size+2][board_size+3]) {
    board[0][0]=board[0][board_size+1]=\
    board[board_size+1][0]=board[board_size+1][board_size+1]=' ';

    for(char i=y_boundries[0];comp(y_boundries[0],i,y_boundries[1]);++i)
        board[y_boundries[1]-i+1][0]=board[y_boundries[1]-i+1][board_size+1]=i;
    for(char i=x_boundries[0];comp(x_boundries[0],i,x_boundries[1]);++i)
        board[0][i-x_boundries[0]+1]=board[board_size+1][i-x_boundries[0]+1]=i;
    
    for(char i=y_boundries[0];comp(y_boundries[0],i,y_boundries[1]);++i)
        for(char j=x_boundries[0];comp(x_boundries[0],j,x_boundries[1]);++j) {
            char symbol = ' ';
            if(!(*_board)(j,i)->isOccupied()){
                if((*_board)(j,i)->getColor()==BLACK)
                    symbol='*';
            }
            else {
                Pawn* pwn=(*_board)(j,i)->getPawn();
                if(pwn->getColor()==WHITE)
                    symbol='o';
                else
                    symbol='x';
                if(pwn->isKing()) symbol -= 32;
            }
            board[y_boundries[1]+1-i][j-x_boundries[0]+1]=symbol;
        }
    for(char i=0;i<board_size+2;++i)
        board[i][board_size+2]='\0';
}

bool Checkers::isAbleToMove(Checkers::Pawn* p){
    Board& b=*_board;
    Board::Square* sq=p->getSquare();
    char x=sq->getX();
    char y=sq->getY();
    char direction=1;
    Color col=p->getColor();
    if(col==BLACK) direction=-1;
    if(!p->isKing()){
        if((b.onBoard(x-1,y+direction)&&!b(x-1,y+direction)->isOccupied())||\
        (b.onBoard(x+1,y+direction)&&!b(x+1,y+direction)->isOccupied()))
            return true;
    }
    //KING
    return false;
}

bool Checkers::isAbleToCapture(Checkers::Pawn* p){
    Board& b=*_board;
    Board::Square* sq=p->getSquare();
    char x=sq->getX();
    char y=sq->getY();
    char direction=1;
    Color col=p->getColor();
    if(col==BLACK) direction=-1;
    if(!p->isKing()){
        if((b.onBoard(x-2,y+2*direction)&&b(x-1,y+direction)->getPawn()->getColor()!=col&&\
        !b(x-2,y+2*direction)->isOccupied())||\
        (b.onBoard(x+2,y+2*direction)&&b(x+1,y+direction)->getPawn()->getColor()!=col&&\
        !b(x+2,y+2*direction)->isOccupied())||\
        (b.onBoard(x-2,y-2*direction)&&b(x-1,y-direction)->getPawn()->getColor()!=col&&\
        !b(x-2,y-2*direction)->isOccupied())||\
        (b.onBoard(x+2,y-2*direction)&&b(x+1,y-direction)->getPawn()->getColor()!=col&&\
        !b(x+2,y-2*direction)->isOccupied()))
            return true;
    }
    //KING
    return false;
}

bool Checkers::choosePawn(char x, char y) {
    if(!_board->onBoard(x,y)) return false;
    auto sq = (*_board)(x,y);
    if(sq->isOccupied()&&sq->getPawn()->getColor()==move&&\
        (isAbleToMove(sq->getPawn())||isAbleToCapture(sq->getPawn()))){
        chosenPawn=sq->getPawn();
        return true;
    }
    return false;
}

bool Checkers::makeMove(char x, char y) {
    if(!_board->onBoard(x,y)) return false;
    auto pawnColor = chosenPawn->getColor();
    auto sq1 = chosenPawn->getSquare();
    auto sq2 = (*_board)(x,y);
    if(_board->areDiagonal(sq1,sq2)&&_board->distance(sq1,sq2)==1&&!sq2->isOccupied()){
        movePawn(sq1,sq2);
        changePlayer();
        chosenPawn=nullptr;
        return true;
    }
    //KING
    return false;
}

void Checkers::movePawn(Checkers::Board::Square* sq1, Checkers::Board::Square* sq2) {

}