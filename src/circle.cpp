#include"circle.h"

namespace pys{

	circle::circle(point center, float radius, float mass,
		vector speed)
	:body(center, mass, speed, 1), radius(radius){
		flag_point = center + point(radius, 0);
	}

	float circle::max_x(){
		return center.x + radius;
	}

	float circle::min_x(){
		return center.x - radius;
	}

	float circle::max_y(){
		return center.y + radius;
	}

	float circle::min_y(){
		return center.y - radius;
	}

	void circle::transfrom(float angle){
		flag_point = transfrom_by_center(angle, flag_point);
	}

	void circle::single_update(float time){
		basic_update(time);
		this->flag_point += speed * time;
		transfrom(this->anglespeed * time);
	}

	void circle::update(const float time){
		for(int i = 0; i < COLLISION_DETC_TIME_PER_SEPT; i++)
			single_update(time / (float)COLLISION_DETC_TIME_PER_SEPT);
	}

	void circle::position_correct(vector v){
		
	}
}