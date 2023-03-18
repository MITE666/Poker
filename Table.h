#include <vector>
#include "Player.h"
#include "FlopTurnRiver.h"
#include "Combination.h"
#include "Bot.h"

class Table {
private:
    std::map<std::string, int> combinations = {
            std::make_pair("High Card", 0), std::make_pair("Pair", 1),
            std::make_pair("Two Pair", 2), std::make_pair("Three of a Kind", 3),
            std::make_pair("Straight", 4), std::make_pair("Flush", 5),
            std::make_pair("Full House", 6), std::make_pair("Four of a Kind", 7),
            std::make_pair("Straight Flush", 8), std::make_pair("Royal Flush", 9),
    };
    std::map <std::string, int> numberValue = {
            std::pair <std::string, int> ("Two", 0), std::pair <std::string, int> ("Three", 1),
            std::pair <std::string, int> ("Four", 2), std::pair <std::string, int> ("Five", 3),
            std::pair <std::string, int> ("Six", 4), std::pair <std::string, int> ("Seven", 5),
            std::pair <std::string, int> ("Eight", 6), std::pair <std::string, int> ("Nine", 7),
            std::pair <std::string, int> ("Ten", 8), std::pair <std::string, int> ("Jack", 9),
            std::pair <std::string, int> ("Queen", 10), std::pair <std::string, int> ("King", 11),
            std::pair <std::string, int> ("Ace", 12)
    };
    Player player;
    std::vector<Bot> bots;
    Deck deck;
    int startingMoney;
    FlopTurnRiver ftr;

public:
    Table(Deck& deck_, int money_) : player{Player(deck_, money_)}, deck{deck_}, startingMoney{money_}, ftr{FlopTurnRiver(deck_)} {
        for(int i = 0; i < 5; ++i) {
            bots.emplace_back(deck_, money_);
        }
    }

