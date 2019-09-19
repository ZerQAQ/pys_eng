#include"body.h"

namespace pys{

    body::body (point center, float mass, vector speed, int type)
        :center(center), speed(speed), mass(mass), type(type){
            acceleration = force = vector(0, 0);
            rate = sqrt(speed.x * speed.x + speed.y * speed.y);
            anglespeed = 0;
            restitution = 0.9;
            inertia = mass;
            static_friction = 0.5f;
            dynamic_friction = 0.3f;
        }

    void body::set_anglespeed(float v){
        anglespeed = v;
    }

    point body::transfrom_by_center(float angle, point p){
        vector relat_vector = p - center;
        relat_vector = rotate(relat_vector, angle);
        return center + relat_vector;
    }

    void body::receive_force(const vector Force){
        force = force + Force;
    }

    void body::count_force(float time){
        force = vector(0, 0);
        force += G * mass;
    }

    void body::basic_update(const float time){
        if(mass == 0) return;
        count_force(time);
        acceleration = force / mass;
        speed += acceleration * time;
        center += speed * time;
    }

    void body::apply_impulse(vector imp, vector r){
        if(mass == 0) return;
        speed += imp / mass;
        anglespeed += cross_product(r, imp) / inertia;
	}

}