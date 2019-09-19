#include"rectangle.h"

namespace pys{

	rectangle::rectangle(point leftup, point rightdown,
				float mass, vector speed)
				:body(point((leftup.x + rightdown.x) / 2, (leftup.y + rightdown.y) / 2),
				mass, speed, 2),
				leftup(leftup), rightdown(rightdown){
					leftdown = point(leftup.x , rightdown.y);
					rightup = point(rightdown.x, leftup.y);
					xlen = rightdown.x - leftdown.x;
					ylen = leftup.y - leftdown.y;
			}

	rectangle::rectangle(point center, float xlen, float ylen,
			float mass, vector speed)
				:body(center, mass, speed, 2),
				xlen(xlen), ylen(ylen){
					leftdown.x = leftup.x = center.x - xlen / 2;
					rightdown.x = rightup.x = center.x + xlen / 2;
					leftup.y = rightup.y = center.y + ylen / 2; 
					leftdown.y = rightdown.y = center.y - ylen / 2;
				}

	float rectangle::max_x(){
		return max(max(leftdown.x, leftup.x), max(rightdown.x, rightup.x));
	}

	float rectangle::min_x(){
		return min(min(leftdown.x, leftup.x), min(rightdown.x, rightup.x));
	}

	float rectangle::max_y(){
		return max(max(leftdown.y, leftup.y), max(rightdown.y, rightup.y));
	}

	float rectangle::min_y(){
		return min(min(leftdown.y, leftup.y), min(rightdown.y, rightup.y));
	}

	void rectangle::transfrom(float angle){
		leftup = transfrom_by_center(angle, leftup);
		leftdown = transfrom_by_center(angle, leftdown);
		rightdown = transfrom_by_center(angle, rightdown);
		rightup = transfrom_by_center(angle, rightup);
	}

	void rectangle::single_update(const float time){
		basic_update(time);
		leftup += speed * time;
		leftdown += speed * time;
		rightup += speed * time;
		rightdown += speed * time;
		transfrom(anglespeed * time);
	}

	void rectangle::update(const float time){
		for(int i = 0; i < COLLISION_DETC_TIME_PER_SEPT; i++)
			single_update(time / (float)COLLISION_DETC_TIME_PER_SEPT);
	}

	void rectangle::position_correct(vector v){
		
	}
}
