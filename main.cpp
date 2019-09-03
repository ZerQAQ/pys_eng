#include<algorithm>
#include<cstring>
#include<vector>
#include"gra.cpp"

pys::world world;

void display(){
    gra::draw_line(gra::point(-400, -200), gra::point(400, -200), gra::WHITE);    
	gra::draw_line(gra::point(-400, -200), gra::point(-400, 300), gra::WHITE);
	gra::draw_line(gra::point(400, -200), gra::point(400, 300), gra::WHITE);

	int len = world.size();
	gra::update(world);
	gra::draw(world);
//	gra::draw_circle(* (pys::circle*) world[0]);
}

int main(){
	gra::set_background_color(gra::color(15.0, 15.0, 19.0));
	gra::set_windows_size(1000, 600);
	gra::set_fps(120);

	world.add_circle(pys::point(100, 200), 20, 10, pys::vector(200, 50));
//	world.add_rectangle(pys::point(15, 215), pys::point(-15, 185), 10, pys::vector(200, 50));

	world.add_circle(pys::point(-100, 200), 20, 10, pys::vector(-300, 0));
	world.add_circle(pys::point(-200, 200), 20, 10, pys::vector(-100, 70));
	world.add_circle(pys::point(200, 80), 20, 10, pys::vector(260, -80));
	world.add_circle(pys::point(150, 20), 20, 10, pys::vector(150, 0));
	world.add_circle(pys::point(0, 200), 20, 10, pys::vector(250, 0));
	world.add_circle(pys::point(-50, 200), 20, 10, pys::vector(300, 0));
	world.add_circle(pys::point(-50, 300), 20, 10, pys::vector(20, 0));
	world.add_circle(pys::point(-300, 200), 20, 10, pys::vector(0, 0));
	world.add_circle(pys::point(-150, 100), 20, 10, pys::vector(0, 0));
	gra::set_loop_func(display);
	gra::start();
    return 0;
}