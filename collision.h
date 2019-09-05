#ifndef PYS_COLLISION_H
#define PYS_COLLISION_H

#include"pys.h"
#include"rectangle.h"
#include"circle.h"

namespace pys{
    struct coll_inf;

    void solve_collision(coll_inf *inf);

    bool collision_detc(circle *A, circle *B);

    bool collision_detc(rectangle *A, rectangle *B);

    template <typename T>
	bool collision_detc(T A, body *B);

    bool collision_detc(body *A, body *B);
}

#include"collision.cpp"
#endif