#include"fpair.h"
#include"shape.h"
#include"coll_inf.h"
#include"body.h"
#include"const.h"
#include"collision.h"
#include"render.h"
#include"world.h"
#include<vector>

namespace pys{

    World::World(real dt_):dt(dt_) {}

    void World::set_dt(real dt_){
        dt = dt_;
    }

    void World::add(Shape* shape, real x, real y){
        Body* object = new Body(shape, x, y);
        world.push_back(object);
        size++;
    }

    void World::intergrate_force(Body *o){
        if(!o->inv_mass) return;

        o->speed += (o->force * o->inv_mass) * (dt / 2.0);
        o->anglespeed += (o->torque * o->inv_inertia) * (dt / 2.0);
    }

    void World::intergrate_speed(Body *o){
        if(!o->inv_mass) return;

        if(o->speed.len() > EPSILON)
            o->center += o->speed * dt;
        o->shape->rotate_shape(o->anglespeed * dt);
    }

    void World::update(){
        contact.clear();
        for(Body* object : world){
            object->apply_force(G * object->mass, Vector(0, 0)); //重力
            intergrate_force(object);
            intergrate_speed(object);
            intergrate_force(object); //inter_force一次应用一半 可以提高精度
            object->force = object->torque = 0;
        }

        Coll_inf *inf = new Coll_inf(0, 0);
        for(int i = 0; i < size; i++){
            for(int j = i + 1; j < size; j++){
                if(collision_dect(world[i], world[j], inf)){
                    inf->apply_impulse();
                    contact.push_back(*inf);
                }
            }
        }
    }

    void World::render(){
        for(Body* object : world){
            draw_shape(object->shape);
            draw_point(object->center.x, object->center.y);
        }
        for(Coll_inf inf : contact){
            for(int i = 0; i < inf.contact_count; i++){
                draw_line(inf.contact_points[i], inf.contact_points[i] - (inf.impulse[i] / 500) - (inf.tangent_impluse[i] / 500), Color(0, 1, 0));
                //draw_line(inf.contact_points[i], inf.contact_points[i] - (inf.tangent_impluse[i] / 100), Color(0, 0, 1));
                draw_point(inf.contact_points[i].x, inf.contact_points[i].y, Color(1, 0, 0));
            }
        }
    }
    
}