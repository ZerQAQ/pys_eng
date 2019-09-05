#ifndef PYS_FPAIR_H
#define PYS_FPAIR_H
#include<cmath>
#include<algorithm>
using std::max;
using std::min;

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

                float operator * (const fpair&);//点乘

                fpair operator / (const float&);//向量与标量除

                fpair standard();
        }; 

        typedef fpair point;
        typedef fpair vector;

        vector rotate(const vector, const float);
}

#include"fpair.cpp"
#endif