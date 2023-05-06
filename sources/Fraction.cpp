#include "Fraction.hpp"

/**
 * Calculates the least common multiple (LCM) of two fractions.
 * @param other The fraction to calculate the LCM with.
 * @return The LCM of the two fractions.
 */
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

/**
 * Converts a float value to a Fraction object.
 * Multiplies the float value by 1000 to obtain a more accurate representation of the fraction, and then creates a Fraction object with the resulting numerator and denominator of 1000.
 * The sign of the float value is preserved in the resulting Fraction object.
 * @param x The float value to convert to a Fraction object.
 * @return A Fraction object representing the given float value.
 */
Fraction Fraction::floatToFraction(float x) {
    int sign = x < 0 ? -1 : 1;
    x = std::abs(x) * 1000.0f;
    int intVal = static_cast<int>(x);
    Fraction result = {intVal * sign, 1000};
    return result;
}

/**
 * Adds two integers and returns the result. Checks for integer overflow and underflow.
 * @param a The first integer to add.
 * @param b The second integer to add.
 * @throws std::overflow_error If the result of the addition overflows the maximum or underflows the minimum integer value.
 * @return The sum of the two integers.
 */
int add_ints(int a, int b) {
    if (a > 0 && b > std::numeric_limits<int>::max() - a) {
        throw std::overflow_error("Integer overflow");
    }
    if (a < 0 && b < std::numeric_limits<int>::min() - a) {
        throw std::overflow_error("Integer underflow");
    }
    return a + b;
}

/**
 * Subtracts two integers and returns the result. Checks for integer overflow and underflow.
 * @param a The integer to subtract from.
 * @param b The integer to subtract.
 * @throws std::overflow_error If the result of the subtraction overflows the maximum or underflows the minimum integer value.
 * @return The difference of the two integers.
 */
int sub_ints(int a, int b) {
    if (b < 0 && a > std::numeric_limits<int>::max() + b) {
        throw std::overflow_error("Integer overflow");
    }
    if (b > 0 && a < std::numeric_limits<int>::min() + b) {
        throw std::overflow_error("Integer underflow");
    }
    return a - b;
}

/**
 * Multiplies two integers and checks for integer overflow.
 * Multiplies two integers and checks if the result exceeds the maximum integer value that can be represented in the given data type.
 * If integer overflow occurs, throws an exception with an error message.
 * Returns the product of the two integers.
 * @param a The first integer to multiply.
 * @param b The second integer to multiply.
 * @return The product of the two integers.
 * @throws std::overflow_error If integer overflow occurs.
 */
int mul_ints(int a, int b) {

    if (a > 0 && b > 0 && a > std::numeric_limits<int>::max() / b) {
        throw std::overflow_error("Integer overflow");
    }
    if (a < 0 && b < 0 && a < std::numeric_limits<int>::max() / b) {
        throw std::overflow_error("Integer overflow");
    }
    return a * b;
}

int Fraction::getNumerator() const {
    return numerator;
}

int Fraction::getDenominator() const {
    return denominator;
}

/**
 * Constructs a Fraction object with the given numerator and denominator.
 * If the denominator is negative, the sign is inverted for both the numerator and denominator.
 * If the denominator is 0, an invalid_argument exception is thrown.
 * The constructor reduces the fraction to its simplest form by dividing both the numerator and denominator by their greatest common divisor.
 * @param n The numerator of the fraction.
 * @param d The denominator of the fraction.
 * @throws std::invalid_argument If the denominator is 0.
 */
Fraction::Fraction(int n, int d) {
    if (d < 0) {
        d = d * (-1);
        n = n * (-1);
    } else if (d == 0) {
        throw invalid_argument("0");
    }

    int sign = n * d < 0 ? -1 : 1;
    int gcd = __gcd(n, d);
    numerator = abs(n / gcd) * sign;
    denominator = abs(d / gcd);
}

