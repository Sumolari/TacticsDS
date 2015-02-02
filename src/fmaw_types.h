#ifndef FMAW_TYPES_H
#define FMAW_TYPES_H

typedef unsigned char uint8;
typedef unsigned short int uint16;

#include <nds.h>
#include <nds/debug.h>

#include <iostream>
#include <sstream>
using namespace std;

/**
 * Basic type for Fixed Point operations. E is the amount of bits allocated for
 * the DECIMAL part.
 */
/*
template<int E>
struct BasicFixedReal
{
    typedef BasicFixedReal self;
    static const int factor = 1 << E;
    BasicFixedReal() : m(0) { }
    BasicFixedReal(double d) : m(static_cast<int>(d *factor)) { }
    static self BasicFixedRealFromRaw(int raw) {
        self newFixedReal = self();
        newFixedReal.m = raw;
        return newFixedReal;
    }
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
        m <<= E;
        m /= x.m;
        return *this;
    }
    self operator-() {
        return -m;
    }
    int raw() const {
        return m;
    }
    int toInt() const {
        return m >> E;
    }
    double toDouble() const {
        return double(m) / factor;
    }
    void print() {
        std::stringstream str;
        str << this->m;
        nocashMessage(str.str().c_str());
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
*/

typedef int FixedReal;
typedef int PreciseFixedReal;

#endif