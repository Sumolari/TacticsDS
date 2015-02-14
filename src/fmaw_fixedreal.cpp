#include "fmaw_fixedreal.h"
#include <stdexcept>
//#include <iostream>

// implementation of fixedreal's default constructor.
fixedreal::fixedreal()
    :num{0}, fraction_size{8}
{
}

// implementation of fixedreal's explicit constructor.
fixedreal::fixedreal(short int fs)
{
  if(fs < 0 || fs > 31) 
    throw std::length_error{"Precision cannot be bigger than "
    "31 bits and it cannot be negative"};
  
  num = 0;
  fraction_size = fs;
}

// implementation of fixedreal's explicit constructor.
fixedreal::fixedreal(int n, short int fs)
{
  if(fs < 0 || fs > 31) 
    throw std::length_error{"Precision cannot be bigger than "
    "31 bits and it cannot be negative"};
  
  num = n << fs;
  fraction_size = fs;
}
/*
// implementation of fixedreal's integer semiexplicit constructor.
fixedreal::fixedreal(int n)
    :num{(n << 8)}, fraction_size{8}
{
}
*/

// implementation of fixedreal's explicit constructor.
fixedreal::fixedreal(double d, short int fs)
{
  if(fs < 0 || fs > 31) 
    throw std::length_error{"Precision cannot be bigger than "
    "31 bits and it cannot be negative"};
  
  num = d * (1 << fs);
  fraction_size = fs;
}
/*
// implementation of fixedreal's integer semiexplicit constructor.
fixedreal::fixedreal(double d)
    :num{static_cast<int>(d * (1 << 8))}, fraction_size{8}
{
}
*/

// implementation of fixedreal's raw() method.
int fixedreal::raw() const{
  return fixedreal::num;
}

/*
int main(){
  fixedreal* fr = new fixedreal;
  fixedreal* fr2 = new fixedreal(24);
  fixedreal* fr3 = new fixedreal(5, 10);
  fixedreal* fr4 = new fixedreal(1.11, 8);
  
  printf("%d is a 0, just like %d.\n", fr->raw(), fr2->raw() );
  printf("%d is a 5 in 22.10 format.\n", fr3->raw() );
  printf("%d is a 1.11 in 24.8 format.\n", fr4->raw() );
  
  return 0;
}*/