/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Dungeon.h"

Dungeon::Dungeon() : xmax(25), ymax(80) {
    dungeonMap = nullptr;
    t = nullptr;
}

Dungeon::~Dungeon() {

    for (int i = 0; i < xmax; i++)
        delete[] dungeonMap[i];
    delete[] dungeonMap;
}

TileType Dungeon::getCell(int x, int y) const {
    return dungeonMap[x][y];
}

int Dungeon::getXsize() const {
    return xmax;
}

int Dungeon::getYsize() const {
    return ymax;
}

void Dungeon::buildRoom(Node* room) {
    for (int i = room->xi; i < room->xf; i++) {
        for (int j = room->yi; j < room->yf; j++) {
            if (i == room->xi || j == room->yi || i == room->xf - 1 || j == room->yf - 1)
                dungeonMap[i][j] = TileType::Wall;
            else
                dungeonMap[i][j] = TileType::Floor;
        }
    }
}

void Dungeon::buildCorridor(Node* from, Node* to) {
    int mn;
    int mx;
    int door;

    if (from->top->slice == 'v') {//caso 1: corridoio orizzontale
        mn = max(from->xi, to->xi);
        mx = min(from->xf, to->xf);
        door = t->getRand(mn, mx);
        if (from->yf != ymax - 1) {
            while (dungeonMap[door ][from->yf - 2] == TileType::Wall || dungeonMap[door ][from->yf + 1] == TileType::Wall) {
                door = (door + 1) % mx;
            }
            dungeonMap[door][from->yf - 1] = TileType::Floor;
            dungeonMap[door][to->yi] = TileType::Floor;
        }
    } else {//caso 2: corridoio verticale
        mn = max(from->yi, to->yi);
        mx = min(from->yf, to->yf);
        door = t->getRand(mn, mx);

        if (from->xf != xmax - 1) {
            while (dungeonMap[from->xf - 2][door ] == TileType::Wall || dungeonMap[from->xf + 1][door ] == TileType::Wall) {
                door = (door + 1) % mx;
            }
            dungeonMap[from->xf - 1][door] = TileType::Floor;
            dungeonMap[to->xi][door] = TileType::Floor;
        }
    }
}

bool Dungeon::isLegalCell(int x, int y) {
    return dungeonMap[x][y] == TileType::Floor;
}

bool Dungeon::createDungeon() {
    dungeonMap = new TileType*[xmax];
    for (int i = 0; i < xmax; ++i)
        dungeonMap[i] = new TileType[ymax];
    t = new Tree(xmax, ymax);
    if (t->buildTree(t->getHead())) {
        makeRoom(t->getHead());
        makeCorridor(t->getHead());
        delete t;
        return true;
    }
    delete t;
    return false;
}

void Dungeon::makeCorridor(Node* current) {
    if (current != nullptr)
        if (current->left != nullptr) {
            buildCorridor(current->left, current->right);
            makeCorridor(current->left);
            makeCorridor(current->right);

        }
}

void Dungeon::makeRoom(Node* current) {
    if (current->left != nullptr) {
        makeRoom(current->left);
        makeRoom(current->right);
    } else
        buildRoom(current);
}

