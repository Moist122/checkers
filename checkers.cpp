#include"checkers.hh"
#include"board.hh"
#include"square.hh"
#include"pawn.hh"

#include<algorithm>

Checkers::Checkers()
:_board(new Board), move(WHITE), chosenPawn(nullptr), tp(CHOOSEPAWN){
    Board& b=*_board;
    tp = CHOOSEPAWN;
    move = WHITE;
    //create pawns
    for(char i=y_boundries[0];comp(y_boundries[0],i,y_boundries[0]+num_rows-1);++i)
        for(char j=x_boundries[0];comp(x_boundries[0],j,x_boundries[1]);++j)
            if(b(j,i)->getColor()==WHITE){
                Pawn* p=new Pawn(WHITE,b(j,i));
                b(j,i)->putPawn(p);
                white_pawns.push_back(p);
            }
    //(*_board)('A','3')->getPawn()->promote();

    for(char i=y_boundries[1];comp(y_boundries[1]-num_rows+1,i,y_boundries[1]);--i)
        for(char j=x_boundries[0];comp(x_boundries[0],j,x_boundries[1]);++j)
            if(b(j,i)->getColor()==WHITE){
                Pawn* p=new Pawn(BLACK,b(j,i));
                b(j,i)->putPawn(p);
                black_pawns.push_back(p);
            }
                //Pawn* p=new Pawn(WHITE,b('H','4'));
                //b('H','4')->putPawn(p);
                //white_pawns.push_back(p);
/*
    for(char i=y_boundries[1]-3;comp(y_boundries[1]-3,i,y_boundries[1]);--i)
        for(char j=x_boundries[0];comp(x_boundries[0],j,x_boundries[1]);++j)
            if(b(j,i)->getColor()==WHITE){
                Pawn* p=new Pawn(BLACK,b(j,i));
                b(j,i)->putPawn(p);
                black_pawns.push_back(p);
            }*/
        
}
Checkers::Checkers(Checkers& game) {
    _board = new Board();
    //copy pawns
    for(auto i: game.white_pawns) {
        Square* sq = (*_board)(i->getSquare()->getX(),i->getSquare()->getY());
        Pawn* p = new Pawn(i->getColor(),sq);
        sq->putPawn(p);
        white_pawns.push_back(p);
    }
    for(auto i: game.black_pawns) {
        Square* sq = (*_board)(i->getSquare()->getX(),i->getSquare()->getY());
        Pawn* p = new Pawn(i->getColor(),sq);
        sq->putPawn(p);
        black_pawns.push_back(p);
    }
    move = game.move;
    tp = game.tp;
    if(game.chosenPawn) {
        choosePawn(game.chosenPawn->getSquare()->getX(),game.chosenPawn->getSquare()->getY());
    }
        
}
Checkers::~Checkers() {
    delete _board;
    for(auto i: white_pawns) delete i;
    for(auto i: black_pawns) delete i;
}

void Checkers::showBoard(char board[y_graphic_array][x_graphic_array]) {
    //board drawing with ASCII
    for(int i=0;i<y_graphic_array;++i)
        for(int j=0;j<x_graphic_array;++j)
            board[i][j]=' ';
    for(int i=1;i<x_graphic_array-2;++i)
        board[1][i]=board[y_graphic_array-2][i]='=';
    for(int i=2;i<y_graphic_array-2;++i)
        board[i][1]=board[i][x_graphic_array-3]='|';
    for(int i=2;i<4+2*board_size;i+=2)
        for(int j=2;j<y_graphic_array-2;++j) {
            board[j][i] = j%2 ? '+':'|';
        }
    for(int i=3;i<3+2*board_size;i+=2)
        for(int j=3;j<y_graphic_array-2;j+=2) {
            board[j][i] = '-';
        }
    // square coordinates
    for(char i=y_boundries[0];comp(y_boundries[0],i,y_boundries[1]);++i)
        board[(y_boundries[1]-i)*2+2][0]=board[(y_boundries[1]-i)*2+2][x_graphic_array-2]=i;
    for(char i=x_boundries[0];comp(x_boundries[0],i,x_boundries[1]);++i)
        board[0][(i-x_boundries[0])*2+3]=board[y_graphic_array-1][(i-x_boundries[0])*2+3]=i;
    // puting pawns and black squares
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
            board[(y_boundries[1]-i)*2+2][(j-x_boundries[0])*2+3]=symbol;
        }
    // ending lines
    for(char i=0;i<y_graphic_array;++i)
        board[i][x_graphic_array-1]='\0';
}

bool Checkers::isAbleToMove(Checkers::Pawn* p){
    Board& b=*_board;
    Square* sq=p->getSquare();
    char x=sq->getX();
    char y=sq->getY();
    char direction=1;
    Color col=p->getColor();
    if(col==BLACK) direction=-1;
    if((b.onBoard(x-1,y+direction)&&!b(x-1,y+direction)->isOccupied())||\
    (b.onBoard(x+1,y+direction)&&!b(x+1,y+direction)->isOccupied()))
        return true;
    if(p->isKing())
        if((b.onBoard(x-1,y-direction)&&!b(x-1,y-direction)->isOccupied())||\
            (b.onBoard(x+1,y-direction)&&!b(x+1,y-direction)->isOccupied()))
            return true;
    return false;
}

