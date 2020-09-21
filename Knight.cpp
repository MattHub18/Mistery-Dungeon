/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Knight.h"

Knight::Knight(int hp):GameCharacter(hp){}

char Knight::getCharacterSymbol() const {
    return 'K';
}

int Knight::fight(GameCharacter &enemy) {
    int damage=basicFight(enemy);
    return damage;
}