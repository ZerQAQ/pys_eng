#include<cstdio>
#include"pys.h"
#include"gra.h"
#include<vector>


pys::world world;

void display(){

	int len = world.size();
	gra::update(world);
	gra::draw(world);
}

int main(){
	int k = 0;
	gra::set_background_color(gra::color(15.0, 15.0, 19.0));
	gra::set_windows_size(1000, 600);
	gra::set_fps(120);

/*
	world.add_circle(pys::point(100, 200), 20, 10, pys::vector(200, 50));
	world.add_circle(pys::point(-100, 200), 20, 10, pys::vector(-300, 0));
	world.add_circle(pys::point(-200, 200), 20, 10, pys::vector(-100, 70));
	world.add_circle(pys::point(200, 80), 20, 10, pys::vector(260, -80));
	world.add_circle(pys::point(150, 20), 20, 10, pys::vector(150, 0));
	world.add_circle(pys::point(0, 200), 20, 10, pys::vector(250, 0));
	world.add_circle(pys::point(-50, 200), 20, 10, pys::vector(300, 0));
	world.add_circle(pys::point(-50, 300), 20, 10, pys::vector(20, 0));
	world.add_circle(pys::point(-300, 200), 20, 10, pys::vector(0, 0));
	world.add_circle(pys::point(-150, 100), 20, 10, pys::vector(0, 0));
*/


	world.add_polygon(pys::point(-200, 200), 3, 50, 10, pys::vector(100, 20));
	world.add_polygon(pys::point(0, 200), 5, 30, 10, pys::vector(70, 50));
	world.add_polygon(pys::point(200, 200), 6, 30, 10, pys::vector(-40, -30));

	std::vector<pys::point> rec;
	rec.push_back(pys::point(-250, -140));
	rec.push_back(pys::point(250, -140));
	rec.push_back(pys::point(250, -160));
	rec.push_back(pys::point(-250, -160));

	world.add_polygon(rec, 50, pys::vector(0, 0));

	rec[0] = pys::point(-400, -200);
	rec[1] = pys::point(+400, -200);
	rec[2] = pys::point(+400, -210);
	rec[3] = pys::point(-400, -210);

	world.add_polygon(rec, 0, pys::vector(0, 0));

	gra::set_loop_func(display);
	gra::start(); 
    return 0;
}
