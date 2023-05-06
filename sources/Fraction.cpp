#include "Fraction.hpp"

int Fraction::lcm(const Fraction &other) const {
    int lcm = (denominator * other.getDenominator()) / __gcd(denominator, other.getDenominator());
    int num1 = numerator;
    num1 *= (lcm / denominator);
    int num2 = other.getNumerator();
    num2 *= lcm / other.getDenominator();

    int sum_num = num1 + num2;
    int gcd = __gcd(sum_num, lcm);
    lcm /= gcd;
    return lcm;
}

Fraction::Fraction(int n, int d) {
    if (d < 0) {
        d = d * (-1);
        n = n * (-1);
    } else if (d == 0) {
        throw invalid_argument("0");
    }
    int gcd = __gcd(n, d);
    numerator = n / gcd;
    denominator = d / gcd;
}

int Fraction::getNumerator() const {
    return numerator;
}

int Fraction::getDenominator() const {
    return denominator;
}

std::ostream &operator<<(std::ostream &out, const Fraction &c) {
    out << c.getNumerator() << '/' << c.getDenominator() << endl;
    return out;
}

std::istream &operator>>(std::istream &in, Fraction &fraction) {
    string input;
    if (getline(in, input, '/')) {
        fraction.numerator = std::stoi(input);
        if (getline(in, input)) {
            fraction.denominator = stoi(input);
        } else {
            fraction.denominator = 1;
        }
    }
    return in;
}

Fraction Fraction::operator+(const Fraction &other) const {

    int LCM = lcm(other);
    int sum_num = numerator + other.getNumerator();
    int gcd = __gcd(sum_num, LCM);
    sum_num /= gcd;
    return {sum_num, LCM};
}

Fraction Fraction::operator-(const Fraction &other) const {

    int LCM = lcm(other);

    int new_num1 = numerator * (LCM / denominator);
    int new_num2 = other.getNumerator() * (LCM / other.getDenominator());

    int result_num = new_num1 - new_num2;

    return {result_num, LCM};
}

Fraction Fraction::operator/(const Fraction &other) const {
    return {numerator * other.getDenominator(), denominator * other.getNumerator()};
}

Fraction Fraction::operator*(const Fraction &other) const {
    return {numerator * other.getNumerator(), denominator * other.getDenominator()};
}

bool Fraction::operator==(const Fraction &other) const {

    if (numerator == other.getNumerator() && denominator == other.getDenominator()) return true;
    return false;
}

Fraction &Fraction::operator++() {
    numerator += denominator;
    return *this;
}

Fraction &Fraction::operator--() {
    numerator -= denominator;
    return *this;
}

bool Fraction::operator>(const Fraction &other) const {
    if (denominator == other.getDenominator()) {
        if (numerator > other.getNumerator()) return true;
    }
    int LCM = lcm(other);
    int new_num1 = numerator * (LCM / denominator);
    int new_num2 = other.getNumerator() * (LCM / other.getDenominator());
    return new_num1 > new_num2;
}

bool Fraction::operator<(const Fraction &other) const {
    if (denominator == other.getDenominator()) {
        if (numerator < other.getNumerator()) return true;
    }
    int LCM = lcm(other);
    int new_num1 = numerator * (LCM / denominator);
    int new_num2 = other.getNumerator() * (LCM / other.getDenominator());
    return new_num1 < new_num2;
}

bool Fraction::operator>=(const Fraction &other) const {
    if (denominator == other.getDenominator()) {
        if (numerator >= other.getNumerator()) return true;
    }
    int LCM = lcm(other);
    int new_num1 = numerator * (LCM / denominator);
    int new_num2 = other.getNumerator() * (LCM / other.getDenominator());
    return new_num1 >= new_num2;
}

bool Fraction::operator<=(const Fraction &other) const {
    if (denominator == other.getDenominator()) {
        if (numerator <= other.getNumerator()) return true;
    }
    int LCM = lcm(other);
    int new_num1 = numerator * (LCM / denominator);
    int new_num2 = other.getNumerator() * (LCM / other.getDenominator());
    return new_num1 <= new_num2;
}

Fraction Fraction::floatToFraction(float x) {
    int sign = x < 0 ? -1 : 1;
    x = std::abs(x) * 1000.0f;
    int intVal = static_cast<int>(x);
    Fraction result = {intVal * sign, 1000};
    return result;
}

bool Fraction::operator>(const float other) const {
    Fraction f = floatToFraction(other);
    if (denominator == f.getDenominator()) {
        if (numerator > f.getNumerator()) return true;
    }
    int LCM = lcm(f);
    int new_num1 = numerator * (LCM / denominator);
    int new_num2 = f.getNumerator() * (LCM / f.getDenominator());
    return new_num1 > new_num2;
}


bool Fraction::operator<(const float other) const {
    Fraction f = floatToFraction(other);
    if (denominator == f.getDenominator()) {
        if (numerator > f.getNumerator()) return true;
    }
    int LCM = lcm(f);
    int new_num1 = numerator * (LCM / denominator);
    int new_num2 = f.getNumerator() * (LCM / f.getDenominator());
    return new_num1 < new_num2;
}

bool Fraction::operator>=(const float other) const {
    Fraction f = floatToFraction(other);
    if (denominator == f.getDenominator()) {
        if (numerator >= f.getNumerator()) return true;
    }
    int LCM = lcm(f);
    int new_num1 = numerator * (LCM / denominator);
    int new_num2 = f.getNumerator() * (LCM / f.getDenominator());
    return new_num1 >= new_num2;
}

bool Fraction::operator<=(const float other) const {
    Fraction f = floatToFraction(other);
    if (denominator == f.getDenominator()) {
        if (numerator <= f.getNumerator()) return true;
    }
    int LCM = lcm(f);
    int new_num1 = numerator * (LCM / denominator);
    int new_num2 = f.getNumerator() * (LCM / f.getDenominator());
    return new_num1 <= new_num2;
}

Fraction Fraction::operator+(float other) const {
    Fraction f = floatToFraction(other) + (*this);
    return f;
}

Fraction Fraction::operator-(float other) const {
    Fraction f = floatToFraction(other) - (*this);
    return f;
}

Fraction Fraction::operator/(float other) const {
    if (other == 0) throw invalid_argument("0");
    Fraction f = floatToFraction(other) / (*this);
    return f;
}

bool Fraction::operator==(float other) const {
    Fraction f = floatToFraction(other);
    return f == (*this);
}

Fraction Fraction::operator*(float other) const {
    Fraction f = floatToFraction(other) * (*this);
    return f;
}

Fraction operator*(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value) * f;
    return t;
}

Fraction Fraction::operator++(int) {
    Fraction temp(numerator, denominator);
    numerator += denominator;
    return temp;
}

Fraction Fraction::operator--(int) {
    Fraction temp(numerator, denominator);
    numerator -= denominator;
    return temp;
}

Fraction operator/(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value) / f;
    return t;
}

bool operator==(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value);
    return t == f;
}

bool Fraction::operator!=(const Fraction &other) const {
    return !((*this) == other);
}

bool Fraction::operator!=(float other) const {
    Fraction f = Fraction::floatToFraction(other);
    return (*this) != f;
}

bool operator!=(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value);
    return f != t;
}

bool operator>(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value);
    return t > f;
}

Fraction operator+(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value);
    return t + f;
}

Fraction operator-(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value);
    return t - f;
}

bool operator<(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value);
    return t < f;
}

bool operator>=(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value);
    return t >= f;
}

bool operator<=(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value);
    return t <= f;
}