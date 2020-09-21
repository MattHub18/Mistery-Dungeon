/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Zombie.h
 * Author: Matteo
 *
 * Created on 19 settembre 2020, 15:12
 */

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "GameCharacter.h"

class Zombie: public GameCharacter {
public:
    Zombie(int hp=10);

    virtual char getCharacterSymbol()const override;

    virtual int fight(GameCharacter &enemy) override;
};


#endif /* ZOMBIE_H */

