#ifndef FMAW_FIXEDREAL_H
#define FMAW_FIXEDREAL_H

#include <iostream>

namespace FMAW {

class FixedReal {
private:
    int num;
    short int fraction_size;
public:
    /**
     *  Creates a FixedReal instance with precision (32-fs).fs and
     *  an initial value of d.
     *
     *  Warning: Precision loss is to be expected
     */
    FixedReal(double d, short int fs);

    /**
     *  Creates a FixedReal instance with precision (32-fs).fs and
     *  an initial value of (n).0.
     */
    FixedReal(int n, short int fs);

    /**
     *  Creates a FixedReal instance with precision (32-fs).fs and
     *  an initial value of 0.0.
     */
    FixedReal(short int fs);

    /**
     *  Creates a FixedReal instance with precision 24.8 and
     *  an initial value of 0.0.
     */
    FixedReal();

    /**
     *  Adds x to this instance of FixedReal, modifying its value, and
     *  returns a reference to this instance. In case of non-matching
     *  precisions, the one on this instance is preserved.
     */
    FixedReal &operator+=(const FixedReal x);

    /**
     *  Adds x to this instance of FixedReal and returns the result. In case of
     *  non-matching precisions, the one on this instance is preserved.
     */
    FixedReal operator+(const FixedReal x);
    FixedReal operator+(const int x);
    FixedReal operator+(const double x);

    /**
     *  Substracts x to this instance of FixedReal. In case of
     *  non-matching precisions, the one on this instance is preserved.
     */
    FixedReal &operator-=(const FixedReal x);

    /**
     *  Substracts x to this instance of FixedReal and returns the result.
     *  In case of non-matching precisions, the one on this instance
     *  is preserved.
     */
    FixedReal operator-(const FixedReal x);
    FixedReal operator-(const int x);
    FixedReal operator-(const double x);

    /**
     *  Multiplies x to this instance of FixedReal. The precision of
     *  this instance is preserved.
     */
    FixedReal &operator*=(const FixedReal x);

    /**
     *  Multiplies x to this instance of FixedReal and returns the result.
     *  The precision of this instance is the one preserved.
     */
    FixedReal operator*(const FixedReal x);
    FixedReal operator*(const int x);
    FixedReal operator*(const double x);

    /**
     *  Divides this instance of FixedReal by x. The precision of
     *  this instance is preserved.
     */
    FixedReal &operator/=(const FixedReal x);
    /**
     *  Divides this instance of FixedReal by x and returns the result.
     *  The precision of this instance is preserved.
     */
    FixedReal operator/(const FixedReal x);
    FixedReal operator/(const int x);
    FixedReal operator/(const double x);

    /**
     *  Returns the FixedReal value as is, without converting to any type.
     */
    int raw() const;

    /**
     *  Returns the FixedReal value converted to natural integer.
     */
    int toInt() const;

    /**
     *  Overloads int casting operator. Calls toInt() method.
     */
    operator int() const;

    /**
     *  Returns the FixedReal value converted to natural double.
     *
     *  Warning: Precision loss is to be expected.
     */
    double toDouble() const;

    /**
     *  Overloads double casting operator. Calls toDouble() method.
     */
    operator double() const;

    /**
     *  Returns true if FixedReal x is equal to this instance of FixedReal.
     *  False otherwise.
     */
    bool operator==(const FixedReal x) const;

    /**
     *  Returns false if FixedReal x is equal to this instance of FixedReal.
     *  True otherwise.
     */
    bool operator!=(const FixedReal x) const;

    /**
     *  Returns true if this instance of FixedReal is greater than FixedReal x.
     *  False otherwise.
     */
    bool operator>(const FixedReal x) const;

    /**
     *  Returns true if this instance of FixedReal is lesser than FixedReal x.
     *  False otherwise.
     */
    bool operator<(const FixedReal x) const;

    /**
     *  Returns true if this instance of FixedReal is greater than  or equal to
     *  FixedReal x. False otherwise.
     */
    bool operator>=(const FixedReal x) const;

    /**
     *  Returns true if this instance of FixedReal is lesser than  or equal to
     *  FixedReal x. False otherwise.
     */
    bool operator<=(const FixedReal x) const;

    friend std::ostream &operator<<(std::ostream &strm, const FixedReal &a);
};

}

#endif