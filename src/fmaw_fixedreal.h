#ifndef FMAW_FIXEDREAL_H
#define FMAW_FIXEDREAL_H

namespace FMAW {

// TODO: Remove "New" prefix from class name once it can substitute Framework's
//       previous definition of FixedReal (int).
class NewFixedReal {
private:
    int num;
    short int fraction_size;
public:
    // TODO: Document me properly!
    NewFixedReal(double d, short int fs); // NewFixedReal (32-fs).fs with value d
    //NewFixedReal(double d);  // NewFixedReal 24.8 with value d
    // TODO: Document me properly!
    NewFixedReal(int n, short int fs); // NewFixedReal (32-fs).fs with value (n).0
    //NewFixedReal(int n); // NewFixedReal 24.8 with value (n).0
    // TODO: Document me properly!
    NewFixedReal(short int fs);  // NewFixedReal (32-fs).fs with value 0.0
    // TODO: Document me properly!
    NewFixedReal();      // NewFixedReal 24.8 with value 0.0

    // TODO: Document me properly!
    NewFixedReal &operator+=(const NewFixedReal x); // add x to self
    // TODO: Add support for + operator (not just += operator).
    // TODO: Document me properly!
    NewFixedReal &operator-=(const NewFixedReal x); // substract x from self
    // TODO: Add support for - operator (not just -= operator).
    /*
    // TODO: Document me properly!
    NewFixedReal& operator*=(const NewFixedReal x); // multiply self by x
    // TODO: Add support for * operator (not just *= operator).
    // TODO: Document me properly!
    NewFixedReal& operator/=(const NewFixedReal x); // divide self by x
    // TODO: Add support for / operator (not just /= operator).
    */

    // TODO: Document me properly!
    int raw() const;  // return the NewFixedReal number as is
    /*
    // TODO: Document me properly!
    int toInt() const;  // return the integer part of the NewFixedReal number
    // TODO: Document me properly!
    double toDouble() const;  // return the NewFixedReal number as a double
    */

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

}

#endif