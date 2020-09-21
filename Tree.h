/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tree.h
 * Author: Matteo
 *
 * Created on 17 settembre 2020, 13:36
 */

#ifndef TREE_H
#define TREE_H

#include <vector>
using namespace std;

struct Node{
    int xi;
    int yi;
    int xf;
    int yf;
    Node* top;
    Node* left;
    Node* right;
    char slice;
};

class Tree{
public:
    Tree(int xMax, int yMax);
    ~Tree();
    Node* getHead();
    bool buildTree(Node* current);
    int getRand(int min, int max);
    
private:
    Node* buildNode(int x_i, int y_i,int x_f, int y_f, Node* t);
    
    Node* head;
    int xMax;
    int yMax;
    long oldseed;
    int xMin;
    int yMin;
};


#endif /* TREE_H */

