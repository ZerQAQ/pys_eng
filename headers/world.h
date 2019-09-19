#ifndef PYS_WORLD_H
#define PYS_WORLD_H

#include<vector>
#include"fpair.h"

namespace pys{
    struct world{
		std::vector<body*> world;

		void add_circle(point center, float radius,
		 float mass, vector speed = vector(0, 0));
		
		void add_rectangle(point leftup, point rightdown,
		 float mass, vector speed = vector(0, 0));

		void add_rectangle(point center, float xlen, float ylen,
		 float mass, vector speed = vector(0, 0));

		void add_polygon(point center, int edges_num, float edges_length, 
		float mass, vector speed = vector(0, 0));

		void add_polygon(std::vector<point> vertexs, float mass, vector speed);

		body* operator[] (const int index);

		void update(float time);

		int size();
	};
}

#endif