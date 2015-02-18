#ifndef FMAW_FIXEDREAL_H
#define FMAW_FIXEDREAL_H

#include <iostream>

namespace FMAW {

// TODO: Remove "New" prefix from class name once it can substitute Framework's
//       previous definition of FixedReal (int).
class NewFixedReal {
private:
    int num;
    short int fraction_size;
public:
    /**
     *  Creates a NewFixedReal instance with precision (32-fs).fs and
     *  an initial value of d.
     *
     *  Warning: Precision loss is to be expected
     */
    NewFixedReal(double d, short int fs);
    //NewFixedReal(double d);  // NewFixedReal 24.8 with value d
    /**
     *  Creates a NewFixedReal instance with precision (32-fs).fs and
     *  an initial value of (n).0.
     */
    NewFixedReal(int n, short int fs);
    //NewFixedReal(int n); // NewFixedReal 24.8 with value (n).0
    /**
     *  Creates a NewFixedReal instance with precision (32-fs).fs and
     *  an initial value of 0.0.
     */
    NewFixedReal(short int fs);
    /**
     *  Creates a NewFixedReal instance with precision 24.8 and
     *  an initial value of 0.0.
     */
    NewFixedReal();

    /**
     *  Adds x to this instance of FixedReal, modifying its value, and
     *  returns a reference to this instance. In case of non-matching
     *  precisions, the one on this instance is preserved.
     */
    NewFixedReal &operator+=(const NewFixedReal x);
    /**
     *  Adds x to this instance of FixedReal and returns the result. In case of 
     *  non-matching precisions, the one on this instance is preserved.
     */
    NewFixedReal operator+(const NewFixedReal x);
    
    /**
     *  Substracts x to this instance of FixedReal. In case of 
     *  non-matching precisions, the one on this instance is preserved.
     */
    NewFixedReal &operator-=(const NewFixedReal x);
    /**
     *  Substracts x to this instance of FixedReal and returns the result.
     *  In case of non-matching precisions, the one on this instance 
     *  is preserved.
     */
    NewFixedReal operator-(const NewFixedReal x);
    /*
    // TODO: Document me properly!
    NewFixedReal& operator*=(const NewFixedReal x); // multiply self by x
    // TODO: Add support for * operator (not just *= operator).
    // TODO: Document me properly!
    NewFixedReal& operator/=(const NewFixedReal x); // divide self by x
    // TODO: Add support for / operator (not just /= operator).
    */

    /**
     *  Returns the NewFixedReal value as is, without converting to any type.
     */
    int raw() const;
    /**
     *  Returns the NewFixedReal value converted to natural integer.
     */
    int toInt() const;
    /**
     *  Overloads int casting operator. Calls toInt() method.
     */
    operator int() const;

    /**
     *  Returns the NewFixedReal value converted to natural double.
     *  
     *  Warning: Precision loss is to be expected.
     */
    double toDouble() const;
    /**
     *  Overloads double casting operator. Calls toDouble() method.
     */
    operator double() const;

    /*
    // TODO: Document me properly!
    bool operator==(const self &x, const self &y);
    // TODO: Document me properly!
    bool operator!=(const self &x, const self &y);
    // TODO: Document me properly!
    bool operator>(const self &x, const self &y);
    // TODO: Document me properly!
    bool operator<(const self &x, const self &y);
    // TODO: Document me properly!
    bool operator>=(const self &x, const self &y);
    // TODO: Document me properly!
    bool operator<=(const self &x, const self &y);
    */
};

std::ostream& operator<<(std::ostream &strm, const NewFixedReal &a) {
  return strm << a.raw();
}

}

#endif