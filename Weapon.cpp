/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Weapon.h"

Weapon::Weapon(int strength):strength(strength) {}

Weapon::Weapon():Weapon(3) {}

Weapon::~Weapon() {}

int Weapon::getStrength() const {
    return strength;
}

void Weapon::setStrength(int s){
    strength=s;
}

int Weapon::basicUse() {
    int result=strength;
    return result;
}






