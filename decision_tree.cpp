#include"decision_tree.hh"
#include"pawn.hh"
#include"square.hh"

#include<iostream>

// DecisionTree::DecisionTree(char levels, Checkers* game)
//     :_root(new DecisionNode(game)) {
//         _root->addChildren(levels-1);
// }

// DecisionTree::~DecisionTree() {
//     //TODO
// }

// DecisionTree::DecisionNode::DecisionNode(Checkers* g) 
//     :game(g){
//     if(g->whoseMove()==Checkers::WHITE) move=MAX;
//     else move=MIN;
//     parent = nullptr;
// }

// DecisionTree::DecisionNode::DecisionNode(std::vector<char> d, Checkers* g,\
//         DecisionNode* p) :game(g), parent(p) {
//     if(g->whoseMove()==Checkers::WHITE) move=MAX;
//     else move=MIN;
//     decision = d;
//     int value = g->evaluate();
//     if(value==1000||value==-1000) {
//         score = std::unique_ptr<int>(new int(value));
//     }
// }

// void DecisionTree::DecisionNode::addChildren(char levelsRemaining) {
//     //get pawn list
//     std::list<Checkers::Pawn*> pawns=game->listPawns();
//     char direction = move==MAX ? 1:-1;
//     Checkers gameState(*game);
//     for(auto i: pawns) {
//     std::cout<<"ok0"<<std::endl;
//         //gameState = *game;
//         char x = i->getSquare()->getX();
//         char y = i->getSquare()->getY();
//         if(gameState.playerChoice(x,y)){
//         Checkers basicState(gameState);
//             if(!i->isKing()) {
//                 //all possible non-king moves
//                 if(gameState.playerChoice(x+1,y+direction)) {
//                     std::vector<char> m = {x,y,x+1,y+direction};
//                     children.push_back(new DecisionNode(m,new Checkers(gameState),this));
//                     gameState = basicState;
//     std::cout<<"ok1"<<std::endl;
//                 }
//                 if(gameState.playerChoice(x-1,y+direction)) {
//                     std::vector<char> m = {x,y,x-1,y+direction};
//                     children.push_back(new DecisionNode(m,new Checkers(gameState),this));
//                     gameState = basicState;
//     std::cout<<"ok2"<<std::endl;
//                 }
//                 //possible captures
//                 std::list<Checkers> gameStatesOnTheWay;
//                 std::list<std::vector<char>> m; //sequence of choices
//                 gameStatesOnTheWay.push_back(gameState);
//                 m.push_back({x,y});
//                 while(!gameStatesOnTheWay.empty()) {
//                     gameState = gameStatesOnTheWay.front();
//                     x = m.front()[m.size()-1];
//                     y = m.front().back();
//                     std::vector<std::vector<char>> cptrs = {{2,2},{2,-2},{-2,-2},{-2,2}};
//     std::cout<<"ok3"<<std::endl;
//                     for(auto j:cptrs) {
//     std::cout<<x<<y<<std::endl;
//                         if(gameState.playerChoice(x+j[0],y+j[1])) {
//                             if(gameState.getTP()==gameState.CHOOSECAPTURE){
//                                 gameStatesOnTheWay.push_back(gameState);
//                                 m.push_back(m.front());
//                                 m.back().push_back(x+j[0]);
//                                 m.back().push_back(y+j[1]);
//                             gameState = gameStatesOnTheWay.front();
//                             }
//                             else {
//                                 std::vector<char> mv = m.front();
//                                 mv.push_back(x+j[0]);
//                                 mv.push_back(y+j[1]);
//                                 children.push_back(new DecisionNode(m.front(),&gameState,this));
//                             gameState = gameStatesOnTheWay.front();
//                             }
//                         }
//                     }
//                     std::cout<<"pop front"<<std::endl;
//                     gameStatesOnTheWay.pop_front();
//                     m.pop_front();
//                 }
//                 gameState = *game;
//                     std::cout<<"exit while"<<std::endl;

