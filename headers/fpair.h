#ifndef PYS_FPAIR_H
#define PYS_FPAIR_H

typedef float real;

namespace pys{
    class Fpair{
        public:
            real x, y;
            void set(real, real);

            Fpair(real x = 0, real y = 0);

            real sqrlen();
            
            real len();

            Fpair operator + (const Fpair&);
            
            void operator += (const Fpair&);

            Fpair operator - (const Fpair&);

            Fpair operator - () const;

            void operator -= (const Fpair&);

            Fpair operator * (const real&);//数量乘

            void operator *= (const real&);

            real operator * (const Fpair&);//点乘

            void operator *= (const Fpair&);

            Fpair operator / (const real&);//向量与标量除

            void operator /= (const real&);

            void normalize();

            Fpair right_normal();

            void rotate(const real);

    }; 

    typedef Fpair Point;
    typedef Fpair Vector;

    Fpair operator * (float s, const Fpair&);

    Vector rotate(Vector vect, const real angle, const Vector center = Vector(0, 0));

    real sqr(real);

    real cross_product(const Vector, const Vector);

    Vector cross_product(const Vector, const real);
    
    Vector cross_product(const real, const Vector);

    real max(real a, real b);

    real min(real a, real b);

    int max(int a, int b);

    int min(int a, int b);
}

#endif