/**
 * Constructs a Fraction object from a floating-point value.
 * Uses the floatToFraction function to convert the floating-point value to a Fraction object.
 * Sets the numerator and denominator of the Fraction object to the numerator and denominator of the resulting Fraction object.
 * @param f The floating-point value to convert to a Fraction object.
 */
Fraction::Fraction(float f) {
    Fraction temp = floatToFraction(f);
    numerator = temp.getNumerator();
    denominator = temp.getDenominator();
}

Fraction::Fraction() {
    numerator = 0;
    denominator = 1;
}

/**
 * Overloads the << operator to enable printing a Fraction object to an output stream.
 * The Fraction object is printed as "numerator/denominator".
 * @param out The output stream to write the Fraction object to.
 * @param c The Fraction object to print.
 * @return The output stream after writing the Fraction object to it.
 */
std::ostream &operator<<(std::ostream &out, const Fraction &c) {
    return out << c.getNumerator() << '/' << c.getDenominator();
}

/**
 * Overloads the >> operator to enable reading a Fraction object from an input stream.
 * Reads the input stream for a numerator and a denominator, separated by a slash (/) or a space.
 * Sets the numerator and denominator of the Fraction object accordingly.
 * If the input is not a valid fraction, throws an exception.
 * @param in The input stream to read the Fraction object from.
 * @param fraction The Fraction object to populate with the input.
 * @throws std::invalid_argument If the input is not a valid fraction or only one argument is provided.
 * @throws std::runtime_error If the numerator or denominator is not a valid integer, or if the denominator is initialized by 0, or if a float is passed as denominator.
 * @return The input stream after reading the Fraction object from it.
 */
std::istream &operator>>(std::istream &in, Fraction &fraction) {
    string input;
    char c;

    // Read numerator
    while (in.get(c)) {
        if (c == '/' || c == ' ' || c == ',') {
            break;
        }
        if (c == '.') throw runtime_error("Invalid argument, numerator is not a valid integer.");
        input += c;
    }
    try {
        fraction.numerator = std::stoi(input);
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Invalid argument, numerator is not a valid integer.");
    }

    // Read denominator
    input = "";
    while (in.get(c)) {
        if (c == '\n' || c == '\r' || c == ' ') {
            break;
        }
        if (c == '.') throw runtime_error("Invalid argument, cannot initialize float as denominator.");
        input += c;
    }
    if (input == "0") throw runtime_error("Denominator initialize by 0 is not defined.");
    if (input.empty()) throw invalid_argument("Invalid argument, only one argument provided.");
    fraction.denominator = stoi(input);

    int sign = fraction.numerator * fraction.denominator < 0 ? -1 : 1;
    fraction.numerator = abs(fraction.numerator) * sign;
    fraction.denominator = abs(fraction.denominator);
    return in;
}

/**
 * Overloads the + operator to enable adding two Fraction objects.
 * Calculates the least common multiple of the two denominators.
 * Multiplies each numerator by the LCM over its original denominator.
 * Adds the resulting numerators together using the add_ints function to check for integer overflow and underflow.
 * Returns a new Fraction object with the resulting numerator and LCM as the numerator and denominator, respectively.
 * @param other The Fraction object to add to this Fraction object.
 * @return A new Fraction object that is the sum of this Fraction object and the other Fraction object.
 */
Fraction Fraction::operator+(const Fraction &other) const {

    int lcm = (denominator * other.getDenominator()) / __gcd(denominator, other.getDenominator());

    int new_num1 = numerator * (lcm / denominator);
    int new_num2 = other.getNumerator() * (lcm / other.getDenominator());

    int result_num = add_ints(new_num1, new_num2);

    return {result_num, lcm};
}

/**
 * Overloads the - operator to enable subtracting two Fraction objects.
 * Calculates the least common multiple of the two denominators.
 * Multiplies each numerator by the LCM over its original denominator.
 * Subtracts the resulting numerators using the sub_ints function to check for integer overflow and underflow.
 * Returns a new Fraction object with the resulting numerator and LCM as the numerator and denominator, respectively.
 * @param other The Fraction object to subtract from this Fraction object.
 * @return A new Fraction object that is the difference between this Fraction object and the other Fraction object.
 */
