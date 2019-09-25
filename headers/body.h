#ifndef PYS_BODY_H
#define PYS_BODY_H

#include"fpair.h"
#include"shape.h"

namespace pys{
    struct Body{
		Point center;
		Vector speed, force;
        real inertia, mass, inv_inertia, inv_mass;
		real anglespeed, torque;
		real restitution, static_friction, dynamic_friction;
        Shape *shape;

		real radius;


		Body (Shape *s, real x, real y);

        void apply_force(const Vector &f, const Vector &r);

        void apply_impulse(const Vector& impulse, const Vector& r);

        void set_static();
	};
}

#endif