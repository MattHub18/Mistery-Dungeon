/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sword.h"

Sword::Sword(int s) : Weapon(s){}

Sword *Sword::clone() const {
    return new Sword(*this);
}

int Sword::use() {
    int result=0;
    result+=basicUse();
    return result;
}