bool Checkers::isAbleToCapture(Checkers::Pawn* p){
    Board& b=*_board;
    Square* sq=p->getSquare();
    char x=sq->getX();
    char y=sq->getY();
    char direction=1;
    Color col=p->getColor();
    if(col==BLACK) direction=-1;
    if(!p->isKing()){
        if((b.onBoard(x-2,y+2*direction)&&b(x-1,y+direction)->isOccupied()&&\
        b(x-1,y+direction)->getPawn()->getColor()!=col&&!b(x-2,y+2*direction)->isOccupied())||\
        (b.onBoard(x+2,y+2*direction)&&b(x+1,y+direction)->isOccupied()&&\
        b(x+1,y+direction)->getPawn()->getColor()!=col&&!b(x+2,y+2*direction)->isOccupied())||\
        (b.onBoard(x-2,y-2*direction)&&b(x-1,y-direction)->isOccupied()&&\
        b(x-1,y-direction)->getPawn()->getColor()!=col&&!b(x-2,y-2*direction)->isOccupied())||\
        (b.onBoard(x+2,y-2*direction)&&b(x+1,y-direction)->isOccupied()&&\
        b(x+1,y-direction)->getPawn()->getColor()!=col&&!b(x+2,y-2*direction)->isOccupied()))
            return true;
    }
    else {
        char x1=x+1, y1=y+1;
        for(x1,y1;b.onBoard(x1,y1);x1++,y1++){
            char pawnsBetween = b.howManyPawnsBetween(b(x,y),b(x1,y1));
            if(pawnsBetween>1) break;
            if(pawnsBetween==1&&b.pawnBetween(b(x,y),b(x1,y1))->getColor()!=col&&\
                !b(x1,y1)->isOccupied()) return true;
        }
        x1=x-1, y1=y+1;
        for(x1,y1;b.onBoard(x1,y1);x1--,y1++){
            char pawnsBetween = b.howManyPawnsBetween(b(x,y),b(x1,y1));
            if(pawnsBetween>1) break;
            if(pawnsBetween==1&&b.pawnBetween(b(x,y),b(x1,y1))->getColor()!=col&&\
                !b(x1,y1)->isOccupied()) return true;
        }
        x1=x-1, y1=y-1;
        for(x1,y1;b.onBoard(x1,y1);x1--,y1--){
            char pawnsBetween = b.howManyPawnsBetween(b(x,y),b(x1,y1));
            if(pawnsBetween>1) break;
            if(pawnsBetween==1&&b.pawnBetween(b(x,y),b(x1,y1))->getColor()!=col&&\
                !b(x1,y1)->isOccupied()) return true;
        }
        x1=x+1, y1=y-1;
        for(x1,y1;b.onBoard(x1,y1);x1++,y1--){
            char pawnsBetween = b.howManyPawnsBetween(b(x,y),b(x1,y1));
            if(pawnsBetween>1) break;
            if(pawnsBetween==1&&b.pawnBetween(b(x,y),b(x1,y1))->getColor()!=col&&\
                !b(x1,y1)->isOccupied()) return true;
        }
    }
    return false;
}

bool Checkers::choosePawn(char x, char y) {
    if(!_board->onBoard(x,y)) return false;
    auto sq = (*_board)(x,y);
    if(sq->isOccupied()&&sq->getPawn()->getColor()==move&&\
        (isAbleToMove(sq->getPawn())||isAbleToCapture(sq->getPawn()))){
        chosenPawn=sq->getPawn();
        tp=CHOOSEMOVE;
        return true;
    }
    return false;
}

bool Checkers::makeMove(char x, char y) { 
    if(!_board->onBoard(x,y)) {return false;}
    auto pawnColor = chosenPawn->getColor();
    auto sq1 = chosenPawn->getSquare();
    auto sq2 = (*_board)(x,y);
    char direction=1;
    if(pawnColor==BLACK) direction=-1;

    if(_board->areDiagonal(sq1,sq2)&&y==sq1->getY()+direction&&!sq2->isOccupied()){
        movePawn(sq1,sq2);
        changePlayer();
        chosenPawn=nullptr;
        tp=CHOOSEPAWN;
        return true;
    }
    if(_board->areDiagonal(sq1,sq2)&&_board->distance(sq1,sq2)==2&&\
        _board->howManyPawnsBetween(sq1,sq2)==1&&\
        _board->pawnBetween(sq1,sq2)->getColor()!=pawnColor\
        &&!sq2->isOccupied()){
            movePawn(sq1,sq2);
            removePawn(_board->pawnBetween(sq1,sq2));
            if(!isAbleToCapture(chosenPawn)){
                chosenPawn=nullptr;
                changePlayer();
                tp=CHOOSEPAWN;
            }
            else
                tp = CHOOSECAPTURE;
        return true;
    }
    if(chosenPawn->isKing()){
        if(_board->areDiagonal(sq1,sq2)&&_board->howManyPawnsBetween(sq1,sq2)==0\
            &&!sq2->isOccupied()){
            movePawn(sq1,sq2);
            changePlayer();
            chosenPawn=nullptr;
            tp=CHOOSEPAWN;
            return true;
        }
        if(_board->areDiagonal(sq1,sq2)&&\
            _board->howManyPawnsBetween(sq1,sq2)==1&&\
            _board->pawnBetween(sq1,sq2)->getColor()!=pawnColor\
            &&!sq2->isOccupied()){
                movePawn(sq1,sq2);
                removePawn(_board->pawnBetween(sq1,sq2));
                if(!isAbleToCapture(chosenPawn)){
                    chosenPawn=nullptr;
                    changePlayer();
                    tp=CHOOSEPAWN;
                }
                else
                    tp = CHOOSECAPTURE;
            return true;
        }
    }
    return false;
}

