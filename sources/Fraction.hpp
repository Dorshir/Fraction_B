#ifndef FRACTION_A_MAIN_FRACTION_HPP
#define FRACTION_A_MAIN_FRACTION_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <limits>

using namespace std;

namespace ariel {}

class Fraction {

private:

    int numerator;
    int denominator;

public:

    Fraction();

    Fraction(float fraction);

    Fraction(int numerator, int denominator);

    static Fraction floatToFraction(float value);

    friend std::ostream &operator<<(std::ostream &outstream, const Fraction &fraction);

    friend std::istream &operator>>(std::istream &instream, Fraction &fraction);

    Fraction operator+(const Fraction &other) const;

    Fraction operator+(float other) const;

    friend Fraction operator+(float value, const Fraction &fraction);

    Fraction operator-(const Fraction &other) const;

    Fraction operator-(float other) const;

    friend Fraction operator-(float value, const Fraction &fraction);

    Fraction operator/(const Fraction &other) const;

    Fraction operator/(float other) const;

    friend Fraction operator/(float value, const Fraction &fraction);

    Fraction operator*(const Fraction &other) const;

    Fraction operator*(float other) const;

    friend Fraction operator*(float value, const Fraction &fraction);

    bool operator==(const Fraction &other) const;

    bool operator==(float other) const;

    friend bool operator==(float value, const Fraction &fraction);

    bool operator!=(const Fraction &other) const;

    bool operator!=(float other) const;

    friend bool operator!=(float value, const Fraction &fraction);

    bool operator>(const Fraction &other) const;

    bool operator>(float other) const;

    friend bool operator>(float value, const Fraction &fraction);

    bool operator<(const Fraction &other) const;

    bool operator<(float other) const;

    friend bool operator<(float value, const Fraction &fraction);

    bool operator>=(const Fraction &other) const;

    bool operator>=(float other) const;

    friend bool operator>=(float value, const Fraction &fraction);

    bool operator<=(const Fraction &other) const;

    bool operator<=(float other) const;

    friend bool operator<=(float value, const Fraction &fraction);

    Fraction& operator++();

    Fraction operator++(int);

    Fraction& operator--();

    Fraction operator--(int);

    [[nodiscard]] int getNumerator() const;

    [[nodiscard]] int getDenominator() const;

    [[nodiscard]] int lcm(const Fraction &other) const;
};

    int add_ints(int first, int second);

    int sub_ints(int first, int second);

    int mul_ints(int first, int second);


#endif
