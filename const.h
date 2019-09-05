#ifndef PYS_CONST_H
#define PYS_CONST_H

#include"fpair.h"

namespace pys{
    float XMIN = -400;
    float XMAX = 400;
    float YMIN = -200;
    float YMAX = 250;
    float RESTITUTION_ON_WALL = 1.95;
    const int COLLISION_DETC_TIME_PER_SEPT = 10;

    vector G = vector(0, -500);
}

#endif