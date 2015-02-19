#ifndef FMAW_CAMERA_H
#define FMAW_CAMERA_H

#include "./fmaw_types.h"

#include <nds.h>

namespace FMAW {

class Camera {
public:
    /**
     * Sets horizontal offset of the camera.
     * @param x New horizontal offset of the camera.
     */
    static void setHorizontalOffset(FixedReal x);

    /**
     * Sets vertical offset of the camera.
     * @param y New vertical offset of the camera.
     */
    static void setVerticalOffset(FixedReal y);
};

}

#endif