#include "FlopTurnRiver.h"

int main() {
    Deck deck;
    Player player(deck);
    std::array < Player, 5 > bot = { Player(deck), Player(deck), Player(deck), Player(deck), Player(deck)};
    std::cout << "Jucatorul are: \n" << player;
    for(int i = 0; i < 5; ++i)
        std::cout << "Botul " << i << " are: \n" << bot[i];
    FlopTurnRiver ftr(deck);
    ftr.Flop();
    ftr.Turn();
    ftr.River();
    return 0;
}