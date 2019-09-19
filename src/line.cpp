#include"line.h"

namespace pys{
    line::line(point p1, point p2):p1(p1), p2(p2){
        max_x = max(p1.x, p2.x);
        min_x = min(p1.x, p2.x);
        max_y = max(p1.y, p2.y);
        min_y = min(p1.y, p2.y);
    }

    bool check_if_1d_line_cross(fpair A, fpair B){
        if(A.x > B.x) swap(A, B);
        return B.x <= A.y;
    }

    bool check_if_line_cross(line A, line B){
        if(!check_if_1d_line_cross(fpair(A.min_x, A.max_x), fpair(B.min_x, B.max_x))
        || !check_if_1d_line_cross(fpair(A.min_y, A.max_y), fpair(B.min_y, B.max_y)))
            return 0;
        if(cross_product(A.p2 - A.p1, B.p1 - A.p1) * cross_product(A.p2 - A.p1, B.p2 - A.p1) > 0
        || cross_product(B.p2 - B.p1, A.p1 - B.p1) * cross_product(B.p2 - B.p1, A.p2 - B.p1) > 0)
            return 0;
        return 1;
    }

    fpair find_k_and_b(line L){
        point A = L.p1, B = L.p2;   
        float k = A.y - B.y / (A.x - B.x);
        float b = A.y - k * A.x;
        return fpair(k, b);
    }

    point fine_cross_point(line A, line B){
        fpair lineA = find_k_and_b(A);
        fpair lineB = find_k_and_b(B);
        if(lineA.x - lineB.x == 0){
            
        }
        float x = - (lineA.y - lineB.y) / (lineA.x - lineB.x);
        float y = lineA.x * x + lineA.y;
        return point(x, y);
    }
}