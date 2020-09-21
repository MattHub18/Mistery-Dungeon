/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Matteo
 *
 * Created on 16 settembre 2020, 16:51
 */


#include <iostream>
#include <typeinfo>
#include <vector>
#include "Dungeon.h"
#include "GameCharacter.h"
#include "Weapon.h"
#include "Dice.h"
#include "Wizard.h"
#include "Knight.h"
#include "Zombie.h"
#include "Staff.h"
#include "Sword.h"
#include "MageKnight.h"

enum class GameEvent {
    quit, up, left, down, right, fight, noop
};

GameEvent getEvent() {
    char c;
    while (std::cin >> c) {
        std::cin.ignore(100, '\n');
        switch (c) {
            case 'Q':
                return GameEvent::quit;
            case 'w':
                return GameEvent::up;
            case 'a':
                return GameEvent::left;
            case 's':
                return GameEvent::down;
            case 'd':
                return GameEvent::right;
            case 'f':
                return GameEvent::fight;
            default:
                return GameEvent::noop;
        }
    }
    return GameEvent::noop;
}

bool isLegalCell(int x, int y, const Dungeon &map) {
    switch (map.getCell(x, y)) {
        case TileType::Unused:
            return false;
        case TileType::Wall:
            return false;
        case TileType::Floor:
            return true;
        default:
            return false;
    };
}

bool findFreeMapTile(int &x, int &y, const Dungeon &map, std::vector<GameCharacter*> &gameCharacters) {
    for (int i = x; i < map.getXsize(); i++) {
        for (int j = y; j < map.getYsize(); j++) {
            if (map.getCell(i, j) == TileType::Floor) {
                x = i;
                y = j;

                for (auto gc : gameCharacters) {
                    if (gc->getPosY() == y && gc->getPosX() == x)
                        return false;
                }

                return true;
            }
        }
    }
    return false;
}

bool checkEnemyPositions(int heroX, int heroY, std::vector<GameCharacter*> &enemies) {
    bool result = false;
    for (auto enemy : enemies) {
        if (heroX == enemy->getPosX() && heroY == enemy->getPosY())
            result = true;
    }
    return result;
}

GameCharacter& selectEnemy(GameCharacter &hero, std::vector<GameCharacter*> &enemies) {
    int maxDistance = 1;
    for (auto enemy : enemies)
        if ((abs(hero.getPosX() - enemy->getPosX()) <= maxDistance) || (abs(hero.getPosX() - enemy->getPosY()) <= maxDistance))
            return *enemy;
    return *(new Zombie(50));
}

bool isLegalMove(GameCharacter &hero, int dX, int dY, const Dungeon &map, std::vector<GameCharacter*> &enemies) {
    int newX = hero.getPosX() + dX;
    int newY = hero.getPosY() + dY;
    bool enemyPos = checkEnemyPositions(newX, newY, enemies);
    return (isLegalCell(newX, newY, map) && !enemyPos);
}

bool updateGame(const GameEvent &gameEvent, GameCharacter &hero, std::vector<GameCharacter*> &enemies,
        const Dungeon &map) {
    switch (gameEvent) {
        case GameEvent::quit: //
            return true;
        case GameEvent::down:
        {
            if (isLegalMove(hero, 1, 0, map, enemies))
                hero.move(1, 0);
            break;
        }
        case GameEvent::right:
        {
            if (isLegalMove(hero, 0, 1, map, enemies))
                hero.move(0, 1);
            break;
        }
        case GameEvent::up:
        {
            if (isLegalMove(hero, -1, 0, map, enemies))
                hero.move(-1, 0);
            break;
        }
        case GameEvent::left:
        {
            if (isLegalMove(hero, 0, -1, map, enemies))
                hero.move(0, -1);
            break;
        }
        case GameEvent::fight:
        {
            GameCharacter &selectedEnemy = selectEnemy(hero, enemies);
            if (selectedEnemy.getHP() != 50) {
                if (hero.isLegalFight(selectedEnemy, 1)) {
                    std::cout << "Fight" << std::endl;

                    int result = hero.fight(selectedEnemy);
                    if (result) {
                        std::cout << "Enemy hit ! (HP: " << selectedEnemy.getHP() << ")" << std::endl;
                        if (selectedEnemy.getHP() <= 0)
                            std::cout << "Enemy is dead." << std::endl;
                    } else
                        std::cout << "Hit missed..." << std::endl;
                    int result1 = selectedEnemy.fight(hero);
                    if (result1) {
                        std::cout << "You were hit ! (HP: " << hero.getHP() << ")" << std::endl;
                        if (hero.getHP() <= 0)
                            std::cout << "You were dead." << std::endl;
                    } else
                        std::cout << "Hit missed..." << std::endl;
                } else
                    std::cout << "Enemy too far, can not fight" << std::endl;
            } else
                std::cout << "Enemy too far, can not fight" << std::endl;
            break;
        }
        case GameEvent::noop:
        {
            std::cout << "Press: w,a,s,d,f or Q to quit." << std::endl;
            break;
        }
    }
    return false;
}