bool Checkers::capture(char x, char y) {
    if(!_board->onBoard(x,y)) return false;
    auto pawnColor = chosenPawn->getColor();
    auto sq1 = chosenPawn->getSquare();
    auto sq2 = (*_board)(x,y);
    if(_board->areDiagonal(sq1,sq2)&&_board->distance(sq1,sq2)==2&&\
        _board->howManyPawnsBetween(sq1,sq2)==1&&\
        _board->pawnBetween(sq1,sq2)->getColor()!=pawnColor\
        &&!sq2->isOccupied()){
            movePawn(sq1,sq2);
            removePawn(_board->pawnBetween(sq1,sq2));
            if(!isAbleToCapture(chosenPawn)){
                chosenPawn=nullptr;
                changePlayer();
                tp=CHOOSEPAWN;
            }
            else
                tp = CHOOSECAPTURE;
        return true;
    }
    if(chosenPawn->isKing())
        if(_board->areDiagonal(sq1,sq2)&&\
            _board->howManyPawnsBetween(sq1,sq2)==1&&\
            _board->pawnBetween(sq1,sq2)->getColor()!=pawnColor\
            &&!sq2->isOccupied()){
                movePawn(sq1,sq2);
                removePawn(_board->pawnBetween(sq1,sq2));
                if(!isAbleToCapture(chosenPawn)){
                    chosenPawn=nullptr;
                    changePlayer();
                    tp=CHOOSEPAWN;
                }
                else
                    tp = CHOOSECAPTURE;
                return true;
        }
    return false;
}

void Checkers::movePawn(Checkers::Square* sq1, Checkers::Square* sq2) {
    Pawn* p=sq1->getPawn();
    sq1->removePawn();
    sq2->putPawn(p);
    p->putOnSquare(sq2);
    if((p->getColor()==WHITE&&p->getSquare()->getY()==y_boundries[1])||\
        (p->getColor()==BLACK&&p->getSquare()->getY()==y_boundries[0]))
        p->promote();
}

void Checkers::removePawn(Pawn* p) {
    p->getSquare()->removePawn();
    if(p->getColor()==BLACK){
        auto findIter = std::find(black_pawns.begin(), black_pawns.end(), p);
        black_pawns.erase(findIter);
    }
    else {
        auto findIter = std::find(white_pawns.begin(), white_pawns.end(), p);
        white_pawns.erase(findIter);
    }
    delete p;
}

bool Checkers::checkWhiteWin() {
    if(!black_pawns.size())
        return true;
    for(auto i:black_pawns)
        if(isAbleToMove(i)||isAbleToCapture(i)) return false;
    return true;
}
bool Checkers::checkBlackWin() {
    if(!white_pawns.size())
        return true;
    for(auto i:white_pawns)
        if(isAbleToMove(i)||isAbleToCapture(i)) return false;
    return true;
}

bool Checkers::gameWon() {
    if((move==WHITE&&checkBlackWin())||(move==BLACK&&checkWhiteWin()))
        return true;
    return false;
}

bool Checkers::playerChoice(char a, char b) {
    if(tp==CHOOSEPAWN)
        return choosePawn(a,b);
    else if(tp==CHOOSEMOVE)
        return makeMove(a,b);
    else
        return capture(a,b);
}

void Checkers::getChosenPawnCoordinates(char str[3]) {
    Square* sq=chosenPawn->getSquare();
    str[0]=sq->getX();
    str[1]=sq->getY();
    str[2]='\0';
}

int Checkers::evaluate() {
    int result = white_pawns.size() - black_pawns.size();
    for(auto i: white_pawns) if(i->isKing()) result+=2;
    for(auto i: black_pawns) if(i->isKing()) result-=2;
    if(move==WHITE&&checkBlackWin()) return -1000;
    if(move==BLACK&&checkWhiteWin()) return 1000;
    return result;
}

std::list<Checkers::Pawn*> Checkers::listPawns() {
    if(move==WHITE)
        return white_pawns;
    return black_pawns;
}