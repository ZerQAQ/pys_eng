#include<algorithm>
#include<vector>
#include"gra.cpp"

int k = 0;
float hi = 0;

std::vector<pys::circle> world;

void display(){
    gra::draw_line(gra::point(-400, -200), gra::point(400, -200), gra::WHITE);    
	gra::draw_line(gra::point(-400, -200), gra::point(-400, 300), gra::WHITE);
	gra::draw_line(gra::point(400, -200), gra::point(400, 300), gra::WHITE);

	int len = world.size();

	for(int i = 0; i < len; i++){
		for(int j = i + 1; j < len; j++){
			pys::collision_detc(&world[i], &world[j]);
		}
	}

	for(int i = 0; i < len; i++){
		gra::update(world[i]);
	}

	for(int i = 0; i < len; i++){
		gra::draw_circle(world[i], gra::WHITE);
	}
/*
	hi = std::max(hi, A.center.y);
	if(++k % gra::get_fps() == 0){
		printf("V = %lf %lf\nC = %lf %lf\nF = %lf %lf\n", A.speed.x, A.speed.y, A.center.x, A.center.y, A.force.x, A.force.y);
		if(k % 200 == 0) printf ("highest = %lf\n", hi), hi = 0;
	}
*/
}

int main(){
	gra::set_background_color(gra::color(15.0, 15.0, 19.0));
	gra::set_windows_size(1000, 600);
	gra::set_fps(120);

	world.push_back(pys::circle(pys::point(100, 200), 20, 10, pys::vector(200, 50)));
	world.push_back(pys::circle(pys::point(-100, 200), 20, 10, pys::vector(-300, 0)));
	world.push_back(pys::circle(pys::point(-200, 200), 20, 10, pys::vector(-100, 70)));
	world.push_back(pys::circle(pys::point(200, 80), 20, 10, pys::vector(260, -80)));
	world.push_back(pys::circle(pys::point(150, 20), 20, 10, pys::vector(150, 0)));
	world.push_back(pys::circle(pys::point(0, 200), 20, 10, pys::vector(250, 0)));
	world.push_back(pys::circle(pys::point(-50, 200), 20, 10, pys::vector(300, 0)));
	world.push_back(pys::circle(pys::point(-50, 300), 20, 10, pys::vector(20, 0)));
	world.push_back(pys::circle(pys::point(-300, 200), 20, 10, pys::vector(0, 0)));
	world.push_back(pys::circle(pys::point(-150, 100), 20, 10, pys::vector(0, 0)));

	gra::set_loop_func(display);
	gra::start();
    return 0;
}