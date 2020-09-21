/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MageKnight.h
 * Author: Matteo
 *
 * Created on 16 settembre 2020, 17:52
 */

#ifndef MAGEKNIGHT_H
#define MAGEKNIGHT_H

#include "Knight.h"
#include "Wizard.h"

class MageKnight: public Knight, public Wizard{
    public:
    MageKnight(int hp = 12, int m = 30);

    virtual char getCharacterSymbol() const override;

    virtual void doMagic() override;

    virtual int fight(GameCharacter &enemy) override;

};

#endif /* MAGEKNIGHT_H */

