#ifndef FMAW_DEBUG_H
#define FMAW_DEBUG_H

#include "./debug.h"

namespace FMAW {

/**
 * Prints given message applying format, if needed.
 */
void printf( const std::string fmt_str, ... );

}

#endif