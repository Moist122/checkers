#include<iostream>
#include"checkers.hh"

using namespace std;

int main() {
    Checkers game;
    char board[y_graphic_array][x_graphic_array];
    char choice[3];
    char currentPawn[3];
    currentPawn[2] = '\0';
    while(1) {
        game.showBoard(board);
        for(char i=0;i<y_graphic_array;++i)
            cout<<board[i]<<endl;
        if(game.getTP()==game.CHOOSEPAWN){
            if(game.whoseMove()==game.WHITE)
                cout<<"White's move, choose pawn:"<<endl;
            else
                cout<<"Black's move, choose pawn:"<<endl;
            cin>>choice;
            while(!game.choosePawn(choice[0],choice[1])) {
                cout<<"Invalid choice, try again"<<endl;
                cin>>choice;
            }
            currentPawn[0]=choice[0];
            currentPawn[1]=choice[1];
        }
        else {
            cout<<"Move pawn "<<currentPawn<<':'<<endl;
            cin>>choice;
            while(!game.makeMove(choice[0],choice[1])){
                cout<<"Invalid choice, try again"<<endl;
                cin>>choice;
            }
            
            while(game.getTP()==game.CHOOSEMOVE) {
                currentPawn[0]=choice[0];
                currentPawn[1]=choice[1];
                game.showBoard(board);
                for(char i=0;i<y_graphic_array;++i)
                    cout<<board[i]<<endl;
                cout<<"Choose next capture with "<<currentPawn<<':'<<endl;
                cin>>choice;
            
                while(!game.capture(choice[0],choice[1])) {
                    cout<<"Invalid choice, try again"<<endl;
                    cin>>choice;
                }
            }
        }
        if(game.whoseMove()==game.BLACK&&game.checkWhiteWin()){
            cout<<"White won!"<<endl;
            game.showBoard(board);
            for(char i=0;i<y_graphic_array;++i)
                cout<<board[i]<<endl;
            break;
        }
        if(game.whoseMove()==game.WHITE&&game.checkBlackWin()){
            cout<<"Black won!"<<endl;
            game.showBoard(board);
            for(char i=0;i<y_graphic_array;++i)
                cout<<board[i]<<endl;
            break;
        }
    }
    return 0;
}