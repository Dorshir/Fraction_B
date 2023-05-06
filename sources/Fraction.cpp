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

int add_ints(int a, int b) {
    if (a > 0 && b > std::numeric_limits<int>::max() - a) {
        throw std::overflow_error("Integer overflow");
    }
    if (a < 0 && b < std::numeric_limits<int>::min() - a) {
        throw std::overflow_error("Integer underflow");
    }
    return a + b;
}

int sub_ints(int a, int b) {
if (b < 0 && a > std::numeric_limits<int>::max() + b) {
        throw std::overflow_error("Integer overflow");
    }
    if (b > 0 && a < std::numeric_limits<int>::min() + b) {
        throw std::overflow_error("Integer underflow");
    }
    return a - b;
}

int mul_ints(int a, int b) {

    if (a > 0 && b > 0 && a > std::numeric_limits<int>::max() / b) {
        throw std::overflow_error("Integer overflow");
    }
    if (a < 0 && b < 0 && a < std::numeric_limits<int>::max() / b) {
        throw std::overflow_error("Integer overflow");}
    return a * b;  
}

Fraction::Fraction(int n, int d) {
    if (d < 0) {
        d = d * (-1);
        n = n * (-1);
    } else if (d == 0) {
        throw invalid_argument("0");
    }

    int sign = n*d < 0 ? -1 : 1;
    int gcd = __gcd(n, d);
    numerator = abs(n / gcd) * sign;
    denominator = abs(d / gcd);
}

Fraction::Fraction(float f){
    Fraction temp = floatToFraction(f);
    numerator = temp.getNumerator();
    denominator = temp.getDenominator();
}

Fraction::Fraction(){
    numerator = 0;
    denominator = 1;
}

int Fraction::getNumerator() const {
    return numerator;
}

int Fraction::getDenominator() const {
    return denominator;
}

std::ostream &operator<<(std::ostream &out, const Fraction &c) {
    return out << c.getNumerator() << '/' << c.getDenominator();
}

std::istream &operator>>(std::istream &in, Fraction &fraction) {
    string input;
    char c;

    // Read numerator
    while (in.get(c)) {
        if (c == '/' || c == ' ' || c == ',') {
            break;
        }
        if(c == '.') throw runtime_error("Invalid argument, cannot initialize float as numerator.");
        input += c;
    }
    try {
    fraction.numerator = std::stoi(input);
} catch (const std::invalid_argument& e) {
    throw std::runtime_error("Invalid argument, numerator is not a valid integer.");
}

    // Read denominator
    input = "";
    while (in.get(c)) {
        if (c == '\n' || c == '\r' || c == ' ') {
            break;
        }
        if(c == '.') throw runtime_error("Invalid argument, cannot initialize float as denominator.");
        input += c;
    }
    if(input == "0") throw runtime_error("Denominator initialize by 0 is not defined.");
    if(input == "") throw invalid_argument("One number only.");
    fraction.denominator = stoi(input);
    
    int sign = fraction.numerator * fraction.denominator < 0 ? -1 : 1;
    fraction.numerator = abs(fraction.numerator) * sign;
    fraction.denominator = abs(fraction.denominator);
    return in;
}

Fraction Fraction::operator+(const Fraction &other) const {

    int lcm = (denominator * other.getDenominator()) / __gcd(denominator, other.getDenominator());

    int new_num1 = numerator * (lcm / denominator);
    int new_num2 = other.getNumerator() * (lcm / other.getDenominator());

    int result_num = add_ints(new_num1,new_num2);

    return {result_num, lcm};
}

Fraction Fraction::operator-(const Fraction &other) const {

    int lcm = (denominator * other.getDenominator()) / __gcd(denominator, other.getDenominator());

    int new_num1 = numerator * (lcm / denominator);
    int new_num2 = other.getNumerator() * (lcm / other.getDenominator());

    int result_num = sub_ints(new_num1,new_num2);

    return {result_num, lcm};
}

Fraction Fraction::operator/(const Fraction &other) const {
    if(other == 0) throw runtime_error("Division by 0 is not defined.");
    return {mul_ints(numerator,other.getDenominator()), mul_ints(denominator, other.getNumerator())};
}

Fraction Fraction::operator*(const Fraction &other) const {

    return {mul_ints(numerator, other.getNumerator()), mul_ints(denominator,other.getDenominator())};
}

bool Fraction::operator==(const Fraction &other) const {

    if ((numerator == other.getNumerator() && denominator == other.getDenominator()) || ((*this).numerator == 0 && other.getNumerator() == 0)) return true;
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
    // int LCM = lcm(other);
    // int new_num1 = numerator * (LCM / denominator);
    // int new_num2 = other.getNumerator() * (LCM / other.getDenominator());
    // return new_num1 >= new_num2;

    int new_num1 = numerator * other.getDenominator();
    int new_num2 = other.getNumerator() * denominator;

    return new_num1 >= new_num2;
}

bool Fraction::operator<=(const Fraction &other) const {
    if (denominator == other.getDenominator()) {
        if (numerator <= other.getNumerator()) return true;
    }
    // int LCM = lcm(other);
    // int new_num1 = numerator * (LCM / denominator);
    // int new_num2 = other.getNumerator() * (LCM / other.getDenominator());
    // return new_num1 <= new_num2;

    int new_num1 = numerator * other.getDenominator();
    int new_num2 = other.getNumerator() * denominator;

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
    Fraction f = (*this) - floatToFraction(other);
    return f;
}

Fraction Fraction::operator/(float other) const {
    if (other == 0) throw runtime_error("Division by 0 is not defined.");
    Fraction f = (*this) / floatToFraction(other);
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