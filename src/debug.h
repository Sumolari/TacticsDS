#ifndef FMAW_DEBUG_H
#define FMAW_DEBUG_H

#include <string>

#include "./debug.h"

namespace FMAW {

/**
 * Prints given message applying format, if needed.
 */
void printf( const std::string fmt_str, ... );

/**
 * Returns a string representing given byte in binary.
 * @param  x Byte to represent in binary.
 * @return   Binary representation of given byte.
 */
std::string byte_to_binary( uint16 x );

/**
 * Returns a string representing given half word in binary.
 * @param  x Half word to represent in binary.
 * @return   Binary representation of given half word.
 */
std::string half_word_to_binary( uint16 x );

}

#endif