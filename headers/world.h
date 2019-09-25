#ifndef WORLD_H
#define WORLD_H

#include"fpair.h"
#include"Shape.h"
#include"Body.h"
#include"coll_inf.h"

namespace pys{
    struct World
    {
        std::vector<Body*> world;
        std::vector<Coll_inf> contact;
        int size;
        real dt;

        World(real dt_);

        void set_dt(real dt_);

        void add(Shape* shape, real x, real y);

        void intergrate_force(Body *o);

        void intergrate_speed(Body *o);

        void update();

        void render();
    };
}

#endif