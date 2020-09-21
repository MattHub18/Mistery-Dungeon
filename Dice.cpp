/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <ctime>
#include <cstdlib>
#include "Dice.h"

int Dice::numRolls=0;

Dice::Dice(int faces): faces(faces) {
srand(time(0));
}

int Dice::roll(int r) {
    int result=0;
    if((numRolls % maxRolls)==0)
        srand(time(0));
    for (int i = 0; i < r; ++i)
        result+=rand() % faces+1;
    numRolls++;
    return result;
}