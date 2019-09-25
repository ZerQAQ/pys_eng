#ifndef COLLISION_H
#define COLLISION_H

#include"body.h"
#include"coll_inf.h"

namespace pys{

    bool collision_dect(Body *A, Body *B, Coll_inf *inf);

    bool circle_to_circle(Body *A, Body *B, Coll_inf *inf);

    bool polygon_to_circle(Body *A, Body *B, Coll_inf *inf);

    bool circle_to_polygon(Body *A, Body *B, Coll_inf *inf);

    bool polygon_to_polygon(Body *A, Body *B, Coll_inf *inf);
}

#endif