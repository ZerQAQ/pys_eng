#include"polygon.h"
#include"circle.h"
#include"rectangle.h"
#include"collision.h"
#include"world.h"

namespace pys{

	void world::add_circle(point center, float radius,
		float mass, vector speed){
		world.push_back(new circle(center, radius, mass, speed));
	}
	
	void world::add_rectangle(point leftup, point rightdown,
		float mass, vector speed){
		world.push_back(new rectangle(leftup, rightdown, mass, speed));
	}

	void world::add_rectangle(point center, float xlen, float ylen,
		float mass, vector speed){
		world.push_back(new rectangle(center, xlen, ylen, mass, speed));
	}

	void world::add_polygon(point center, int edges_num, float edges_length,
		float mass, vector speed){
		world.push_back(new polygon(center, edges_num, edges_length, mass, speed));
	}

	void world::add_polygon(std::vector<point> vertexs, float mass, vector speed){
		world.push_back(new polygon(vertexs, mass, speed));
	}

	body* world::operator[] (const int index){
		return world[index];
	}

	void world::update(float time){
		const int len = world.size();
		for(int i = 0; i < len; i++){
			for(int j = i + 1; j < len; j++){
				collision_detc(world[i], world[j]);
			}
		}
		for(int i = 0; i < len; i++){
			world[i]->update(time);
		}
	}

	int world::size(){
		return world.size();
	}
}