Fraction Fraction::operator-(const Fraction &other) const {

    int lcm = (denominator * other.getDenominator()) / __gcd(denominator, other.getDenominator());

    int new_num1 = numerator * (lcm / denominator);
    int new_num2 = other.getNumerator() * (lcm / other.getDenominator());

    int result_num = sub_ints(new_num1, new_num2);

    return {result_num, lcm};
}

/**
 * Overloads the / operator to enable dividing two Fraction objects.
 * Checks if the divisor is 0, and throws an exception if it is.
 * Divides the numerator of this Fraction object by the denominator of the other Fraction object.
 * Divides the denominator of this Fraction object by the numerator of the other Fraction object.
 * Returns a new Fraction object with the resulting numerator and denominator.
 * @param other The Fraction object to divide this Fraction object by.
 * @throws std::runtime_error If the other Fraction object is equal to 0.
 * @return A new Fraction object that is the quotient of this Fraction object divided by the other Fraction object.
 */
Fraction Fraction::operator/(const Fraction &other) const {
    if (other == 0) throw runtime_error("Division by 0 is not defined.");
    return {mul_ints(numerator, other.getDenominator()), mul_ints(denominator, other.getNumerator())};
}

/**
 * Overloads the * operator to enable multiplying two Fraction objects.
 * Multiplies the numerator of this Fraction object by the numerator of the other Fraction object.
 * Multiplies the denominator of this Fraction object by the denominator of the other Fraction object.
 * Returns a new Fraction object with the resulting numerator and denominator.
 * @param other The Fraction object to multiply this Fraction object by.
 * @return A new Fraction object that is the product of this Fraction object and the other Fraction object.
 */
Fraction Fraction::operator*(const Fraction &other) const {

    return {mul_ints(numerator, other.getNumerator()), mul_ints(denominator, other.getDenominator())};
}

/**
 * Overloads the == operator to enable comparing two Fraction objects for equality.
 * Compares the numerator and denominator of this Fraction object to the numerator and denominator of the other Fraction object.
 * Returns true if they are equal, false otherwise.
 * Special case: returns true if both fractions are 0.
 * @param other The Fraction object to compare this Fraction object to.
 * @return True if the two Fraction objects are equal, false otherwise.
 */
bool Fraction::operator==(const Fraction &other) const {

    if ((numerator == other.getNumerator() && denominator == other.getDenominator()) ||
        ((*this).numerator == 0 && other.getNumerator() == 0))
        return true;
    return false;
}

/**
 * Overloads the pre-increment operator to enable incrementing a Fraction object by one.
 * Adds the denominator to the numerator of this Fraction object.
 * Returns a reference to this Fraction object.
 * @return A reference to this Fraction object after being incremented by one.
 */
Fraction &Fraction::operator++() {
    numerator += denominator;
    return *this;
}

/**
 * Overloads the pre-decrement operator to enable decrementing a Fraction object by one.
 * Subtracts the denominator from the numerator of this Fraction object.
 * Returns a reference to this Fraction object.
 * @return A reference to this Fraction object after being decremented by one.
 */
Fraction &Fraction::operator--() {
    numerator -= denominator;
    return *this;
}

/**
 * Overloads the > operator to enable comparing two Fraction objects for greater-than.
 * Checks if the denominators of this Fraction object and the other Fraction object are equal.
 * If they are, compares the numerators of this Fraction object and the other Fraction object.
 * If the numerator of this Fraction object is greater than the numerator of the other Fraction object, returns true.
 * Otherwise, calculates the LCM of the denominators, multiplies the numerators by the LCM over their original denominator, and compares the resulting numerators.
 * Returns true if the numerator of this Fraction object is greater than the numerator of the other Fraction object, false otherwise.
 * @param other The Fraction object to compare this Fraction object to.
 * @return True if this Fraction object is greater than the other Fraction object, false otherwise.
 */
