#include <array>
#include "Deck.h"

class Player {
private:
    std::array< Card, 2 > hand;

public:
    Player(Deck& deck) {
        hand[0] = deck.getRandomCard();
        hand[1] = deck.getRandomCard();
        std::cout << "Am creat jucatorul\n";
    }
    const std::array< Card, 2 > getHand() const {
        return hand;
    }
    friend std::ostream& operator<<(std::ostream& os, const Player& p) {
        os << p.hand[0] << "\n" << p.hand[1] << "\n";
        return os;
    }
    ~Player() = default;
};