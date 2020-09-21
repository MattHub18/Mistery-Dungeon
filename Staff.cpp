/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Staff.h"
#include "Dice.h"

Staff::Staff(int s) : Weapon(s) {}

Staff *Staff::clone() const {
    return new Staff(*this);
}

int Staff::use() {
    Dice* d=new Dice(6);
    int result=basicUse()+(d->roll(2)%3+1);
    delete d;
    return result;
}