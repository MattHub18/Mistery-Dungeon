/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dungeon.h
 * Author: Matteo
 *
 * Created on 16 settembre 2020, 19:07
 */

#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>
#include "Tree.h"
#include <vector>

enum class TileType {
    Unused = 0, Wall, Floor
};


static std::string TileTypeToTileString(const TileType& tile) {
    switch (tile) {
        case TileType::Unused:
            return " ";
        case TileType::Wall:
            return "#";
        case TileType::Floor:
            return ".";
        default:
            return "";
    };
}

using namespace std;

class Dungeon {
public:
    Dungeon();
    ~Dungeon();
    bool createDungeon();
    TileType getCell(int x, int y) const;
    int getXsize() const;
    int getYsize() const;

private:
    
    void buildRoom(Node* room);
    void buildCorridor(Node* from, Node* to);
    void makeCorridor(Node* current);
    void makeRoom(Node* current);
    bool isLegalCell(int x, int y);
    
    TileType** dungeonMap;
    Tree* t;
    
    const int xmax;
    const int ymax;
};


#endif /* DUNGEON_H */

