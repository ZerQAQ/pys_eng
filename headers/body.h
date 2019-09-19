#ifndef PYS_BODY_H
#define PYS_BODY_H

#include"fpair.h"
#include"const.h"

namespace pys{
    class body{
		public:
		point center;
		vector speed, acceleration, force;
		float rate, mass, anglespeed, restitution, inertia;
		float static_friction, dynamic_friction;
		int type;
		/*
			类型：
			1.圆
			2.矩形
			3.多边形
		*/

		body (point center = point(0, 0), float mass = 0,
		 	vector speed = vector(0, 0), int type = 0);

		virtual ~body() {}

		void set_anglespeed(float angle_speed);

		point transfrom_by_center(float angle, point center);

		void receive_force(const vector);

		virtual float min_x() = 0;
		
		virtual float max_x() = 0;

		virtual float min_y() = 0;

		virtual float max_y() = 0;

		void count_force(float time);

		void basic_update(const float time);

		void apply_impulse(vector imp, vector r);

		virtual void update(const float time) = 0;

		virtual void position_correct(vector) = 0;
	};
    
}

#endif