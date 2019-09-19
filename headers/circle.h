#ifndef PYS_CIRCLE_H
#define PYS_CIRCLE_H

#include"fpair.h"
#include"body.h"

namespace pys{
    class circle: public body{
		public:
			point flag_point;
			float radius;

			circle(point center, float radius, float mass,
			 vector speed = vector(0, 0));

			float max_x();

			float min_x();

			float max_y();

			float min_y();

			void transfrom(float angle);

			void single_update(float time);

			void update(const float time);

			void position_correct(vector v);
	};
}

#endif