bool Fraction::operator>(const Fraction &other) const {
    if (denominator == other.getDenominator()) {
        if (numerator > other.getNumerator()) return true;
    }
    int LCM = lcm(other);
    int new_num1 = numerator * (LCM / denominator);
    int new_num2 = other.getNumerator() * (LCM / other.getDenominator());
    return new_num1 > new_num2;
}

/**
 * Overloads the < operator to enable comparing two Fraction objects for less-than.
 * Checks if the denominators of this Fraction object and the other Fraction object are equal.
 * If they are, compares the numerators of this Fraction object and the other Fraction object.
 * If the numerator of this Fraction object is less than the numerator of the other Fraction object, returns true.
 * Otherwise, calculates the LCM of the denominators, multiplies the numerators by the LCM over their original denominator, and compares the resulting numerators.
 * Returns true if the numerator of this Fraction object is less than the numerator of the other Fraction object, false otherwise.
 * @param other The Fraction object to compare this Fraction object to.
 * @return True if this Fraction object is less than the other Fraction object, false otherwise.
 */
bool Fraction::operator<(const Fraction &other) const {
    if (denominator == other.getDenominator()) {
        if (numerator < other.getNumerator()) return true;
    }
    int LCM = lcm(other);
    int new_num1 = numerator * (LCM / denominator);
    int new_num2 = other.getNumerator() * (LCM / other.getDenominator());
    return new_num1 < new_num2;
}

/**
 * Overloads the >= operator to enable comparing two Fraction objects for greater-than or equal-to.
 * Checks if the denominators of this Fraction object and the other Fraction object are equal.
 * If they are, compares the numerators of this Fraction object and the other Fraction object for greater-than or equal-to.
 * If the numerator of this Fraction object is greater than or equal to the numerator of the other Fraction object, returns true.
 * Otherwise, multiplies the numerators of this Fraction object and the other Fraction object by the opposite denominator and compares the resulting numerators for greater-than or equal-to.
 * Returns true if the numerator of this Fraction object is greater than or equal to the numerator of the other Fraction object, false otherwise.
 * @param other The Fraction object to compare this Fraction object to.
 * @return True if this Fraction object is greater than or equal to the other Fraction object, false otherwise.
 */
bool Fraction::operator>=(const Fraction &other) const {
    if (denominator == other.getDenominator()) {
        if (numerator >= other.getNumerator()) return true;
    }

    int new_num1 = numerator * other.getDenominator();
    int new_num2 = other.getNumerator() * denominator;

    return new_num1 >= new_num2;
}

/**
 * Overloads the <= operator to enable comparing two Fraction objects for less-than or equal-to.
 * Checks if the denominators of this Fraction object and the other Fraction object are equal.
 * If they are, compares the numerators of this Fraction object and the other Fraction object for less-than or equal-to.
 * If the numerator of this Fraction object is less than or equal to the numerator of the other Fraction object, returns true.
 * Otherwise, multiplies the numerators of this Fraction object and the other Fraction object by the opposite denominator and compares the resulting numerators for less-than or equal-to.
 * Returns true if the numerator of this Fraction object is less than or equal to the numerator of the other Fraction object, false otherwise.
 * @param other The Fraction object to compare this Fraction object to.
 * @return True if this Fraction object is less than or equal to the other Fraction object, false otherwise.
 */
bool Fraction::operator<=(const Fraction &other) const {
    if (denominator == other.getDenominator()) {
        if (numerator <= other.getNumerator()) return true;
    }

    int new_num1 = numerator * other.getDenominator();
    int new_num2 = other.getNumerator() * denominator;

    return new_num1 <= new_num2;
}

