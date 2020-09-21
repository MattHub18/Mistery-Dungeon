/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Weapon.h
 * Author: Matteo
 *
 * Created on 16 settembre 2020, 16:56
 */

#ifndef WEAPON_H
#define WEAPON_H

class Weapon {
public:
    Weapon();

    explicit Weapon(int strength);

    virtual ~Weapon()=0;

    virtual Weapon* clone() const=0;

    int getStrength() const;
    
    void setStrength(int s);

    virtual int use()=0;

private:
    int strength;
    
protected:
    virtual int basicUse();
};

#endif /* WEAPON_H */

