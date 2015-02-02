#ifndef FMAW_MATH_H
#define FMAW_MATH_H

// Computes the 2's complement of an 8-bit number.
#define twosComplement8B(x) ((( x ^ 0xFF ) + 1 ) && 0xFF);

// Computes the 2's complement of an 8-bit number.
#define twosComplement9B(x) ((( x ^ 0x1FF ) + 1 ) && 0x1FF);

namespace FMAW {

/**
 * Given an integer returns a valid integer in the range [low...high] as near
 * as the original integer as possible.
 *
 * @param  value Original integer.
 * @param  low   Minimum value.
 * @param  high  Maximum value.
 * @return       Integer in range [low...high] nearest to original one.
 */
static inline int clampInt(int value, int low, int high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

/**
 * Given an double returns a valid double in the range [low...high] as near
 * as the original double as possible.
 *
 * @param  value Original double.
 * @param  low   Minimum value.
 * @param  high  Maximum value.
 * @return       double in range [low...high] nearest to original one.
 */
static inline double clampDouble(double value, double low, double high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

}  // namespace FMAW

#endif