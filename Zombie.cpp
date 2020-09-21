/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Zombie.h"

Zombie::Zombie(int hp): GameCharacter(hp) {}

char Zombie::getCharacterSymbol() const {
    return 'Z';
}

int Zombie::fight(GameCharacter &enemy) {
    int damage=basicFight(enemy);
    return damage;
}