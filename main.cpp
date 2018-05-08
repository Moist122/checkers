#include<iostream>
#include"checkers.hh"

using namespace std;

void printBoard(char board[y_graphic_array][x_graphic_array], Checkers* game) {
        game->showBoard(board);
        for(char i=0;i<y_graphic_array;++i)
            cout<<board[i]<<endl;
}

int main() {
    Checkers game;
    char board[y_graphic_array][x_graphic_array];
    char choice[3];
    char currentPawn[3];
    currentPawn[2] = '\0';
    while(!game.gameWon()) {
        printBoard(board,&game);
        if(game.whoseMove()==game.WHITE)
            cout<<"White's move."<<endl;
        else
            cout<<"Black's move."<<endl;
        if(game.getTP()==game.CHOOSEPAWN)
            cout<<"Choose pawn to move:"<<endl;
        else if(game.getTP()==game.CHOOSEMOVE){
            game.getChosenPawnCoordinates(currentPawn);
            cout<<"Choose move of pawn "\
                <<currentPawn<<':'<<endl;
        }
        else {
            game.getChosenPawnCoordinates(currentPawn);
            cout<<"Choose next capture of pawn "\
                <<currentPawn<<':'<<endl;
        }
        cin>>choice;
        cout<<choice[0]<<choice[1]<<endl;
        while(!game.playerChoice(choice[0],choice[1])) {
            cout<<"Invalid choice, try again."<<endl;
            cin>>choice;
        }
    }
    if(game.whoseMove()==game.BLACK) cout<<"White won!"<<endl;
    else cout<<"Black won!"<<endl;
    return 0;
}