#ifndef PYS_FPAIR_H
#define PYS_FPAIR_H
#include<cmath>
#include<algorithm>
using std::max;
using std::min;
using std::swap;

namespace pys{
    class fpair
        {
            public:
                float x, y;
                fpair(float x = 0, float y = 0);

                float sqlength();
                
                float length();

                fpair operator + (const fpair&);
                
                void operator += (const fpair&);

                fpair operator - (const fpair&);

                void operator -= (const fpair&);

                fpair operator * (const float&);//数量乘

                void operator *= (const float&);

                float operator * (const fpair&);//点乘

                void operator *= (const fpair&);

                fpair operator / (const float&);//向量与标量除

                void operator /= (const float&);

                void standard();

                fpair right_normal();

                void rotate(const float);

        }; 

        typedef fpair point;
        typedef fpair vector;

        vector rotate(vector vect, const float angle, const vector center = vector(0, 0));

        float sqr(float);

        float cross_product(const vector, const vector);

        vector cross_product(const vector, const float);
        
        vector cross_product(const float, const vector);
}

#endif