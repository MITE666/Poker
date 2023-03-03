#include <iostream>

class Card {
private:
    std::string suit;
    std::string number;

public:
    Card() {
        suit = "";
        number = "";
    }
    Card(const std::string suit_, const std::string number_) : suit{suit_}, number{number_} {}
    const std::string& getSuit() const { return suit; }
    const std::string& getNumber() const { return number; }
    Card& operator=(const Card& other) {
        suit = other.getSuit();
        number = other.getNumber();
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Card& c) {
        os << c.number << " of " << c.suit << "\n";
        return os;
    }
    ~Card() {};
};