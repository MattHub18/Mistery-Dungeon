/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dice.h
 * Author: Matteo
 *
 * Created on 16 settembre 2020, 17:47
 */

#ifndef DICE_H
#define DICE_H

class Dice {
public:

    explicit Dice(int faces=6);

    int roll(int r);

private:
    int faces;
    static int numRolls;
    const int maxRolls=5;
};

#endif /* DICE_H */

