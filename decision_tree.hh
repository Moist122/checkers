#pragma once
#include<memory>
#include<list>
#include<vector>
#include"checkers.hh"

class DecisionTree {
public:
    //DecisionTree(char levels, Checkers* game);
    DecisionTree();
    ~DecisionTree();
    void addRoot(Checkers* game);
    bool empty() {return _root==nullptr;}
    class DecisionNode;
    DecisionNode* root() {return _root;}
    //std::vector<char> makeDecision();
private:
    DecisionNode* _root;
};

class DecisionTree::DecisionNode {
public:
    DecisionNode(Checkers* g);
    DecisionNode(std::vector<char> dec, Checkers* g, DecisionNode* p, int d);
    ~DecisionNode();
    void addChildren();
    bool evaluated()
        {return score!=nullptr;}
    int getScore() 
        {return *score;}
    void calculateValue();
    //std::vector<char> makeDecision(int a, int b);
    void deleteRecursively();
    std::list<DecisionNode*>& listChildren() {return children;}
    enum Player {MIN, MAX};
//private:
    Checkers* game;
    std::vector<char> decision;
    Player move;
    DecisionNode* parent;
    std::list<DecisionNode*> children;
    std::unique_ptr<int> score;
    char depth;
};

std::vector<char> makeDecision(Checkers* game, int levels);
void alphaBetaPruning(DecisionTree::DecisionNode*, int, int, int);