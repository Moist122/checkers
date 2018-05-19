#include"decision_tree.hh"
#include"pawn.hh"
#include"square.hh"

#include<iostream>

DecisionTree::DecisionTree() :_root(nullptr){}
DecisionTree::~DecisionTree() {
    if(!empty()) _root->deleteRecursively();
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
            std::list<Checkers*> statesToCheck;
            std::list<std::vector<char>> moveSeq;
            statesToCheck.push_back(gameState);
            moveSeq.push_back(std::vector<char>{x,y});
                while(!statesToCheck.empty()) {
                    Checkers* actualState = new Checkers(*statesToCheck.front());
                    std::vector<char> moves = moveSeq.front();
                    char x = *(moves.end()-2);
                    char y = *(moves.end()-1);
                    std::list<std::vector<char>> mvs;
                    pawn = actualState->getChosenPawn();
                    if(!pawn->isKing()) {
                        mvs = {{char(x+2),char(y+2)},\
                                {char(x-2),char(y+2)},\
                                {char(x-2),char(y-2)},\
                                {char(x+2),char(y-2)},\
                                {char(x+1),char(y+direction)},\
                                {char(x-1),char(y+direction)}};
                    }
                    else {
                        char directions[4][2] {{1,1},{1,-1},{-1,-1},{-1,1}};
                        for(auto j: directions) {
                            char mult = 1;
                            while(gameState->onBoard(x+mult*j[0],y+mult*j[1])) {
                                mvs.push_back(std::vector<char>{char(x+mult*j[0]),\
                                        char(y+mult*j[1])});
                            ++mult;
                            }
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
    std::vector<char> decision;
    if(tree.root()->whoseMove()==tree.root()->MAX) {
        int value = -1000;
        for(auto node:tree.root()->listChildren()){
            if(node->evaluated()&&node->getScore()>value){
                value=node->getScore();
                decision = node->getDecision();
            }
        }
    }
    else {
        int value = 1000;
        for(auto node:tree.root()->listChildren()){
            if(node->evaluated()&&node->getScore()<value){
                value=node->getScore();
                decision = node->getDecision();
            }
        }
    }
    return decision;
}

void alphaBetaPruning(DecisionTree::DecisionNode* node, int levels, int a, int b) {
    if(levels<=node->getDepth()||node->getGame()->gameWon()) {
        node->calculateValue();
        return;
    }
    node->addChildren();
    if(node->whoseMove()==node->MAX) {
        int value = -1000;
        for(auto& n: node->listChildren()) {
            alphaBetaPruning(n,levels,a,b);
            value = std::max(value, n->getScore());
            a = std::max(a,value);
            if(b<=a) break;
        }
        node->setScore(value);
    }
    else {
        int value = 1000;
        for(auto& n: node->listChildren()) {
            alphaBetaPruning(n,levels,a,b);
            value = std::min(value, n->getScore());
            a = std::min(b,value);
            if(b<=a) break;
        }
        node->setScore(value);
    }
}