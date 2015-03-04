#ifndef FMAW_CONSTANTS_H
#define FMAW_CONSTANTS_H

#define FRAMES_PER_SECOND 60
#define MS_BETWEEN_FRAMES 16 // 1000 / 60

#ifdef NDS
#include "./fmaw_constants.fds"
#else
#include "./fmaw_constants.fgl"
#endif

#endif