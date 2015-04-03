// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./fmaw_geometry.h"
#include "./fmaw_debug.h"

namespace FMAW {

bool pointInArea(Point p, Area a) {
    Point tl = a.topLeft;
    Point br = a.bottomRight;
    return (p.x >= tl.x && p.x <= br.x && p.y <= br.y && p.y >= tl.y);
}

}  // namespace FMAW

#ifdef NDS
#include "./fmaw_geometry.fds"
#elif OPENGL
#include "./fmaw_geometry.fgl"
#endif
