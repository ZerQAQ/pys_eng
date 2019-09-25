#ifndef RENDER_H
#define RENDER_H

#include"shape.h"
#include"fpair.h"

namespace pys{

    struct Color
    {
        real r, g, b, al;
        Color(real r = 1.0, real g = 1.0, real b = 1.0, real al = 1.0);
    };

    extern const Color WHITE;
    

    void draw_shape(Shape *shape_, const Color c = WHITE);

    void draw_string(real x, real y, const char *s, const Color c = WHITE);

    void draw_point(real x, real y, Color c = WHITE);

    void draw_line(Point a, Point b, Color c = WHITE);
}

#endif