/**
 * Overloads the > operator to enable comparing a Fraction object to a float value for greater-than.
 * Converts the float value to a Fraction object using the floatToFraction() function.
 * If the denominators of this Fraction object and the other Fraction object are equal, compares the numerators of this Fraction object and the other Fraction object for greater-than.
 * If the numerator of this Fraction object is greater than the numerator of the other Fraction object, returns true.
 * Otherwise, multiplies the numerators of this Fraction object and the other Fraction object by the opposite denominator and compares the resulting numerators for greater-than.
 * Returns true if the numerator of this Fraction object is greater than the numerator of the other Fraction object, false otherwise.
 * @param other The float value to compare this Fraction object to.
 * @return True if this Fraction object is greater than the other float value, false otherwise.
 */
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

/**
 * Overloads the < operator to enable comparing a Fraction object to a float value for less-than.
 * Converts the float value to a Fraction object using the floatToFraction() function.
 * If the denominators of this Fraction object and the other Fraction object are equal, compares the numerators of this Fraction object and the other Fraction object for less-than.
 * If the numerator of this Fraction object is less than the numerator of the other Fraction object, returns true.
 * Otherwise, multiplies the numerators of this Fraction object and the other Fraction object by the opposite denominator and compares the resulting numerators for less-than.
 * Returns true if the numerator of this Fraction object is less than the numerator of the other Fraction object, false otherwise.
 * @param other The float value to compare this Fraction object to.
 * @return True if this Fraction object is less than the other float value, false otherwise.
 */
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

/**
 * Overloads the >= operator to enable comparing a Fraction object to a float value for greater-than or equal-to.
 * Converts the float value to a Fraction object using the floatToFraction() function.
 * If the denominators of this Fraction object and the other Fraction object are equal, compares the numerators of this Fraction object and the other Fraction object for greater-than or equal-to.
 * If the numerator of this Fraction object is greater than or equal to the numerator of the other Fraction object, returns true.
 * Otherwise, multiplies the numerators of this Fraction object and the other Fraction object by the opposite denominator and compares the resulting numerators for greater-than or equal-to.
 * Returns true if the numerator of this Fraction object is greater than or equal to the numerator of the other Fraction object, false otherwise.
 * @param other The float value to compare this Fraction object to.
 * @return True if this Fraction object is greater than or equal to the other float value, false otherwise.
 */
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

/**
 * Overloads the <= operator to enable comparing a Fraction object to a float value for less-than or equal-to.
 * Converts the float value to a Fraction object using the floatToFraction() function.
 * If the denominators of this Fraction object and the other Fraction object are equal, compares the numerators of this Fraction object and the other Fraction object for less-than or equal-to.
 * If the numerator of this Fraction object is less than or equal to the numerator of the other Fraction object, returns true.
 * Otherwise, multiplies the numerators of this Fraction object and the other Fraction object by the opposite denominator and compares the resulting numerators for less-than or equal-to.
 * Returns true if the numerator of this Fraction object is less than or equal to the numerator of the other Fraction object, false otherwise.
 * @param other The float value to compare this Fraction object to.
 * @return True if this Fraction object is less than or equal to the other float value, false otherwise.
 */
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

/**
 * Overloads the + operator to enable adding a float value to a Fraction object.
 * Converts the float value to a Fraction object using the floatToFraction() function, then adds it to this Fraction object.
 * Returns a new Fraction object that represents the sum of the two numbers.
 * @param other The float value to add to this Fraction object.
 * @return A new Fraction object that represents the sum of this Fraction object and the float value.
 */
Fraction Fraction::operator+(float other) const {
    Fraction f = floatToFraction(other) + (*this);
    return f;
}

/**
 * Overloads the - operator to enable subtracting a float value from a Fraction object.
 * Converts the float value to a Fraction object using the floatToFraction() function, then subtracts it from this Fraction object.
 * Returns a new Fraction object that represents the difference between the two numbers.
 * @param other The float value to subtract from this Fraction object.
 * @return A new Fraction object that represents the difference between this Fraction object and the float value.
 */
Fraction Fraction::operator-(float other) const {
    Fraction f = (*this) - floatToFraction(other);
    return f;
}

