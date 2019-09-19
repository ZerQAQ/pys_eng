#ifndef PYS_RECTANGLE_H
#define PYS_RECTANGLE_H

#include"fpair.h"
#include"body.h"

namespace pys{
    class rectangle: public body {
		public:
			point leftup, leftdown, rightup, rightdown;//矩形的四个顶点
			float xlen, ylen; //x轴上的边长和y轴上的边长

			rectangle(point leftup, point rightdown,
					float mass, vector speed = vector(0, 0));

			rectangle(point center, float xlen, float ylen,
					float mass, vector speed = vector(0, 0));

			float max_x();

			float min_x();

			float max_y();

			float min_y();

			void transfrom(float angle);

			void single_update(const float time);

			void update(const float time);

			void position_correct(vector v);
	};
}

#endif