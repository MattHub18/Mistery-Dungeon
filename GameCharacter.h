/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameCharacter.h
 * Author: Matteo
 *
 * Created on 16 settembre 2020, 16:53
 */



#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "Weapon.h"

class GameCharacter {
public:
    GameCharacter();

    explicit GameCharacter(int hp);

    virtual ~GameCharacter()=0;

    GameCharacter(const GameCharacter &that);

    GameCharacter &operator=(const GameCharacter &that);

    int getHP() const;

    void setHP(int HP);

    int getPosX() const;

    void setPosX(int PosX);

    int getPosY() const;

    void setPosY(int PosY);

    Weapon *getWeapon() const;

    void setWeapon(Weapon *weapon);

    virtual char getCharacterSymbol() const;

    virtual void move(int x, int y);

    virtual int fight(GameCharacter &enemy)=0;

    static int l1Distance(const GameCharacter &p, const GameCharacter &q);

    bool isLegalFight(GameCharacter &enemy, int maxDistance);

    virtual int receiveDamage(int points);
    
private:
    int HP;
    int PosX;
    int PosY;
    Weapon* weapon;
protected:
    int basicFight(GameCharacter &enemy);
};

#endif /* GAMECHARACTER_H */