void renderHUD(GameCharacter &hero) {
    std::cout << "Press: w,a,s,d,f or Q to quit." << std::endl;
    std::cout << "Hero - HP: " << hero.getHP();
    if (hero.getWeapon() != nullptr)
        std::cout << " - Weapon strength: " << hero.getWeapon()->getStrength();
    std::cout << " - Hero type:";
    if (typeid (hero) == typeid (Knight))
        std::cout << " Knight.";
    else if (typeid (hero) == typeid (Wizard))
        std::cout << " Wizard.";
    else if (typeid (hero) == typeid (MageKnight))
        std::cout << " MageKnight.";
    else
        std::cout << " Unknown.";
    std::cout << std::endl;
}

bool checkMonsterPosition(int x, int y, std::vector<GameCharacter*> &enemies, char &renderSymbol) {
    for (auto enemy : enemies) {
        if (enemy->getHP() <= 0)
            return false;
        if (x == enemy->getPosX() && y == enemy->getPosY()) {
            renderSymbol = enemy->getCharacterSymbol();
            return true;
        }
    }
    return false;
}

void renderGame(Dungeon &map, GameCharacter &hero, std::vector<GameCharacter*> &enemies) {
    for (int x = 0; x < map.getXsize(); x++) {
        for (int y = 0; y < map.getYsize(); y++) {
            char renderSymbol = ' ';
            if (x == hero.getPosX() && y == hero.getPosY())
                std::cout << hero.getCharacterSymbol();
            else if (checkMonsterPosition(x, y, enemies, renderSymbol))
                std::cout << renderSymbol;
            else {
                std::string tileSymbol = TileTypeToTileString(map.getCell(x, y));
                std::cout << tileSymbol;
            }
        }
        std::cout << std::endl;
    }
}

GameCharacter* chooseCharacter(GameCharacter *hero) {
    std::cout << "Welcome! Your goal is to defeat all enemies." << std::endl;
    std::cout << "Please, choose your character." << std::endl;
    std::cout << "Wizard has low hp but he can do magic tricks afar with his staff. Type w" << std::endl;
    std::cout << "Knight kills everyone with his mythical sword Caliber. Type k" << std::endl;
    std::cout << "Nobody can match MageKnight strength. Type m" << std::endl;
    char a = 0;
    std::cin>> a;
    Weapon* weapon;
    if (a == 'w') {
        hero = new Wizard();
        weapon = new Staff();
        hero->setWeapon(weapon);
    } else if (a == 'k') {
        hero = new Knight();
        weapon = new Sword();
        hero->setWeapon(weapon);
    } else if (a == 'm') {
        hero = new MageKnight();
        Dice* d = new Dice();
        if (d->roll(1) % 2)
            weapon = new Staff();
        else
            weapon = new Sword();
        hero->setWeapon(weapon);
        delete d;
    }
    return hero;
}

