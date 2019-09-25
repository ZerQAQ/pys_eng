#include"fpair.h"
#include"const.h"
#include"shape.h"
#include"body.h"

namespace pys{
    Body::Body (Shape *s, real x, real y):shape(s->clone()){
        shape->body = this;
        shape->init();

        center.set(x, y);
        speed.set(0, 0);
        force.set(0, 0);

        anglespeed = torque = 0;
        
        static_friction = DEFAULT_SF;
        dynamic_friction = DEFAULT_DF;
        restitution = DEFAULT_RESTITUTION;
    }

    void Body::apply_force(const Vector &f, const Vector &r){
        force += f;
        torque += cross_product(r, f);
    }

    void Body::apply_impulse(const Vector& impulse, const Vector& r){
        speed += inv_mass * impulse;
        anglespeed += inv_inertia * cross_product(r, impulse);
    }

    void Body::set_static(){
        mass = inv_mass = inertia = inv_inertia = 0;
    }
}