/**
 * Overloads the / operator to enable dividing a Fraction object by a float value.
 * Converts the float value to a Fraction object using the floatToFraction() function, then divides this Fraction object by the resulting Fraction object.
 * Returns a new Fraction object that represents the quotient of the two numbers.
 * @param other The float value to divide this Fraction object by.
 * @return A new Fraction object that represents the quotient of this Fraction object and the float value.
 * @throws runtime_error if other is 0, as division by 0 is not defined.
 */
Fraction Fraction::operator/(float other) const {
    if (other == 0) throw runtime_error("Division by 0 is not defined.");
    Fraction f = (*this) / floatToFraction(other);
    return f;
}

/**
 * Overloads the == operator to enable comparing a Fraction object to a float value.
 * Converts the float value to a Fraction object using the floatToFraction() function, then compares the resulting Fraction object to this Fraction object.
 * Returns true if the two numbers are equal, false otherwise.
 * @param other The float value to compare to this Fraction object.
 * @return True if this Fraction object and the float value are equal, false otherwise.
 */
bool Fraction::operator==(float other) const {
    Fraction f = floatToFraction(other);
    return f == (*this);
}

/**
 * Overloads the * operator to enable multiplying a Fraction object by a float value.
 * Converts the float value to a Fraction object using the floatToFraction() function, then multiplies this Fraction object by the resulting Fraction object.
 * Returns a new Fraction object that represents the product of the two numbers.
 * @param other The float value to multiply this Fraction object by.
 * @return A new Fraction object that represents the product of this Fraction object and the float value.
 */
Fraction Fraction::operator*(float other) const {
    Fraction f = floatToFraction(other) * (*this);
    return f;
}

/**
 * Overloads the * operator to enable multiplying a float value by a Fraction object.
 * Converts the float value to a Fraction object using the floatToFraction() function, then multiplies the resulting Fraction object by the input Fraction object.
 * Returns a new Fraction object that represents the product of the two numbers.
 * @param value The float value to multiply the input Fraction object by.
 * @param f The Fraction object to be multiplied by the float value.
 * @return A new Fraction object that represents the product of the float value and the input Fraction object.
 */
Fraction operator*(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value) * f;
    return t;
}

/**
 * Overloads the post-increment operator to increase the value of the Fraction object by 1/1.
 * Creates a temporary copy of the current Fraction object, increases the numerator by the denominator, and returns the temporary copy.
 * @param int Dummy parameter to distinguish the post-increment operator overload function from the pre-increment operator overload function.
 * @return A copy of the current Fraction object before it was incremented by 1/1.
 */
Fraction Fraction::operator++(int) {
    Fraction temp(numerator, denominator);
    numerator += denominator;
    return temp;
}

/**
 * Overloads the post-decrement operator to decrease the value of the Fraction object by 1/1.
 * Creates a temporary copy of the current Fraction object, decreases the numerator by the denominator, and returns the temporary copy.
 * @param int Dummy parameter to distinguish the post-decrement operator overload function from the pre-decrement operator overload function.
 * @return A copy of the current Fraction object before it was decremented by 1/1.
 */
Fraction Fraction::operator--(int) {
    Fraction temp(numerator, denominator);
    numerator -= denominator;
    return temp;
}

/**
 * Overloads the division operator to divide a float value by a Fraction object.
 * Converts the float value to a Fraction using the floatToFraction() function and performs the division using the Fraction class division operator.
 * @param value The float value to be divided by the Fraction object.
 * @param f The Fraction object to divide the float value by.
 * @return A new Fraction object that represents the result of the division.
 * @throws std::runtime_error if the Fraction object is equal to 0, as division by 0 is not defined.
 */
Fraction operator/(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value) / f;
    return t;
}

/**
 * Overloads the equality operator to check if a float value is equal to a Fraction object.
 * Converts the float value to a Fraction using the floatToFraction() function and performs the equality check using the Fraction class equality operator.
 * @param value The float value to be compared with the Fraction object.
 * @param f The Fraction object to be compared with the float value.
 * @return True if the float value is equal to the Fraction object, false otherwise.
 */