//             }
//             else { //king
//                 std::vector<std::vector<char>> mvs;
//                 char directions[4][2] {{1,1},{1,-1},{-1,-1},{-1,1}};
//                 std::list<Checkers> gameStatesOnTheWay;
//                 std::list<std::vector<char>> m; //sequence of choices
//                 gameStatesOnTheWay.push_back(gameState);
//                 m.front()[0]=x;
//                 m.front()[1]=y;
//                 while(!gameStatesOnTheWay.empty()) {
//                     for(auto j: directions) {
//                         char mult = 1;
//                         while(gameState.onBoard(x+mult*j[0],y+mult*j[1])) {
//                             mvs.back().push_back(x+mult*j[0]);
//                             mvs.back().push_back(y+mult*j[0]);
//                             ++mult;
//                         }
//                     }
//                     for(auto j:mvs) {
//                         if(gameState.playerChoice(j[0],j[1])) {
//                             if(gameState.getTP()==gameState.CHOOSECAPTURE){
//                                 gameStatesOnTheWay.push_back(gameState);
//                                 m.push_back(m.front());
//                                 m.back().push_back(j[0]);
//                                 m.back().push_back(j[1]);
//                             }
//                             else {
//                                 std::vector<char> mv = m.front();
//                                 mv.push_back(j[0]);
//                                 mv.push_back(j[1]);
//                                 children.push_back(new DecisionNode(m.front(),&gameState,this));
//                             }
//                             gameState = gameStatesOnTheWay.front();
//                         }
//                         gameStatesOnTheWay.pop_front();
//                         m.pop_front();
//                     }
//                 }
//             }
//         }
//     }
//     //iterate children
//     levelsRemaining--;
//     std::cout<<"Levels: "<<int(levelsRemaining)<<std::endl;
//     std::cout<<"delete game"<<std::endl;
//     delete game;
//     if(levelsRemaining<=0)
//         for(auto i: children){
//         std::cout<<"calc val"<<std::endl;
//             i->calculateValue();
//             std::cout<<*i->score;}
//     else
//         for(auto i: children) {
//             if(!i->evaluated())
//                 i->addChildren(levelsRemaining);
//             else std::cout<<"ev"<<std::endl;}
// }

// void DecisionTree::DecisionNode::calculateValue() {
//     score = std::unique_ptr<int>(new int(game->evaluate()));
// }

// std::vector<char> DecisionTree::makeDecision() {
//     return _root->makeDecision(-1000, 1000);
// }

// std::vector<char> DecisionTree::DecisionNode::makeDecision(int a, int b) {
//     std::cout<<"in makedec yay!"<<std::endl;
//     if(evaluated()) return decision;
//     std::vector<char>* choice;
//     if(move==MAX) {
//         int value = -1000;
//         for(auto& node: children) {
//             node->makeDecision(a,b);
//             if(*(node->score)>value) {
//                 value = *(node->score);
//                 choice = &node->decision;
//             }
//             a = std::max(a,value);
//             if(b<=a) break;
//         }
//     }
//     else {
//         int value = 1000;
//         for(auto& node: children) {
//             node->makeDecision(a,b);
//             if(*(node->score)<value) {
//                 value = *(node->score);
//                 choice = &node->decision;
//             }
//             b = std::min(b,value);
//             if(b<=a) break;
//         }
//     }
//     return *choice;
// }

DecisionTree::DecisionTree() :_root(nullptr){}
DecisionTree::~DecisionTree() {
    //std::cout<<Checkers::counter<<std::endl;
    if(!empty()) _root->deleteRecursively();
    //std::cout<<Checkers::counter<<std::endl;
}

void DecisionTree::addRoot(Checkers* game) {
    _root = new DecisionNode(game);
}

DecisionTree::DecisionNode::DecisionNode(Checkers *g)
:  game(new Checkers(*g)), parent(nullptr), depth(0){
    if(game->whoseMove()==game->WHITE) move = MAX;
    else move = MIN;
}

DecisionTree::DecisionNode::DecisionNode(std::vector<char> dec, Checkers* g, DecisionNode* p, int d)
:  game(g), decision(dec), parent(p), depth(d) {
    if(game->whoseMove()==game->WHITE) move = MAX;
    else move = MIN;
}

DecisionTree::DecisionNode::~DecisionNode() {
    if (game) delete game;
}

void DecisionTree::DecisionNode::deleteRecursively() {
    for(auto i:children)
        i->deleteRecursively();
    delete this;
}

void DecisionTree::DecisionNode::calculateValue() {
    score = std::unique_ptr<int>(new int(game->evaluate()));
}

