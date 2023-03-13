#include <array>
#include <map>
#include "Card.h"

class Combination {
private:
    std::array <Card, 7> cards;
    Card highestCard;
    std::map <std::string, int> numberValue = {
            std::pair <std::string, int> ("Two", 0), std::pair <std::string, int> ("Three", 1),
            std::pair <std::string, int> ("Four", 2), std::pair <std::string, int> ("Five", 3),
            std::pair <std::string, int> ("Six", 4), std::pair <std::string, int> ("Seven", 5),
            std::pair <std::string, int> ("Eight", 6), std::pair <std::string, int> ("Nine", 7),
            std::pair <std::string, int> ("Ten", 8), std::pair <std::string, int> ("Jack", 9),
            std::pair <std::string, int> ("Queen", 10), std::pair <std::string, int> ("King", 11),
            std::pair <std::string, int> ("Ace", 12)
    };

    std::pair <bool, Card> CheckHighCard() {
        int maxim = -1;
        Card card;
        for(int i = 0; i < 7; ++i) {
            int value = numberValue[cards[i].getNumber()];
            if(value > maxim) {
                maxim = value;
                card = cards[i];
            }
        }
        return std::make_pair(1, card);
    };

    std::pair <bool, Card> CheckPair() {
        bool OK = 0;
        int maxim = -1;
        Card card;
        for(int i = 0; i < 6; ++i)
            for(int j = i+1; j < 7; ++j)
                if(cards[i].getNumber() == cards[j].getNumber()){
                    OK = 1;
                    int value = numberValue[cards[i].getNumber()];
                    if(value > maxim) {
                        maxim = value;
                        card = cards[i];
                    }
                }
        return std::make_pair(OK, card);
    }

