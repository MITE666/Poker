#include "FlopTurnRiver.h"
#include "Player.h"
#include "Combination.h"

int main() {
    std::array <Card, 7> playerHand = {
            Card("Clubs", "Ace"), Card("Clubs", "Jack"),
            Card("Clubs", "King"), Card("Clubs", "Queen"),
            Card("Hearts", "Three"), Card("Diamonds", "Eight"),
            Card("Clubs", "Ten")
    };
    Deck deck;
    Player player(deck);
    //playerHand[0] = player.getHand()[0];
    //playerHand[1] = player.getHand()[1];
    std::array < Player, 5 > bot = { Player(deck), Player(deck), Player(deck), Player(deck), Player(deck)};
    std::cout << "Jucatorul are: \n" << player;
    for(int i = 0; i < 5; ++i)
        std::cout << "Botul " << i << " are: \n" << bot[i];
    FlopTurnRiver ftr(deck);
    std::array <Card, 3> flop = ftr.Flop();
    //for(int i = 0; i < 3; ++i)
    //    playerHand[i+2] = flop[i];
    //playerHand[5] = ftr.Turn();
    //playerHand[6] = ftr.River();

    std::cout <<"\n\n\n\n\n";
    for(int i = 0; i < 7; ++i)
        std::cout << playerHand[i] << " ";
    std::cout << "\n";

    Combination combination(playerHand);

    std::pair <std::string, Card> combo = combination.CheckCombination();
    std::cout << combo.first << "\n" << combo.second;
    return 0;
}