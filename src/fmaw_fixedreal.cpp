// Copyright 2015 FMAW

#include "./fmaw_fixedreal.h"
#include <stdexcept>

namespace FMAW {

NewFixedReal::NewFixedReal() : num {0}, fraction_size {8} {}

NewFixedReal::NewFixedReal(short int  fs) {
    if (fs < 0 || fs > 31)
        throw std::length_error {"Precision cannot be bigger than "
                                 "31 bits and it cannot be negative"
                                };

    num = 0;
    fraction_size = fs;
}

NewFixedReal::NewFixedReal(int n, short int  fs) {
    if (fs < 0 || fs > 31)
        throw std::length_error {"Precision cannot be bigger than "
                                 "31 bits and it cannot be negative"
                                };

    num = n << fs;
    fraction_size = fs;
}

/*
NewFixedReal::NewFixedReal(int n)
    :num{(n << 8)}, fraction_size{8}{
}
*/

NewFixedReal::NewFixedReal(double d, short int  fs) {
    if (fs < 0 || fs > 31)
        throw std::length_error {"Precision cannot be bigger than "
                                 "31 bits and it cannot be negative"
                                };

    num = d * (1 << fs);
    fraction_size = fs;
}

/*
NewFixedReal::NewFixedReal(double d)
    :num{static_cast<int>(d * (1 << 8))}, fraction_size{8}{
}
*/

NewFixedReal &NewFixedReal::operator+=(const NewFixedReal x) {
    int res;
    if (fraction_size > x.fraction_size) {
        res = num + (x.num << (fraction_size - x.fraction_size));
    } else if (fraction_size < x.fraction_size) {
        res = num + (x.num >> (x.fraction_size - fraction_size));
    } else {
        res = num + x.num;
    }

    num = res;

    return *this;
}
NewFixedReal NewFixedReal::operator+(const NewFixedReal x) {
    NewFixedReal* res = new NewFixedReal(fraction_size);
    if (fraction_size > x.fraction_size) {
        res->num = num + (x.num << (fraction_size - x.fraction_size));
    } else if (fraction_size < x.fraction_size) {
        res->num = num + (x.num >> (x.fraction_size - fraction_size));
    } else {
        res->num = num + x.num;
    }

    return *res;
}

NewFixedReal &NewFixedReal::operator-=(const NewFixedReal x) {
    int res;
    if (fraction_size > x.fraction_size) {
        res = num - (x.num << (fraction_size - x.fraction_size));
    } else if (fraction_size < x.fraction_size) {
        res = num - (x.num >> (x.fraction_size - fraction_size));
    } else {
        res = num - x.num;
    }

    num = res;

    return *this;
}
NewFixedReal NewFixedReal::operator-(const NewFixedReal x) {
    NewFixedReal* res = new NewFixedReal(fraction_size);
    if (fraction_size > x.fraction_size) {
        res->num = num - (x.num << (fraction_size - x.fraction_size));
    } else if (fraction_size < x.fraction_size) {
        res->num = num - (x.num >> (x.fraction_size - fraction_size));
    } else {
        res->num = num - x.num;
    }

    return *res;
}

int NewFixedReal::raw() const {
    return this->num;
}

int NewFixedReal::toInt() const {
    int res = this->num >> this->fraction_size;
    return res;
}
NewFixedReal::operator int() const{
  return this->toInt();
}

double NewFixedReal::toDouble() const {
    double res = static_cast<double>(this->num) / (1 << this->fraction_size);
    return res;
}
NewFixedReal::operator double() const{
  return this->toDouble();
}
}  // namespace FMAW
