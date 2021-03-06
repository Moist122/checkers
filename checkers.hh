#pragma once
#include<list>
#include<vector>
#include"comparators.hh"

constexpr char board_size=8; //board is square board_size x board_size
constexpr char num_rows=3; //number of rows with pawns at the start
constexpr char x_boundries[]={'A','A'+board_size-1}; //boundries of x coordinates on board
constexpr char y_boundries[]={'1','1'+board_size-1}; //boundries of y coordinates on board
constexpr char x_graphic_array = 2*board_size+6; //size of char array representing board graphicly
constexpr char y_graphic_array = 2*board_size+3;

class Checkers {
    //class representing a game of checkers
public:
    Checkers(); //create basic game object
    Checkers(const Checkers&); //copy constructor
    ~Checkers();
    class Board;
    class Pawn;
    class Square;
    enum Color {WHITE, BLACK}; //colors of pawns and squares
    enum TurnPhase {CHOOSEPAWN, CHOOSEMOVE, CHOOSECAPTURE}; //turn phases

    const TurnPhase getTP() //get current turn phase
        {return tp;}

    void showBoard(char board[y_graphic_array][x_graphic_array]);
        //show the board representation as an array
    bool checkWhiteWin();
        // true if black can't move or has no pawns
    bool checkBlackWin();
        // true if white can't move or has no pawns
    Color whoseMove() const //whose move is now
        {return move;}
    bool playerChoice(char a, char b); //player chooses pawn or move
    bool gameWon(); //check if a player won the game
    Pawn* getChosenPawn() //get currently chosen pawn
        {return chosenPawn;}
    void getChosenPawnCoordinates(char[3]);
        //xy coordinates of currently chosen pawn
    std::list<Pawn*>& listPawns();
        //list of pawns of current player
    int evaluate(); //get game value using heuristic
    bool onBoard(char a, char b); //is square with coordinates a b on board?
    
private:
    bool choosePawn(char,char);
        // choice of pawn to move - returns false if choice is invalid or pawn can't move
    bool makeMove(char,char);
        // choice of destination of pawn to move
    bool capture(char,char);
        // choice of next capture if possible
    bool isAbleToMove(Pawn*); //check if pawn can make move
    bool isAbleToCapture(Pawn*); //check if pawn can capture enemy pawn
    void changePlayer() //change current player
        {move = move==WHITE ? BLACK:WHITE;}
    void movePawn(Square*,Square*); //change location of a pawn
    void removePawn(Pawn*); //destroy pawn

private:
    Board* _board; //game board
    std::list<Pawn*> black_pawns; //all black pawns
    std::list<Pawn*> white_pawns; //all white pawns
    Color move; //color of player that can make move
    Pawn* chosenPawn; //pawn chosen by player to move
    Between comp; //to check if a square is part of the board
    TurnPhase tp; //which turn phase is now
};