void DecisionTree::DecisionNode::addChildren() {
    //get pawn list
    std::list<Checkers::Pawn*> pawns=game->listPawns();
    char direction = move==MAX ? 1:-1;
    Checkers* gameState = new Checkers(*game);
    for(auto pawn:pawns) {
        char x = pawn->getSquare()->getX();
        char y = pawn->getSquare()->getY();
        if(gameState->playerChoice(x,y)) {
            Checkers* baseState = new Checkers(*gameState);
            if(!pawn->isKing()) {
                if(gameState->playerChoice(x+1,y+direction)) {
                    std::vector<char> m = {x,y,x+1,y+direction};
                    children.push_back(new DecisionNode(m,gameState,this,depth+1));
                    gameState = new Checkers(*baseState);
                }
                if(gameState->playerChoice(x-1,y+direction)) {
                    std::vector<char> m = {x,y,x-1,y+direction};
                    children.push_back(new DecisionNode(m,gameState,this,depth+1));
                    gameState = new Checkers(*baseState);
                }
                std::list<Checkers*> statesToCheck;
                std::list<std::vector<char>> moveSeq;
                statesToCheck.push_back(gameState);
                moveSeq.push_back(std::vector<char>{x,y});
                while(!statesToCheck.empty()) {
                    Checkers* actualState = new Checkers(*statesToCheck.front());
                    std::vector<char> moves = moveSeq.front();
                    char x = *(moves.end()-2);
                    char y = *(moves.end()-1);
                    char cptrs[4][2] = {{x+2,y+2},{x-2,y+2},{x-2,y-2},{x+2,y-2}};
                    for(auto cptr:cptrs) {
                        if(actualState->playerChoice(cptr[0],cptr[1])) {
                            // 2 game states to consider
                            if(actualState->getTP()==actualState->CHOOSECAPTURE) {
                                statesToCheck.push_back(actualState);
                                auto newSeq = moves;
                                newSeq.push_back(cptr[0]);
                                newSeq.push_back(cptr[1]);
                                moveSeq.push_back(newSeq);
                            }
                            else {
                                auto newSeq = moves;
                                newSeq.push_back(cptr[0]);
                                newSeq.push_back(cptr[1]);
                                children.push_back(new DecisionNode(newSeq,actualState,this,depth+1));
                            }
                        actualState = new Checkers(*statesToCheck.front());
                        }
                    }
                    delete actualState;
                    delete statesToCheck.front();
                    statesToCheck.pop_front();
                    moveSeq.pop_front();
                }
            }//non-king
            else { //king
            //std::cout<<"king move"<<std::endl;
                char directions[4][2] {{1,1},{1,-1},{-1,-1},{-1,1}};
                std::list<Checkers*> statesToCheck;
                std::list<std::vector<char>> moveSeq; //sequence of choices
                statesToCheck.push_back(gameState);
                moveSeq.push_back(std::vector<char>{x,y});
                while(!statesToCheck.empty()) {
                    Checkers* actualState = new Checkers(*statesToCheck.front());
                    std::vector<char> moves = moveSeq.front();
                    char x = *(moves.end()-2);
                    char y = *(moves.end()-1);
                    std::list<std::vector<char>> mvs;
                    for(auto j: directions) {
                        char mult = 1;
                        while(gameState->onBoard(x+mult*j[0],y+mult*j[1])) {
                            mvs.push_back(std::vector<char>{x+mult*j[0],y+mult*j[1]});
                            ++mult;
                        }
                    }
                    for(auto mv:mvs) {
                        if(actualState->playerChoice(mv[0],mv[1])) {
                            // 2 game states to consider
                            if(actualState->getTP()==actualState->CHOOSECAPTURE) {
                                statesToCheck.push_back(actualState);
                                auto newSeq = moves;
                                newSeq.push_back(mv[0]);
                                newSeq.push_back(mv[1]);
                                moveSeq.push_back(newSeq);
                            }
                            else if(actualState->getTP()==actualState->CHOOSEPAWN) {
                                auto newSeq = moves;
                                newSeq.push_back(mv[0]);
                                newSeq.push_back(mv[1]);
                                children.push_back(new DecisionNode(newSeq,actualState,this,depth+1));
                            }
                        actualState = new Checkers(*statesToCheck.front());
                        }
                    }
                    delete actualState;
                    delete statesToCheck.front();
                    statesToCheck.pop_front();
                    moveSeq.pop_front();
                }
            } //king
            delete baseState;
            gameState = new Checkers(*game);
        }//if can be chosen
    }//for each pawn
    delete gameState;
    //if(!children.empty())delete game;
}

//solve memory leaks for the win

std::vector<char> makeDecision(Checkers* game, int levels){
    DecisionTree tree;
    tree.addRoot(game);
    alphaBetaPruning(tree.root(), levels, -1000, 1000);
    std::vector<char>* decision;
    if(tree.root()->move==tree.root()->MAX) {
        int value = -1000;
        for(auto node:tree.root()->children){
            if(node->score&&*node->score>value){
                value=*node->score;
                decision = &node->decision;
            }
        }
    }
    else {
        int value = 1000;
        for(auto node:tree.root()->children){
            if(node->score&&*node->score<value){
                value=*node->score;
                decision = &node->decision;
            }
        }
    }
    return *decision;
}

void alphaBetaPruning(DecisionTree::DecisionNode* node, int levels, int a, int b) {
    if(levels<=node->depth||node->game->gameWon()) {
        node->calculateValue();
        return;
    }
    node->addChildren();
    if(node->move==node->MAX) {
        int value = -1000;
        for(auto& n: node->children) {
            alphaBetaPruning(n,levels,a,b);
            value = std::max(value, *n->score);
            a = std::max(a,value);
            if(b<=a) break;
        }
        node->score = std::unique_ptr<int>(new int(value));
    }
    else {
        int value = 1000;
        for(auto& n: node->children) {
            alphaBetaPruning(n,levels,a,b);
            value = std::min(value, *n->score);
            a = std::min(b,value);
            if(b<=a) break;
        }
        node->score = std::unique_ptr<int>(new int(value));
    }
}