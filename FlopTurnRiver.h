#include <array>
#include "Deck.h"

class FlopTurnRiver {
private:
    std::array < Card, 3 > flop;
    Card turn, river;

public:
    FlopTurnRiver(Deck& deck) {
        for(int i = 0; i < 3; ++i)
            flop[i] = deck.getRandomCard();
        turn = deck.getRandomCard();
        river = deck.getRandomCard();
    };
    const std::array < Card, 3 >& Flop() {
        std::cout << "Flop: \n";
        for(int i = 0; i < 3; ++i)
            std::cout << flop[i];
        return flop;
    }
    const Card& Turn() {
        std::cout << "Turn: \n" << turn;
        return turn;
    }
    const Card& River() {
        std::cout << "River: \n" << river;
        return river;
    }
    ~FlopTurnRiver() = default;
};