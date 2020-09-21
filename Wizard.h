/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wizard.h
 * Author: Matteo
 *
 * Created on 16 settembre 2020, 17:52
 */

#ifndef WIZARD_H
#define WIZARD_H

#include "GameCharacter.h"
#include "Dice.h"

class Wizard : public virtual GameCharacter {
public:
    Wizard(int hp = 8, int m = 20);

    virtual char getCharacterSymbol() const override;

    virtual void doMagic();

    virtual int fight(GameCharacter &enemy) override;
    
    virtual int getMana();
    
    virtual void setMana(int m);

private:
    int mana;
};

#endif /* WIZARD_H */