std::vector<GameCharacter*> createMonsters(int startX, int startY, int numMonsters, const Dungeon &map) {
    std::vector<GameCharacter*> result;
    result.reserve(numMonsters);
    Dice relPositionDispl(10);

    for (int i = 0; i < numMonsters; i++) {
        GameCharacter* enemy = new Zombie();
        Weapon* weapon = new Sword(1);
        enemy->setWeapon(weapon);

        int flipSearch = 0;
        bool positionFound = false;
        int monsterPositionX = startX;
        int monsterPositionY = startY;
        while (!positionFound) {
            if (flipSearch % 7 == 0) {
                monsterPositionX = startX + 1;
                monsterPositionY = startY + 1;
            }
            if (flipSearch % 2) {
                monsterPositionX += relPositionDispl.roll(1 + flipSearch);
                monsterPositionY += relPositionDispl.roll(1 + flipSearch);
                flipSearch++;
            } else {
                monsterPositionX -= relPositionDispl.roll(1 + flipSearch);
                monsterPositionY -= relPositionDispl.roll(1 + flipSearch);
                flipSearch++;
            }
            if (monsterPositionX < 0 || monsterPositionX > map.getXsize())
                monsterPositionX = startX + 1;
            if (monsterPositionY < 0 || monsterPositionY > map.getYsize())
                monsterPositionY = startY + 1;
            positionFound = findFreeMapTile(monsterPositionX, monsterPositionY, map, result);
            if (monsterPositionX == startX && monsterPositionY == startY)
                positionFound = false;
        }
        enemy->setPosX(monsterPositionX);
        enemy->setPosY(monsterPositionY);
        result.push_back(enemy);
    }
    return result;
}

int loadLevel(GameCharacter *hero) {
    Dungeon map;
    map.createDungeon();
    int startX = 0;
    int startY = 0;
    int NUM_MONSTERS = 4;
    std::vector<GameCharacter*>enemies = createMonsters(startX, startY, NUM_MONSTERS, map);
    while (!findFreeMapTile(startX, startY, map, enemies)) {
        startX += 2;
        startY += 2;
    }

    hero->setPosX(startX);
    hero->setPosY(startY);
    renderHUD(*hero);
    renderGame(map, *hero, enemies);
    int count = NUM_MONSTERS;
    while (true) {
        GameEvent gameEvent = getEvent();
        bool quit = updateGame(gameEvent, *hero, enemies, map);
        if (quit)
            return 0;
        if (hero->getHP() <= 0) {
            std::cout << "Game Over!" << std::endl;
            return 1;
        }
        for (auto enemy=enemies.begin(); enemy<enemies.end();enemy++) {
            if ((*enemy)->getHP() <= 0) {
                enemies.erase(enemy);
                count--;
            }
        }
        if (count == 0)
            return 0;
        renderHUD(*hero);
        renderGame(map, *hero, enemies);
    }
    return 1;
}

void display() {
    std::cout << "## ##   #   #####   #####   #####   ####    #   #                " << std::endl;
    std::cout << "# # #   #   #         #     #       #   #    # #                 " << std::endl;
    std::cout << "# # #   #   #####     #     #####   ####      #                  " << std::endl;
    std::cout << "#   #   #       #     #     #       #  #      #                  " << std::endl;
    std::cout << "#   #   #   #####     #     #####   #   #     #                  " << std::endl;
    std::cout << "" << std::endl;
    std::cout << "            ###     #   #   #   #   #####   #####   #####   #   #" << std::endl;
    std::cout << "            #  #    #   #   ##  #   #       #       #   #   ##  #" << std::endl;
    std::cout << "            #   #   #   #   # # #   #  ##   #####   #   #   # # #" << std::endl;
    std::cout << "            #  #    #   #   #  ##   #   #   #       #   #   #  ##" << std::endl;
    std::cout << "            ###     #####   #   #   #####   #####   #####   #   #" << std::endl;
}

int main() {
    display();
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Press s to start" << std::endl;
    char s = 0;
    std::cin>>s;
    GameCharacter* hero;
    hero = chooseCharacter(hero);
    if (loadLevel(hero) == 0) {
        std::cout << "You Win! Congratulations" << std::endl;
    }
    std::cout << "Press e to exit" << std::endl;
    char e = 0;
    std::cin>>e;
    return 0;
}
