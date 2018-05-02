#pragma once
#include<list>
#include"comparators.hh"

constexpr char board_size=8;
constexpr char x_boundries[]={'A','A'+board_size-1};
constexpr char y_boundries[]={'1','1'+board_size-1};

class Checkers::Board::Square;

class Checkers {
public:
    Checkers();
    ~Checkers();
    class Board;
    class Pawn;
    enum Color {WHITE, BLACK};

    void showBoard(char board[board_size+2][board_size+3]);
    bool choosePawn(char,char);
    bool makeMove(char,char);
    bool capture(char,char);
    
private:
    bool isAbleToMove(Pawn*);
    bool isAbleToCapture(Pawn*);
    void changePlayer()
        {move = move==WHITE ? BLACK:WHITE;}
    void movePawn(Board::Square*,Board::Square*);

private:
    Board* _board;
    std::list<Pawn*> black_pawns;
    std::list<Pawn*> white_pawns;
    Color move;
    Pawn* chosenPawn;
    Between comp;
    Different<Color> col_comp;
};