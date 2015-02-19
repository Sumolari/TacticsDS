#ifndef FMAW_CAMERA_H
#define FMAW_CAMERA_H

#include "./fmaw_types.h"

#include <nds.h>

namespace FMAW {

namespace Camera {

/**
 * Sets horizontal offset of the camera.
 * @param x New horizontal offset of the camera.
 */
void setHorizontalOffset(FixedReal x);

/**
 * Sets vertical offset of the camera.
 * @param y New vertical offset of the camera.
 */
void setVerticalOffset(FixedReal y);

}

}

#endif