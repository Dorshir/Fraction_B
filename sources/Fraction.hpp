#ifndef FRACTION_A_MAIN_FRACTION_HPP
#define FRACTION_A_MAIN_FRACTION_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

using namespace std;

namespace ariel {}

class Fraction {

private:

    Fraction();

    Fraction(const float f);

    int numerator;
    int denominator;

public:

    static Fraction floatToFraction(float x);

    Fraction(int numerator, int denominator);

    friend std::ostream &operator<<(std::ostream &out, const Fraction &c);

    friend std::istream &operator>>(std::istream &in, Fraction &c);

    Fraction operator+(const Fraction &other) const;

    Fraction operator+(float other) const;

    friend Fraction operator+(float value, const Fraction &f);

    Fraction operator-(const Fraction &other) const;

    Fraction operator-(float other) const;

    friend Fraction operator-(float value, const Fraction &f);

    Fraction operator/(const Fraction &other) const;

    Fraction operator/(float other) const;

    friend Fraction operator/(float value, const Fraction &f);

    Fraction operator*(const Fraction &other) const;

    Fraction operator*(float other) const;

    friend Fraction operator*(float value, const Fraction &f);

    bool operator==(const Fraction &other) const;

    bool operator==(float other) const;

    friend bool operator==(float value, const Fraction &f);

    bool operator!=(const Fraction &other) const;

    bool operator!=(float other) const;

    friend bool operator!=(float value, const Fraction &f);

    bool operator>(const Fraction &other) const;

    bool operator>(float other) const;

    friend bool operator>(float value, const Fraction &f);

    bool operator<(const Fraction &other) const;

    bool operator<(float other) const;

    friend bool operator<(float value, const Fraction &f);

    bool operator>=(const Fraction &other) const;

    bool operator>=(float other) const;

    friend bool operator>=(float value, const Fraction &f);

    bool operator<=(const Fraction &other) const;

    bool operator<=(float other) const;

    friend bool operator<=(float value, const Fraction &f);

    Fraction& operator++();

    Fraction operator++(int);

    Fraction& operator--();

    Fraction operator--(int);

    [[nodiscard]] int getNumerator() const;

    [[nodiscard]] int getDenominator() const;

    [[nodiscard]] int lcm(const Fraction &other) const;
};


#endif
