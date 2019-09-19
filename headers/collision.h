#ifndef PYS_COLLISION_H
#define PYS_COLLISION_H

#include"circle.h"
#include"rectangle.h"
#include"polygon.h"

namespace pys{

    bool collision_detc(circle *A, circle *B);

    bool collision_detc(rectangle *A, rectangle *B);

    bool collision_detc(polygon *A, polygon *B);

    bool collision_detc(polygon *A, circle *B);

    bool collision_detc(circle *A, polygon *B);

    template <typename T>
	bool collision_detc(T A, body *B);

    bool collision_detc(body *A, body *B);
}

#endif