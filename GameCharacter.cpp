/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GameCharacter.h"
#include "Dice.h"
#include <iostream>

GameCharacter::GameCharacter(int hp) : HP(hp), PosX(0), PosY(0), weapon(nullptr) {
    
}

GameCharacter::GameCharacter() : GameCharacter(10) {
}

GameCharacter::~GameCharacter() {
    if (weapon != nullptr)
        delete weapon;
}

GameCharacter::GameCharacter(const GameCharacter &that) {
    HP = that.HP;
    PosX = that.PosX;
    PosY = that.PosY;
    if (that.weapon != nullptr)
        weapon = that.weapon->clone();
    else
        weapon = nullptr;
}

GameCharacter &GameCharacter::operator=(const GameCharacter &that) {
    if (this != &that) {
        if (weapon != nullptr)
            delete weapon;

        HP = that.HP;
        PosX = that.PosX;
        PosY = that.PosY;
        if (that.weapon != nullptr)
            weapon = that.weapon->clone();
        else
            weapon = nullptr;
    }
    return *this;
}

int GameCharacter::getHP() const {
    return HP;
}

void GameCharacter::setHP(int HP) {
    this->HP = HP;
}

int GameCharacter::getPosX() const {
    return PosX;
}

void GameCharacter::setPosX(int PosX) {
    GameCharacter::PosX = PosX;
}

int GameCharacter::getPosY() const {
    return PosY;
}

void GameCharacter::setPosY(int PosY) {
    GameCharacter::PosY = PosY;
}

Weapon *GameCharacter::getWeapon() const {
    return weapon;
}

void GameCharacter::setWeapon(Weapon *weapon) {
    this->weapon = weapon;
}

char GameCharacter::getCharacterSymbol() const {
    return 'C';
}

void GameCharacter::move(int x, int y) {
    PosX += x;
    PosY += y;
}

int GameCharacter::l1Distance(const GameCharacter &p, const GameCharacter &q) {
    int distance = abs(p.PosX - q.PosX) + abs(p.PosY - q.PosY);
    return distance;
}

bool GameCharacter::isLegalFight(GameCharacter &enemy, int maxDistance) {
    if ((abs(PosX - enemy.PosX) <= maxDistance) || (abs(PosY - enemy.PosY) <= maxDistance))
        return true;
    return false;
}

int GameCharacter::receiveDamage(int points) {
    if (points < 0)
        points = 1;
    HP -= points;
    return points;
}

int GameCharacter::basicFight(GameCharacter &enemy) {
    Dice* d = new Dice(6);
    int hit = 1;
    if (weapon)
        hit = weapon->use();
    int hitChance = d->roll(2);
    int damage = 0;
    if (hitChance >= 7)
        damage = enemy.receiveDamage(hit);
    delete d;
    return damage;
}