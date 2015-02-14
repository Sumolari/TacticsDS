#include "fmaw_fixedreal.h"
#include <iostream>

// implementation of fixedreal's default constructor.
fixedreal::fixedreal()
    :num{0}, fraction_size{8}
{
}

// implementation of fixedreal's explicit constructor.
fixedreal::fixedreal(short int fs)
    :num{0}, fraction_size{fs}
{
}

// implementation of fixedreal's raw() method.
int fixedreal::raw() const{
  return fixedreal::num;
}

/*
int main(){
  fixedreal* fr = new fixedreal;
  fixedreal* fr2 = new fixedreal(24);
  
  printf("%d is a 0, just like %d", fr->raw(), fr2->raw() );
  
  return 0;
}*/