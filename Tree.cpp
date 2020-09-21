/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Tree.h"
#include <iostream>
#include <ctime>

Tree::Tree(int xMax, int yMax) : xMax(xMax), yMax(yMax), oldseed(0), xMin(7), yMin(7) {
    head = buildNode(0,0,xMax-1,yMax-1,nullptr);
}

Tree::~Tree() {
    if (head)
        delete head;
}

Node* Tree::getHead() {
    return head;
}

int Tree::getRand(int min, int max) {
    long seed = time(NULL) + oldseed;
    oldseed = seed;

    srand(seed);
    int n = max - min + 1;
    int i = rand() % n;
    if (i < 0)
        i = -i;
    return min + i;
}

Node* Tree::buildNode(int x_i, int y_i, int x_f, int y_f, Node* t) {
    Node* n = new Node;
    n->xi = x_i;
    n->yi = y_i;
    n->xf = x_f;
    n->yf = y_f;
    n->top = t;
    n->left=nullptr;
    n->right=nullptr;
    n->slice=' ';
    return n;
}

bool Tree::buildTree(Node* current) {
    int slice = 0;
    int s=0;
    Node* sx = nullptr;
    Node* dx = nullptr;
    if(current->xf-current->xi - 2*xMin < 1 && current->yf-current->yi - 2*yMin < 1){
        return false;
    }else if (current->yf-current->yi - 2*yMin < 1) {
        slice = 0;
    } else if (current->xf-current->xi - 2*xMin < 1) {
        slice = 1;
    } else {
        slice = getRand(0, 1);
    }
    if (slice) {//verticale
        s = getRand(yMin+current->yi, current->yf - yMin-1);
        sx = buildNode(current->xi, current->yi, current->xf, s, current);
        dx = buildNode(current->xi, s, current->xf, current->yf, current);
        current->slice='v';
    } else {//orizzontale
        s = getRand(xMin+current->xi, current->xf - xMin-1);
        sx = buildNode(current->xi, current->yi, s, current->yf, current);
        dx = buildNode(s, current->yi, current->xf, current->yf, current);
        current->slice='o';
    }
    current->left = sx;
    current->right = dx;
    buildTree(sx);
    buildTree(dx);
    return true;
}