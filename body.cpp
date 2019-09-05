#include"body.h"

namespace pys{

    body::body (point center, float mass, vector speed, int type)
        :center(center), speed(speed), mass(mass), type(type){
            acceleration = force = vector(0, 0);
            rate = sqrt(speed.x * speed.x + speed.y * speed.y);
            anglespeed = 0;
            restitution = 0.98;
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
        if(min_y() < YMIN){
            force -= G * mass;
            if(speed.y < 0)
            force += vector(0, - RESTITUTION_ON_WALL * mass * speed.y / time);
        }
        if(YMAX < max_y() && speed.y > 0) 
            force += vector(0, - RESTITUTION_ON_WALL * mass * speed.y / time);
        if(min_x() < XMIN && speed.x < 0) 
            force += vector(RESTITUTION_ON_WALL * mass * - speed.x / time, 0);
        if(XMAX < max_x() && speed.x > 0) 
            force += vector(RESTITUTION_ON_WALL * mass * - speed.x / time, 0);
    }

    void body::update_1(const float time){
        count_force(time);
        acceleration = force / mass;
        speed += acceleration * time;
        center += speed * time;
    }

}