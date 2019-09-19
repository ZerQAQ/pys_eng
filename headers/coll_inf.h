#ifndef PYS_COLL_INF_H
#define PYS_COLL_INF_H

#include"polygon.h"
#include"fpair.h"
#include"body.h"
#include<cmath>

namespace pys{

    float inv(float);

    float sqr(float);

    struct coll_inf
    {
        body *A;
        body *B;
        //碰撞对象 A碰撞B
        int contact_count;
        point contact_point[5];
        //碰撞点
        float df, sf, e, penetration;
        vector normal;

        coll_inf(body*, body*);

        void init();

        void solve();
    };

    void count_contact_points(polygon *, polygon *, coll_inf &);
}

#endif