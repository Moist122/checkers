#pragma once
#include<list>
#include"comparators.hh"

constexpr char board_size=5;
constexpr char num_rows=2;
constexpr char x_boundries[]={'A','A'+board_size-1};
constexpr char y_boundries[]={'1','1'+board_size-1};
constexpr char x_graphic_array = 2*board_size+6;
constexpr char y_graphic_array = 2*board_size+3;

class Checkers {
public:
    Checkers();
    ~Checkers();
    class Board;
    class Pawn;
    class Square;
    enum Color {WHITE, BLACK};
    enum TurnPhase {CHOOSEPAWN, CHOOSEMOVE};

    const TurnPhase getTP()
        {return tp;}

    void showBoard(char board[y_graphic_array][x_graphic_array]);
    bool choosePawn(char,char);
    bool makeMove(char,char);
    bool capture(char,char);
    bool checkWhiteWin();
    bool checkBlackWin();
    Color whoseMove() const
        {return move;}
    
private:
    bool isAbleToMove(Pawn*);
    bool isAbleToCapture(Pawn*);
    void changePlayer()
        {move = move==WHITE ? BLACK:WHITE;}
    void movePawn(Square*,Square*);
    void removePawn(Pawn*);

private:
    Board* _board;
    std::list<Pawn*> black_pawns;
    std::list<Pawn*> white_pawns;
    Color move;
    Pawn* chosenPawn;
    Between comp;
    Different<Color> col_comp;
    TurnPhase tp;
};