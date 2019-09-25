#ifndef SHAPE_H
#define SHAPE_H

#include"const.h"
#include"fpair.h"
#include<vector>

namespace pys{

    struct Body;

    struct Shape{
        enum type{
            circle,
            polygon,
            count
        };

        Shape(){}

        virtual Shape* clone() const = 0;
        virtual void init() = 0;
        virtual void compute_mass(real) = 0;
        virtual type get_type() = 0;
        virtual void rotate_shape(real) = 0;

        Body *body;

        real orient;
    };

    struct Circle : public Shape{
        real radius;
        Circle(real r);

        Shape* clone() const;

        void compute_mass(real density);

        void init();

        type get_type();

        void rotate_shape(real);
    };

    struct Polygon : public Shape{
        std::vector<Point> vectices;
        std::vector<Vector> normals;
        int vectices_num;

        Polygon(std::vector<Point> vectices_);

        void init();

        void compute_mass(real density);

        Shape* clone() const;

        type get_type();

        Point get_support(Vector dir, int* index = 0);

        void rotate_shape(real);
    };
}

#endif