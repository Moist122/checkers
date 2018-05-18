#pragma once
#include<memory>
#include<list>
#include<vector>
#include"checkers.hh"

class DecisionTree {
    //a class representing tree used by alpha-beta pruning algorithm to choose
    //the best move
public:
    DecisionTree(); //initialize empty tree
    ~DecisionTree();
    void addRoot(Checkers* game); //add root node holding copy of game
    bool empty() {return _root==nullptr;} //check if tree is empty
    class DecisionNode;
    DecisionNode* root() {return _root;} //get foor of the tree
private:
    DecisionNode* _root; //first node of the tree
};

class DecisionTree::DecisionNode {
    //node of a decision tree
public:
    DecisionNode(Checkers* g); //create root node with game state
    DecisionNode(std::vector<char> dec, Checkers* g, DecisionNode* p, int d);
        //create decision node which is a result of decision dec, holding game g,
        //it is a child of p and its depth is d
    ~DecisionNode();
    enum Player {MIN, MAX}; //minimazing and maximizing player
    void addChildren();
        // add nodes representing aftermath of game state of this node
    bool evaluated() //does this node have assigned value?
        {return score!=nullptr;}
    int getScore() //value assigned to the node
        {return *score;}
    void setScore(int s) //change score of node
        {score=std::unique_ptr<int>(new int(s));}
    std::vector<char>& getDecision() //get decision of the node
        {return decision;}
    char getDepth() //get depth of the node
        {return depth;}
    Checkers* getGame() //get game in node
        {return game;}
    void calculateValue(); //get value of the node according to heuristic
    void deleteRecursively(); //delete all the children, then this node
    std::list<DecisionNode*>& listChildren() //get list of children of this node
        {return children;}
    Player whoseMove() //return current player
        {return move;}
private:
    Checkers* game; //state of the game
    std::vector<char> decision; //decision required to cause game state
    Player move; //current player
    DecisionNode* parent; //parent node
    std::list<DecisionNode*> children; //children of this node
    std::unique_ptr<int> score;
        //score of the node, nullptr if it hasn't been evaluated
    char depth; //depth in tree
};

std::vector<char> makeDecision(Checkers* game, int levels);
    //choose optimal move considering levels moves ahead
void alphaBetaPruning(DecisionTree::DecisionNode*, int, int, int);
    //alpha beta pruning algorithm