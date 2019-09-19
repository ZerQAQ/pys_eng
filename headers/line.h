#ifndef PYS_LINE_H
#define PYS_LINE_H

#include"fpair.h"

namespace pys{
    class line{//几何线段类
        public:
        point p1, p2;//线段端点
        float max_x, min_x, max_y, min_y;//线段的AABB包围盒
        line(point p1 = point(0, 0), point p2 = point(0, 0));

        void print();
    };

    bool check_if_1d_line_cross(fpair A, fpair B);//检查(A.x, A.y)和(B.x, B.y)是否有交

    bool check_if_line_cross(line A, line B);//检查线段是否相交

    fpair find_k_and_b(line L);//求线段对应直线的k和b 返回值为fpair(k, b)

    point fine_cross_point(line A, line B);//寻找两线段对应直线的交点
}

#endif