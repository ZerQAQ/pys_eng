#if defined(_WIN32) || defined(WIN32)
	#include<windows.h>
	#ifndef GLUT_DISABLE_ATEXIT_HACK
		#define GLUT_DISABLE_ATEXIT_HACK
	#endif
#endif

#include<GL/freeglut.h>

#include"body.h"
#include"shape.h"
#include"fpair.h"
#include"render.h"

namespace pys{

    Color::Color(real r, real g, real b, real al)
    :r(r), g(g), b(b), al(al){}

    const Color WHITE = Color();
    

    void draw_shape(Shape *shape_, const Color c){
        if(shape_->get_type() == Shape::circle){
            Circle *shape = (Circle*) shape_;
            glBegin(GL_POLYGON);
            glColor3f(c.r, c.g, c.b);
            for(int i = 0; i < shape->radius; i++){
                real angle = 2.0 * PI / shape->radius * i;
                Point p = shape->body->center;
                Vector r = (0, shape->radius);
                r = rotate(r, angle);
                p += r;
                glVertex2f(p.x, p.y);
            }
            glEnd();
        }
        else if(shape_->get_type() == Shape::polygon){
            Polygon *shape = (Polygon*) shape_;
            glBegin(GL_POLYGON);
            glColor3f(c.r, c.g, c.b);
            for(int i = 0; i < shape->vectices_num; i++){
                Point p = shape->body->center;
                p += shape->vectices[i];
                glVertex2f(p.x, p.y);
            }
            glEnd();
        }
    }

    void draw_string(real x, real y, const char *s, const Color c){
        glColor3f(c.r, c.g, c.b);
        glRasterPos2f(x, y);
        int l = strlen(s);
        for(int i = 0; i < l; i++)
            glutBitmapCharacter( GLUT_BITMAP_9_BY_15, s[i]);
    }

    void draw_point(real x, real y, Color c){
        glBegin(GL_POINTS);
        glColor3f(c.r, c.g, c.b);
        glVertex2f(x, y);
        glEnd();
    }

    void draw_line(Point a, Point b, Color c){
        glBegin(GL_LINES);
        glColor3f(c.r, c.g, c.b);
        glVertex2f(a.x, a.y);
        glVertex2f(b.x, b.y);
        glEnd();
    }
}