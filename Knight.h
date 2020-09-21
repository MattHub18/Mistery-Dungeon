/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Knight.h
 * Author: Matteo
 *
 * Created on 16 settembre 2020, 17:52
 */

#ifndef KNIGHT_H
#define KNIGHT_H

#include "GameCharacter.h"

class Knight : public virtual GameCharacter {
public:
    Knight(int hp = 10);

    virtual char getCharacterSymbol() const override;

    virtual int fight(GameCharacter &enemy) override;

};


#endif /* KNIGHT_H */

