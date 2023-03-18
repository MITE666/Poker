#pragma once

#include <iostream>
#include <string>
#include <utility>

class Card {
private:
    std::string suit;
    std::string number;

public:
    Card() = default;
    Card(std::string  suit_, std::string  number_) : suit{std::move( suit_ )}, number{std::move( number_ )} {};
    [[nodiscard]] const std::string& getSuit() const { return suit; }
    [[nodiscard]] const std::string& getNumber() const { return number; }
    Card& operator=(const Card& other) {
        suit = other.getSuit();
        number = other.getNumber();
        return *this;
    }
    Card(const Card&) = delete;
    friend std::ostream& operator<<(std::ostream& os, const Card& c) {
        os << c.number << " of " << c.suit << "\n";
        return os;
    }
    ~Card() = default;
};