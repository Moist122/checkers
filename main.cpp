#include<iostream>
#include"checkers.hh"

using namespace std;

int main() {
    Checkers game;
    char board[board_size+2][board_size+3];
    game.showBoard(board);
    for(char i=0;i<board_size+2;++i)
        cout<<board[i]<<endl;
    return 0;
}