bool operator==(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value);
    return t == f;
}

/**
 * Overloads the inequality operator to check if a Fraction object is not equal to another Fraction object.
 * Uses the Fraction class equality operator to check if the two Fraction objects are equal, and returns the negation of the result.
 * @param other The Fraction object to be compared with.
 * @return True if the Fraction object is not equal to the other Fraction object, false otherwise.
 */
bool Fraction::operator!=(const Fraction &other) const {
    return !((*this) == other);
}

/**
 * Overloads the inequality operator to check if a Fraction object is not equal to a float value.
 * Converts the float value to a Fraction using the floatToFraction() function and uses the Fraction class equality operator to check if the two Fraction objects are equal, and returns the negation of the result.
 * @param other The float value to be compared with the Fraction object.
 * @return True if the Fraction object is not equal to the float value, false otherwise.
 */
bool Fraction::operator!=(float other) const {
    Fraction f = Fraction::floatToFraction(other);
    return (*this) != f;
}

/**
 * Overload of the inequality operator to compare a float and a Fraction.
 *
 * @param value The float value to be compared with the Fraction.
 * @param f The Fraction to be compared with the float value.
 * @return True if the float value and the Fraction are not equal, false otherwise.
 */
bool operator!=(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value);
    return f != t;
}

/**
 * Overloaded comparison operator that checks if a float value is greater than a fraction.
 *
 * @param value A float value to compare with the fraction.
 * @param f The fraction to compare with the float value.
 * @return True if the float value is greater than the fraction, false otherwise.
 */
bool operator>(float value, const Fraction &f) {
    Fraction t = Fraction::floatToFraction(value);
    return t > f;
}

/**
 * Overloaded addition operator that adds a float value to a fraction.
 *
 * @param value A float value to add to the fraction.
 * @param f The fraction to add to the float value.
 * @return The sum of the float value and the fraction as a new fraction.
 */
Fraction operator+(float value, const Fraction &f) {
    // Convert the float value to a fraction.
    Fraction t = Fraction::floatToFraction(value);

    // Add the two fractions using the "+" operator.
    return t + f;
}

/**
 * Overloaded subtraction operator that subtracts a fraction from a float value.
 *
 * @param value A float value to subtract the fraction from.
 * @param f The fraction to subtract from the float value.
 * @return The difference between the float value and the fraction as a new fraction.
 */
Fraction operator-(float value, const Fraction &f) {
    // Convert the float value to a fraction.
    Fraction t = Fraction::floatToFraction(value);

    // Subtract the fraction from the float value using the "-" operator.
    return t - f;
}

/**
 * Overloaded comparison operator that checks if a float value is less than a fraction.
 *
 * @param value A float value to compare with the fraction.
 * @param f The fraction to compare with the float value.
 * @return True if the float value is less than the fraction, false otherwise.
 */
bool operator<(float value, const Fraction &f) {
    // Convert the float value to a fraction.
    Fraction t = Fraction::floatToFraction(value);

    // Compare the two fractions using the "<" operator.
    return t < f;
}

/**
 * Overloaded comparison operator that checks if a float value is greater than or equal to a fraction.
 *
 * @param value A float value to compare with the fraction.
 * @param f The fraction to compare with the float value.
 * @return True if the float value is greater than or equal to the fraction, false otherwise.
 */
bool operator>=(float value, const Fraction &f) {
    // Convert the float value to a fraction.
    Fraction t = Fraction::floatToFraction(value);

    // Compare the two fractions using the ">=" operator.
    return t >= f;
}

/**
 * Overloaded comparison operator that checks if a float value is less than or equal to a fraction.
 *
 * @param value A float value to compare with the fraction.
 * @param f The fraction to compare with the float value.
 * @return True if the float value is less than or equal to the fraction, false otherwise.
 */
bool operator<=(float value, const Fraction &f) {
    // Convert the float value to a fraction.
    Fraction t = Fraction::floatToFraction(value);

    // Compare the two fractions using the "<=" operator.
    return t <= f;
}