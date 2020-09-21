/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sword.h
 * Author: Matteo
 *
 * Created on 16 settembre 2020, 18:50
 */

#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"

class Sword: public Weapon {
public:
   Sword(int s=4);

    virtual Sword* clone() const override;

   virtual int use() override;
};

#endif /* SWORD_H */