    std::pair <bool, Card> CheckTwoPair() {
        bool OK = 0;
        int maxim = -1;
        Card card;
        int fr[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for(int i = 0; i < 7; ++i)
            ++fr[numberValue[cards[i].getNumber()]];
        int k = 0;
        for(int i = 0; i < 13; ++i)
            if(fr[i] == 2)
                ++k;
        if(k > 1) {
            OK = 1;
            for(int i = 0; i < 7; ++i) {
                int value = numberValue[cards[i].getNumber()];
                if(value > maxim && fr[numberValue[cards[i].getNumber()]] == 2) {
                    maxim = value;
                    card = cards[i];
                }
            }
        }
        return std::make_pair(OK, card);
    }

    std::pair <bool, Card> CheckThreeOfAKind() {
        bool OK = 0;
        int maxim = -1;
        Card card;
        for(int i = 0; i < 5; ++i)
            for(int j = i+1; j < 6; ++j)
                for(int k = j+1; k < 7; ++k)
                    if(cards[i].getNumber() == cards[j].getNumber() && cards[j].getNumber() == cards[k].getNumber()) {
                        OK = 1;
                        int value = numberValue[cards[i].getNumber()];
                        if(value > maxim) {
                            maxim = value;
                            card = cards[i];
                        }
                    }
        return std::make_pair(OK, card);
    }

    std::pair <bool, Card> CheckStraight() {
        bool OK = 0;
        Card card;
        bool straight[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for(int i = 0; i < 7; ++i)
            straight[numberValue[cards[i].getNumber()]] = 1;
        int lgmax = 0, lg = 0;
        for(int i = 0; i < 13; ++i) {
            if(straight[i] == 1)
                ++lg;
            else {
                if(lg > lgmax)
                    lgmax = lg;
                lg = 0;
            }
            if(lg > 4) {
                for(int j = 0; j < 7; ++j)
                    if(i == numberValue[cards[j].getNumber()])
                        card = cards[j];
            }
        }
        // Check for special case when we have the straight: Ace, 2, 3, 4, 5
        if(lgmax < 5 && straight[0] && straight[1] && straight[2] && straight[3] && straight[12]) {
            OK = 1;
            for(int i = 0; i < 7; ++i)
                if(3 == numberValue[cards[i].getNumber()])
                    card = cards[i];
        }
        if(lgmax > 4)
            OK = 1;
        return std::make_pair(OK, card);
    }

    std::pair <bool, Card> CheckFlush() {
        bool OK = 0;
        int maxim = -1;
        Card card;
        std::map <std::string, int> suits;
        suits["Hearts"] = 0;
        suits["Diamonds"] = 0;
        suits["Spades"] = 0;
        suits["Clubs"] = 0;
        for(int i = 0; i < 7; ++i)
            ++suits[cards[i].getSuit()];
        for(const auto& [key, value] : suits)
            if(value > 4) {
                OK = 1;
                for(int i = 0; i < 7; ++i) {
                    int value = numberValue[cards[i].getNumber()];
                    if(value > maxim) {
                        maxim = value;
                        card = cards[i];
                    }
                }
            }
        return std::make_pair(OK, card);
    }

    std::pair <bool, Card> CheckFullHouse() {
        bool OK = 0;
        int maxim = -1;
        Card card;
        std::map <std::string, int> numberCount;
        numberCount["Ace"] = 0;
        numberCount["Two"] = 0;
        numberCount["Three"] = 0;
        numberCount["Four"] = 0;
        numberCount["Five"] = 0;
        numberCount["Six"] = 0;
        numberCount["Seven"] = 0;
        numberCount["Eight"] = 0;
        numberCount["Nine"] = 0;
        numberCount["Ten"] = 0;
        numberCount["Jack"] = 0;
        numberCount["Queen"] = 0;
        numberCount["King"] = 0;
        for(int i = 0; i < 7; ++i)
            ++numberCount[cards[i].getNumber()];
        bool parts[2] = {0, 0};
        for(const auto& [key, value] : numberCount) {
            if(value == 3) {
                if (parts[0] == 1)
                    parts[1] = 1;
                else
                    parts[0] = 1;
            }
            else if(value == 2)
                parts[1] = 1;
        }
        if(parts[0] && parts[1]) {
            OK = 1;
            for(int i = 0; i < 7; ++i) {
                int value = numberValue[cards[i].getNumber()];
                if(numberCount[cards[i].getNumber()] == 3 && value > maxim) {
                    maxim = value;
                    card = cards[i];
                }
            }
        }
        return std::make_pair(OK, card);
    }

    std::pair <bool, Card> CheckFourOfAKind() {
        bool OK = 0;
        Card card;
        std::map <std::string, int> numbers;
        numbers["Ace"] = 0;
        numbers["Two"] = 0;
        numbers["Three"] = 0;
        numbers["Four"] = 0;
        numbers["Five"] = 0;
        numbers["Six"] = 0;
        numbers["Seven"] = 0;
        numbers["Eight"] = 0;
        numbers["Nine"] = 0;
        numbers["Ten"] = 0;
        numbers["Jack"] = 0;
        numbers["Queen"] = 0;
        numbers["King"] = 0;
        for(int i = 0; i < 7; ++i)
            ++numbers[cards[i].getNumber()];
        std::string number;
        for(const auto& [key, value] : numbers)
            if(value == 4) {
                number = key;
                OK = 1;
                break;
            }
        if(OK)
            for(int i = 0; i < 7; ++i)
                if(cards[i].getNumber() == number) {
                    card = cards[i];
                    break;
                }
        return std::make_pair(OK, card);
    }

    std::pair <bool, Card> CheckStraightFlush() {
        bool OK = 0;
        int maxim = -1;
        Card card;
        bool straight[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int length[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for(int i = 0; i < 7; ++i)
            straight[numberValue[cards[i].getNumber()]] = 1;
        if(straight[0])
            length[0] = 1;
        for(int i = 1; i < 13; ++i)
            if(straight[i])
                length[i] = length[i-1] + 1;
        for(int i = 11; i >= 0; --i)
            if(length[i] != 0 && length[i+1] != 0)
                length[i] = length[i+1];
        int lgmax = 0;
        for(int i = 0; i < 13; ++i)
            if(length[i] > lgmax)
                lgmax = length[i];
        // Check again for the Ace, 2, 3, 4, 5 situation
        bool specialCase = 0;
        if(lgmax < 5 && straight[0] && straight[1] && straight[2] && straight[3] && straight[12]) {
            lgmax = 5;
            length[0] = lgmax;
            length[1] = lgmax;
            length[2] = lgmax;
            length[3] = lgmax;
            length[12] = lgmax;
            specialCase = 1;
        }
        if(lgmax > 4) {
            std::string maxSuit;
            for(int i = 0; i < 7; ++i)
                if(length[numberValue[cards[i].getNumber()]] > 4) {
                    maxSuit = cards[i].getSuit();
                    break;
                }
            OK = 1;
            for(int i = 0; i < 7; ++i) {
                if(cards[i].getSuit() != maxSuit && length[numberValue[cards[i].getNumber()]] > 4) {
                    OK = 0;
                    break;
                }
                else if(cards[i].getSuit() == maxSuit && length[numberValue[cards[i].getNumber()]] > 4) {
                    int value = numberValue[cards[i].getNumber()];
                    if (value > maxim && !specialCase) {
                        maxim = value;
                        card = cards[i];
                    } else if (value > maxim && specialCase && cards[i].getNumber() != "Ace") {
                        maxim = value;
                        card = cards[i];
                    }
                }
            }
        }
        return std::make_pair(OK, card);
    }

    std::pair <bool, Card> CheckRoyalFlush() {
        bool OK = 0;
        Card card;
        std::map <std::string, int> suits;
        suits["Hearts"] = 0;
        suits["Clubs"] = 0;
        suits["Diamonds"] = 0;
        suits["Spades"] = 0;
        for(int i = 0; i < 7; ++i)
            ++suits[cards[i].getSuit()];
        std::string maxSuit;
        for(const auto& [key, value] : suits)
            if(value > 4) {
                OK = 1;
                maxSuit = key;
                break;
            }
        if(OK) {
            bool royalFlush[5] = {0, 0, 0, 0, 0};
            for(int i = 0; i < 7; ++i) {
                if(cards[i].getSuit() == maxSuit) {
                    if(cards[i].getNumber() == "Ten")
                        royalFlush[0] = 1;
                    else if(cards[i].getNumber() == "Jack")
                        royalFlush[1] = 1;
                    else if(cards[i].getNumber() == "Queen")
                        royalFlush[2] = 1;
                    else if(cards[i].getNumber() == "King")
                        royalFlush[3] = 1;
                    else if(cards[i].getNumber() == "Ace") {
                        royalFlush[4] = 1;
                        card = cards[i];
                    }
                }
            }
            for(int i = 0; i < 5; ++i)
                OK *= royalFlush[i];
        }
        return std::make_pair(OK, card);
    }

public:
    Combination(std::array <Card, 7>& cards_) {
        for(int i = 0; i < 7; ++i)
            cards[i] = cards_[i];
    }

    std::pair <std::string, Card> CheckCombination() {
        if(CheckRoyalFlush().first)
            return std::make_pair("Royal Flush", CheckRoyalFlush().second);
        else if(CheckStraightFlush().first)
            return std::make_pair("Straight Flush", CheckStraightFlush().second);
        else if(CheckFourOfAKind().first)
            return std::make_pair("Four of a Kind", CheckFourOfAKind().second);
        else if(CheckFullHouse().first)
            return std::make_pair("Full House", CheckFullHouse().second);
        else if(CheckFlush().first)
            return std::make_pair("Flush", CheckFlush().second);
        else if(CheckStraight().first)
            return std::make_pair("Straight", CheckStraight().second);
        else if(CheckThreeOfAKind().first)
            return std::make_pair("Three of a Kind", CheckThreeOfAKind().second);
        else if(CheckTwoPair().first)
            return std::make_pair("Two Pair", CheckTwoPair().second);
        else if(CheckPair().first)
            return std::make_pair("Pair", CheckPair().second);
        else if(CheckHighCard().first)
            return std::make_pair("High Card", CheckHighCard().second);
    }

    ~Combination() = default;
};