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

int NewFixedReal::raw() const {
    return this->num;
}

/*
int main(){
  NewFixedReal* fr = new NewFixedReal;
  NewFixedReal* fr2 = new NewFixedReal(24);
  NewFixedReal* fr3 = new NewFixedReal(5, 10);
  NewFixedReal* fr4 = new NewFixedReal(1.11, 8);

  printf("%d is a 0, just like %d.\n", fr->raw(), fr2->raw() );
  printf("%d is a 5 in 22.10 format.\n", fr3->raw() );
  printf("%d is a 1.11 in 24.8 format.\n", fr4->raw() );
  *fr3 += *fr4;
  printf("%d is the sum of the two before.\n", fr3->raw() );
  *fr3 -= *fr4;
  printf("%d is a 5 in 22.10 format again.\n", fr3->raw() );

  return 0;
}*/

}  // namespace FMAW
