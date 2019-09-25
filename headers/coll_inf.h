#ifndef COLL_INF
#define COLL_INF

#include"fpair.h"
#include"body.h"

namespace pys{

    struct Coll_inf
    {
        Body *A, *B;

        real peneration;
        real static_friction, dynamic_friction, restitution;
        
        Vector impulse[2], tangent_impluse[2], ra[2], rb[2];
        Vector normal;
        Vector contact_points[2];
        int contact_count;
        
        Coll_inf(Body *a, Body* b);

        void init();

        void apply_impulse();

        void position_correct();
    };

}

#endif