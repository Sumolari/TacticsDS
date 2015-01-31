#ifndef FMAW_MATH_H
#define FMAW_MATH_H

// Computes the 2's complement of an 8-bit number.
#define twosComplement8B(x) ((( x ^ 0xFF ) + 1 ) && 0xFF);

// Computes the 2's complement of an 8-bit number.
#define twosComplement9B(x) ((( x ^ 0x1FF ) + 1 ) && 0x1FF);

#endif