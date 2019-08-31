#include"gra.cpp"

int k = 0;
float hi = 0;
pys::circle A(pys::point(0, 200), 30, 10.0, gra::PI * 1.5, pys::vector(670, 0));

void display(){
    gra::draw_line(gra::point(-400, -200), gra::point(400, -200), gra::WHITE);    
	gra::draw_line(gra::point(-400, -200), gra::point(-400, 300), gra::WHITE);
	gra::draw_line(gra::point(400, -200), gra::point(400, 300), gra::WHITE);

	gra::update(A);
	gra::draw_circle(A, gra::WHITE);

	hi = std::max(hi, A.center.y);
	if(++k % gra::get_fps() == 0){
		printf("V = %lf %lf\nC = %lf %lf\nF = %lf %lf\n", A.speed.x, A.speed.y, A.center.x, A.center.y, A.force.x, A.force.y);
		if(k % 200 == 0) printf ("highest = %lf\n", hi), hi = 0;
	}
}

int main(){
	gra::set_background_color(gra::color(15.0, 15.0, 19.0));
	gra::set_windows_size(1000, 600);
	gra::set_fps(120);
	gra::set_loop_func(display);
	gra::start();
    return 0;
}