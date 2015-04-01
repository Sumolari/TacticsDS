// Copyright 2015 FMAW

#include "./fmaw_fixedreal.h"

#include <stdexcept>

namespace FMAW {

FixedReal::FixedReal() : num {0}, fraction_size {8} {}

FixedReal::FixedReal(short int fs) {
    if (fs < 0 || fs > 31)
        throw std::length_error {"Precision cannot be bigger than "
                                 "31 bits and it cannot be negative"
                                };

    num = 0;
    fraction_size = fs;
}

FixedReal::FixedReal(int n, short int fs) {
    if (fs < 0 || fs > 31)
        throw std::length_error {"Precision cannot be bigger than "
                                 "31 bits and it cannot be negative"
                                };

    num = n << fs;
    fraction_size = fs;
}

FixedReal::FixedReal(double d, short int fs) {
    if (fs < 0 || fs > 31)
        throw std::length_error {"Precision cannot be bigger than "
                                 "31 bits and it cannot be negative"
                                };

    num = d * (1 << fs);
    fraction_size = fs;
}

FixedReal &FixedReal::operator+=(const FixedReal x) {
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

FixedReal FixedReal::operator+(const FixedReal x) {
    FixedReal res(fraction_size);
    if (fraction_size > x.fraction_size) {
        res.num = num + (x.num << (fraction_size - x.fraction_size));
    } else if (fraction_size < x.fraction_size) {
        res.num = num + (x.num >> (x.fraction_size - fraction_size));
    } else {
        res.num = num + x.num;
    }

    return res;
}

FixedReal FixedReal::operator+(const int x) {
    FixedReal res(x, 1);

    return (*this + res);
}

FixedReal FixedReal::operator+(const double x) {
    FixedReal res(x, 8);

    return (*this + res);
}

FixedReal &FixedReal::operator-=(const FixedReal x) {
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

FixedReal FixedReal::operator-(const FixedReal x) {
    FixedReal res(fraction_size);
    if (fraction_size > x.fraction_size) {
        res.num = num - (x.num << (fraction_size - x.fraction_size));
    } else if (fraction_size < x.fraction_size) {
        res.num = num - (x.num >> (x.fraction_size - fraction_size));
    } else {
        res.num = num - x.num;
    }

    return res;
}

FixedReal FixedReal::operator-(const int x) {
    FixedReal res(x, 1);

    return (*this - res);
}

FixedReal FixedReal::operator-(const double x) {
    FixedReal res(x, 8);

    return (*this - res);
}

FixedReal &FixedReal::operator*=(const FixedReal x) {
    this->num = (this->num * x.num) >> x.fraction_size;

    return *this;
}

FixedReal FixedReal::operator*(const FixedReal x) {
    FixedReal res(fraction_size);
    res.num = (num * x.num) >> x.fraction_size;

    return res;
}

FixedReal FixedReal::operator*(const int x) {
    FixedReal res(x, 1);

    return (*this * res);
}

FixedReal FixedReal::operator*(const double x) {
    FixedReal res(x, 8);

    return (*this * res);
}

FixedReal &FixedReal::operator/=(const FixedReal x) {
    int aux = (this->num) << x.fraction_size;
    this->num = aux / x.num;

    return *this;
}

FixedReal FixedReal::operator/(const FixedReal x) {
    FixedReal res(fraction_size);
    int aux = (this->num) << x.fraction_size;
    res.num = aux / x.num;

    return res;
}

FixedReal FixedReal::operator/(const int x) {
    FixedReal res(x, 1);

    return (*this / res);
}

FixedReal FixedReal::operator/(const double x) {
    FixedReal res(x, 8);

    return (*this / res);
}

int FixedReal::raw() const {
    return this->num;
}

int FixedReal::toInt() const {
    int res = this->num >> this->fraction_size;
    return res;
}

FixedReal::operator int() const {
    return this->toInt();
}

double FixedReal::toDouble() const {
    double res = static_cast<double>(this->num) / (1 << this->fraction_size);
    return res;
}

FixedReal::operator double() const {
    return this->toDouble();
}

bool FixedReal::operator==(const FixedReal x) const {
    bool res;
    if (fraction_size > x.fraction_size) {
        res = num == (x.num << (fraction_size - x.fraction_size));
    } else if (fraction_size < x.fraction_size) {
        res = num == (x.num >> (x.fraction_size - fraction_size));
    } else {
        res = num == x.num;
    }

    return res;
}

bool FixedReal::operator!=(const FixedReal x) const {
    bool res;
    if (fraction_size > x.fraction_size) {
        res = num != (x.num << (fraction_size - x.fraction_size));
    } else if (fraction_size < x.fraction_size) {
        res = num != (x.num >> (x.fraction_size - fraction_size));
    } else {
        res = num != x.num;
    }

    return res;
}

bool FixedReal::operator>(const FixedReal x) const {
    bool res;
    if (fraction_size > x.fraction_size) {
        res = num > (x.num << (fraction_size - x.fraction_size));
    } else if (fraction_size < x.fraction_size) {
        res = num > (x.num >> (x.fraction_size - fraction_size));
    } else {
        res = num > x.num;
    }

    return res;
}

bool FixedReal::operator<(const FixedReal x) const {
    bool res;
    if (fraction_size > x.fraction_size) {
        res = num < (x.num << (fraction_size - x.fraction_size));
    } else if (fraction_size < x.fraction_size) {
        res = num < (x.num >> (x.fraction_size - fraction_size));
    } else {
        res = num < x.num;
    }

    return res;
}

bool FixedReal::operator>=(const FixedReal x) const {
    bool res;
    if (fraction_size > x.fraction_size) {
        res = num >= (x.num << (fraction_size - x.fraction_size));
    } else if (fraction_size < x.fraction_size) {
        res = num >= (x.num >> (x.fraction_size - fraction_size));
    } else {
        res = num >= x.num;
    }

    return res;
}

bool FixedReal::operator<=(const FixedReal x) const {
    bool res;
    if (fraction_size > x.fraction_size) {
        res = num <= (x.num << (fraction_size - x.fraction_size));
    } else if (fraction_size < x.fraction_size) {
        res = num <= (x.num >> (x.fraction_size - fraction_size));
    } else {
        res = num <= x.num;
    }

    return res;
}

std::ostream &operator<<(std::ostream &strm, const FixedReal &a) {
    return strm << a.raw();
}

}  // namespace FMAW
