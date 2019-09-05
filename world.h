#ifndef PYS_WORLD_H
#define PYS_WORLD_H

#include<vector>
#include"fpair.h"
#include"body.h"
#include"circle.h"
#include"rectangle.h"
#include"collision.h"

namespace pys{
    struct world{
		std::vector<body*> world;

		void add_circle(point center, float radius,
		 float mass, vector speed = vector(0, 0));
		
		void add_rectangle(point leftup, point rightdown,
		 float mass, vector speed = vector(0, 0));

		void add_rectangle(point center, float xlen, float ylen,
		 float mass, vector speed = vector(0, 0));

		body* operator[] (const int index);

		void update(float time);

		int size();
	};
}

#include"world.cpp"
#endif