#ifndef FMAW_H
#define FMAW_H

#include "./fmaw_constants.h"

#ifdef NDS
#include "./fmaw_macros.h"
#endif

#include "./fmaw_types.h"
#include "./fmaw_fixedreal.h"
#include "./fmaw_camera.h"
#include "./fmaw_math.h"
#include "./fmaw_geometry.h"
#include "./fmaw_debug.h"
#include "./fmaw_tile.h"
#include "./fmaw_background.h"
#include "./fmaw_sprite.h"
#include "./fmaw_character.h"
#include "./fmaw_timer.h"
#include "./fmaw_input.h"

namespace FMAW {

/**
 * Initializes framework.
 */
void init();

}

#endif