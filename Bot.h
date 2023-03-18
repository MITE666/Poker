#include <array>
#include "Deck.h"
#include "Turn.h"

class Bot {
private:
    Turn turn;
    std::array<Card, 2> hand;

public:
    Bot() = default;

    Bot(Deck& deck, int money) {
        hand[0] = deck.getRandomCard();
        hand[1] = deck.getRandomCard();
        turn = Turn(money);
    }

    const std::array< Card, 2 >& getHand() const {
        return hand;
    }

    ~Bot() = default;

    Turn& getTurn() { return turn; }
};