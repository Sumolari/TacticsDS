#ifndef FMAW_TYPES_H
#define FMAW_TYPES_H

typedef unsigned char uint8;
typedef unsigned short int uint16;

#include <iostream>
using namespace std;

/**
 * Basic type for Fixed Point operations. E is the amount of bits allocated for
 * the DECIMAL part.
 */
template<int E>
struct BasicFixedReal
{
    typedef BasicFixedReal self;
    static const int factor = 1 << (E - 1);
    BasicFixedReal() : m(0) { }
    BasicFixedReal(double d) : m(static_cast<double>(d *factor)) { }
    self &operator+=(const self &x) {
        m += x.m;
        return *this;
    }
    self &operator-=(const self &x) {
        m -= x.m;
        return *this;
    }
    self &operator*=(const self &x) {
        m *= x.m;
        m >>= E;
        return *this;
    }
    self &operator/=(const self &x) {
        m /= x.m;
        m *= factor;
        return *this;
    }
    self &operator*=(int x) {
        m *= x;
        return *this;
    }
    self &operator/=(int x) {
        m /= x;
        return *this;
    }
    self operator-() {
        return self(-m);
    }
    double toDouble() const {
        return double(m) / factor;
    }
    // friend functions
    friend self operator+(self x, const self &y) {
        return x += y;
    }
    friend self operator-(self x, const self &y) {
        return x -= y;
    }
    friend self operator*(self x, const self &y) {
        return x *= y;
    }
    friend self operator/(self x, const self &y) {
        return x /= y;
    }
    // comparison operators
    friend bool operator==(const self &x, const self &y) {
        return x.m == y.m;
    }
    friend bool operator!=(const self &x, const self &y) {
        return x.m != y.m;
    }
    friend bool operator>(const self &x, const self &y) {
        return x.m > y.m;
    }
    friend bool operator<(const self &x, const self &y) {
        return x.m < y.m;
    }
    friend bool operator>=(const self &x, const self &y) {
        return x.m >= y.m;
    }
    friend bool operator<=(const self &x, const self &y) {
        return x.m <= y.m;
    }
private:
    int m;
};

typedef BasicFixedReal<8> FixedReal;

#endif