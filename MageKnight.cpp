/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "MageKnight.h"
#include "Dice.h"
#include "Weapon.h"

MageKnight::MageKnight(int hp, int m) : Wizard(hp, m) {
}

char MageKnight::getCharacterSymbol() const {
    return 'M';
}

void MageKnight::doMagic() {
    if (getMana() > 4) {
        Weapon* w = this->getWeapon();
        w->setStrength(w->getStrength() + 1);
        setMana(getMana() - 5);
    }
}

int MageKnight::fight(GameCharacter &enemy) {
    Dice* d = new Dice(6);
    GameCharacter* c;
    int damage = 0;
    if (d->roll(1) % 2 == 0) {
        c=new Wizard(8,20);
        damage = c->fight(enemy);
    } else {
        c=new Knight(10);
        damage = c->fight(enemy);
    }
    delete d;
    return damage;
}