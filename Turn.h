#pragma once

#include <iostream>

class Turn {
private:
    int money;

public:
    Turn() = default;

    Turn(int money_) : money{money_} {}

    const int getMoney() { return money; }

    void Blind(int amount) {
        money -= amount;
    }

    bool Call(int bet, int alreadyBet) {
        if(money - bet + alreadyBet >= 0) {
            money -= bet - alreadyBet;
            return true;
        }
        else {
            money = 0;
            return false;
        }

    }

    bool Raise(int raiseValue) {
        if(money >= raiseValue) {
            money -= raiseValue;
            return true;
        }
        else {
            std::cout << "You can't raise by that amount!\n";
            return false;
        }
    }

    void Won(int amount) {
        money += amount;
    }
};