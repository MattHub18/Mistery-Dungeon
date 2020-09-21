/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Wizard.h"

Wizard::Wizard(int hp, int m):GameCharacter(hp),mana(m) {}

char Wizard::getCharacterSymbol() const {
    return 'W';
}

void Wizard::doMagic() {
if(mana>7)
   if(getHP()<=4 && getHP()>0) {
       setHP(getHP() + 2);
       mana-=8;
   }
}

int Wizard::fight(GameCharacter &enemy) {
    int damage = 0;
    Dice* d=new Dice();
    if (mana > 0 && d->roll(1)==6) {
        damage += basicFight(enemy);
        damage += basicFight(enemy);
        mana--;
    } else {
    damage = basicFight(enemy);
    enemy.receiveDamage(damage);
}
    delete d;
    return damage;
}

int Wizard::getMana(){
    return mana;
}

void Wizard::setMana(int m){
    mana=m;
}