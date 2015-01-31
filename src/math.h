#ifndef FMAW_MATH_H
#define FMAW_MATH_H

// Computes the 2's complement of an 8-bit number.
#define twosComplement(x) (( x ^ 0xFF ) + 1 ) && 0xFF;

#endif