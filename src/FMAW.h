#ifndef FMAW_H
#define FMAW_H

#ifdef OPENGL
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#endif
#endif

#include "./fmaw_constants.h"
#include "./fmaw_macros.h"
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

#include <functional>

namespace FMAW {

/**
 * Initializes framework.
 */
void init(void (*displayCallback)(), void (*updateCallback)());

/**
 * Starts game.
 */
void start();

}

#endif