    void Gameplay() {
        while(player.getTurn().getMoney() > 0 && !bots.empty()) {
            deck.deckReset();
            player = Player(deck, player.getTurn().getMoney());
            for(auto & bot : bots)
                bot = Bot(deck, bot.getTurn().getMoney());
            std::cout << "Money:\nPlayer: " << player.getTurn().getMoney() << "\n";
            for(int i = 0; i < bots.size(); ++i)
                std::cout << "Bot number " << i << ": " << bots[i].getTurn().getMoney() << "\n";
            int bank = 0;
            std::array<Card, 5> tableCards;
            std::string answer;
            std::cout << "Your cards are:\n" << player.getHand()[0] << player.getHand()[1];
            player.getTurn().Blind(startingMoney / 10);
            bank += startingMoney / 10;
            for(auto & bot : bots) {
                bot.getTurn().Blind(startingMoney / 10);
                bank += startingMoney / 10;
            }
            std::array<Card, 3> flop = ftr.Flop();
            for(int i = 0; i < 3; ++i)
                tableCards[i] = flop[i];
            std::cout << "Do you want to Check or Raise?\n";
            std::cin >> answer;
            if(answer == "Raise") {
                std::cout << "Raise by what amount?\n";
                int amount;
                std::cin >> amount;
                if(player.getTurn().Raise(amount)) {
                    bank += amount;
                }
                else {
                    std::cout << "Raise by what amount?\n";
                    std::cin >> amount;
                    bank += amount;
                }
                for(auto & bot : bots) {
                    if(bot.getTurn().Call(amount, 0))
                        bank += amount;
                    else
                        bank += bot.getTurn().getMoney();
                }
            }
            tableCards[3] = ftr.Turn();
            std::cout << "Do you want to Check or Raise?\n";
            std::cin >> answer;
            if(answer == "Raise") {
                std::cout << "Raise by what amount?\n";
                int amount;
                std::cin >> amount;
                if(player.getTurn().Raise(amount)) {
                    bank += amount;
                }
                else {
                    std::cout << "Raise by what amount?\n";
                    std::cin >> amount;
                    bank += amount;
                }
                for(auto & bot : bots) {
                    if(bot.getTurn().Call(amount, 0))
                        bank += amount;
                    else
                        bank += bot.getTurn().getMoney();
                }
            }
            tableCards[4] = ftr.River();
            std::cout << "Do you want to Check or Raise?\n";
            std::cin >> answer;
            if(answer == "Raise") {
                std::cout << "Raise by what amount?\n";
                int amount;
                std::cin >> amount;
                if(player.getTurn().Raise(amount)) {
                    bank += amount;
                }
                else {
                    std::cout << "Raise by what amount?\n";
                    std::cin >> amount;
                    bank += amount;
                }
                for(auto & bot : bots) {
                    if(bot.getTurn().Call(amount, 0))
                        bank += amount;
                    else
                        bank += bot.getTurn().getMoney();
                }
            }
            std::array<Card, 7> cards;
            for(int i = 0; i < 5; ++i)
                cards[i] = tableCards[i];
            cards[5] = player.getHand()[0];
            cards[6] = player.getHand()[1];
            Combination combination(cards);
            std::pair<std::string, Card> combo = combination.CheckCombination();
            std::cout << "You have: " << combo.first << "\n";
            int playerPoints = combinations[combo.first];
            std::vector<int> botsPoints;
            for(int i = 0; i < (int)bots.size(); ++i) {
                cards[5] = bots[i].getHand()[0];
                cards[6] = bots[i].getHand()[1];
                combination = Combination(cards);
                combo = combination.CheckCombination();
                std::cout << "Bot number " << i << " had:\n" << bots[i].getHand()[0] << bots[i].getHand()[1];
                std::cout << "He has: " << combo.first << "\n";
                botsPoints.push_back(combinations[combo.first]);
            }
            int maxim = playerPoints;
            int maximBots = 0;
            for(int botsPoint : botsPoints) {
                if(botsPoint > maximBots) {
                    maximBots = botsPoint;
                }
            }
            if(maxim > maximBots) {
                player.getTurn().Won(bank);
                std::cout << "Congratulations! You Won " << bank << "$ on your credit card )) \n";
            }
            else if(maximBots > maxim) {
                for(int i = 0; i < (int)bots.size(); ++i)
                    if(botsPoints[i] == maximBots) {
                        std::cout << "Bot number " << i << " has won " << bank << "$ on his credit card )))\n";
                        bots[i].getTurn().Won(bank);
                        break;
                    }
            }
            else {
                int imax = 0;
                for(int i = 0; i < (int)bots.size(); ++i)
                    if(botsPoints[i] == maxim) {
                        imax = i;
                        break;
                    }
                cards[5] = player.getHand()[0];
                cards[6] = player.getHand()[1];
                combination = Combination(cards);
                playerPoints = numberValue[combination.CheckCombination().second.getNumber()];
                cards[5] = bots[imax].getHand()[0];
                cards[6] = bots[imax].getHand()[1];
                combination = Combination(cards);
                int botPoints = numberValue[combination.CheckCombination().second.getNumber()];
                if(playerPoints > botPoints) {
                    player.getTurn().Won(bank);
                    std::cout << "Congratulations! You Won " << bank << "$ on your credit card )) \n";
                }
                else if(playerPoints < botPoints) {
                    std::cout << "Bot number " << imax << " has won " << bank << "$ on his credit card )))\n";
                    bots[imax].getTurn().Won(bank);
                }
                else {
                    std::cout << "It's a draw!\n";
                    player.getTurn().Won(bank / 2);
                    bots[imax].getTurn().Won(bank / 2);
                }
            }
            for(int i = 0; i < (int)bots.size(); ++i)
                if(bots[i].getTurn().getMoney() == 0) {
                    bots.erase(bots.begin() + i);
                    --i;
                    std::cout << "Bot number " << i << " has been eliminated :((\n";
                }
        }
    }
};