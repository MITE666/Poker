#include <array>
#include "Deck.h"
#include "Turn.h"

class Player {
private:
    Turn turn;
    std::array< Card, 2 > hand;

public:
    Player() = default;
    Player(Deck& deck, int money) {
        hand[0] = deck.getRandomCard();
        hand[1] = deck.getRandomCard();
        turn = Turn(money);
    }
    const std::array< Card, 2 >& getHand() const {
        return hand;
    }
    friend std::ostream& operator<<(std::ostream& os, const Player& p) {
        os << p.hand[0] << "\n" << p.hand[1] << "\n";
        return os;
    }

    Turn& getTurn() { return turn; }

    ~Player() = default;
};