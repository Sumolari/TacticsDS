#ifndef FMAW_FIXEDREAL_H
#define FMAW_FIXEDREAL_H

class fixedreal {
private:
  int num;
  short int fraction_size;
public:
  fixedreal(double d, short int fs); // fixedreal (32-fs).fs with value d
  //fixedreal(double d);  // fixedreal 24.8 with value d
  fixedreal(int n, short int fs); // fixedreal (32-fs).fs with value (n).0
  //fixedreal(int n); // fixedreal 24.8 with value (n).0
  fixedreal(short int fs);  // fixedreal (32-fs).fs with value 0.0
  fixedreal();      // fixedreal 24.8 with value 0.0
  
  fixedreal& operator+=(const fixedreal x); // add x to self
  fixedreal& operator-=(const fixedreal x); // substract x from self
  /*
  fixedreal& operator*=(const fixedreal x); // multiply self by x
  fixedreal& operator/=(const fixedreal x); // divide self by x
  */
  
  int raw() const;  // return the fixedreal number as is
  /*
  int toInt() const;  // return the integer part of the fixedreal number
  double toDouble() const;  // return the fixedreal number as a double
  */
  
  /*
  bool operator==(const self &x, const self &y);
  bool operator!=(const self &x, const self &y);
  bool operator>(const self &x, const self &y);
  bool operator<(const self &x, const self &y);
  bool operator>=(const self &x, const self &y);
  bool operator<=(const self &x, const self &y);
  */
};

#endif