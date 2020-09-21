/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Staff.h
 * Author: Matteo
 *
 * Created on 16 settembre 2020, 18:59
 */

#ifndef STAFF_H
#define STAFF_H

#include "Weapon.h"


class Staff : public Weapon{
public:
    Staff(int s=3);

    virtual Staff* clone() const override;

    virtual int use() override;
};

#endif /* STAFF_H */

