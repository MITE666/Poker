#include <cstdlib>
#include "Card.h"

class Deck {
private:
    Card deck[52] = {
            Card("Hearts", "Ace"), Card("Hearts", "Two"), Card("Hearts", "Three"), Card("Hearts", "Four"),
            Card("Hearts", "Five"), Card("Hearts", "Six"), Card("Hearts", "Seven"), Card("Hearts", "Eight"),
            Card("Hearts", "Nine"), Card("Hearts", "Ten"), Card("Hearts", "Jack"), Card("Hearts", "Queen"),
            Card("Hearts", "King"), Card("Diamonds", "Ace"), Card("Diamonds", "Two"), Card("Diamonds", "Three"),
            Card("Diamonds", "Four"), Card("Diamonds", "Five"), Card("Diamonds", "Six"), Card("Diamonds", "Seven"),
            Card("Diamonds", "Eight"), Card("Diamonds", "Nine"), Card("Diamonds", "Ten"), Card("Diamonds", "Jack"),
            Card("Diamonds", "Queen"), Card("Diamonds", "King"), Card("Spades", "Ace"), Card("Spades", "Two"),
            Card("Spades", "Three"), Card("Spades", "Four"), Card("Spades", "Five"), Card("Spades", "Six"),
            Card("Spades", "Seven"), Card("Spades", "Eight"), Card("Spades", "Nine"), Card("Spades", "Ten"),
            Card("Spades", "Jack"), Card("Spades", "Queen"), Card("Spades", "King"), Card("Clubs", "Ace"),
            Card("Clubs", "Two"), Card("Clubs", "Three"), Card("Clubs", "Four"), Card("Clubs", "Five"),
            Card("Clubs", "Six"), Card("Clubs", "Seven"), Card("Clubs", "Eight"), Card("Clubs", "Nine"),
            Card("Clubs", "Ten"), Card("Clubs", "Jack"), Card("Clubs", "Queen"), Card("Clubs", "King")
    };
    bool freq[52];

    // Robert Jenkins' 96 bit Mix Function
    unsigned long mix(unsigned long a, unsigned long b, unsigned long c) {
        a=a-b;  a=a-c;  a=a^(c >> 13);
        b=b-c;  b=b-a;  b=b^(a << 8);
        c=c-a;  c=c-b;  c=c^(b >> 13);
        a=a-b;  a=a-c;  a=a^(c >> 12);
        b=b-c;  b=b-a;  b=b^(a << 16);
        c=c-a;  c=c-b;  c=c^(b >> 5);
        a=a-b;  a=a-c;  a=a^(c >> 3);
        b=b-c;  b=b-a;  b=b^(a << 10);
        c=c-a;  c=c-b;  c=c^(b >> 15);
        return c;
    }

public:
    Deck() {
        for(int i = 0; i < 52; ++i)
            freq[i] = 0;
        std::cout << "Am creat pachetul de carti\n";
    }
    Card getRandomCard() {
        int r;
        do {
            unsigned long seed = mix(clock(), time(NULL), getpid());
            srand(seed);
            r = rand();
            r %= 52;
        } while(freq[r] == 1);
        freq[r] = true;
        this->getFreq();
        return deck[r];
    }
    void deckReset() {
        for(int i = 0; i < 52; ++i)
            freq[i] = false;
    }
    void getFreq() {
        for(int i = 0; i < 52; ++i)
            std::cout << freq[i] << " ";
        std::cout << "\n";
    }
    ~Deck() {};
};