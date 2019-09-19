#ifndef GRA_H
#define GRA_H

#if defined(_WIN32) || defined(WIN32)
	#include<windows.h>
	#ifndef GLUT_DISABLE_ATEXIT_HACK
		#define GLUT_DISABLE_ATEXIT_HACK
	#endif
#endif

#include"pys.h"
#include<ctime>

#include<gl/freeglut.h>

namespace gra{
	
	struct color{ //颜色
		GLfloat r, g, b, alp;
		color(GLfloat r, GLfloat g, GLfloat b, GLfloat apl = 1.0);
	};

    struct point{
		GLfloat x, y;
		point(GLfloat x, GLfloat y);
		point(pys::point v);
	};

	extern int WINDOWS_WIDTH; //窗口设置
	extern int WINDOWS_HEIGHT;
	extern int FPS; //帧率
	extern float FRAME_SPAN;
	extern float PI;
	extern color BACKGROUND_COLOR; //背景颜色 
	extern char WINDOWS_TITLE[];

	typedef void (*LFC) (); //loop function class
	extern LFC LOOP_FUNCTION; //循环回调函数

	extern const color WHITE;

	point point_transfrom(pys::point p);

	pys::point point_transfrom(point p);

	void set_background_color(color c);

	color get_background_color();

	void set_windows_size(int width, int height);

	int get_windows_height();

	int get_windows_width();

	void set_windows_title(char *v);

	void set_fps(int fps);

	int get_fps();

	void initGL();

	void gl_draw_triangele(const point x, const point y, const point z, const color col);

	void gl_draw_quads(const point a, const point b, const point c, const point d, const color col);

	void gl_draw_line(const point a, const point b, const color col);

	void gl_draw_polygon(std::vector<pys::point> points, const color col);

	void draw_line(pys::point A, pys::point B, color col);

	void draw_line(point A, point B, color col);

	void draw_rectangle(pys::rectangle &A, color col);

	void draw_circle(pys::circle &A, color col, int pn = -1);

	void draw_polygon(pys::polygon &object, color col);

	void draw(pys::world& world);

	void update(pys::world &world);

	void update(pys::rectangle &object);

	void update(pys::circle &object);

	void reshape(const GLsizei width, GLsizei height);

	void keyboard(const unsigned char key, const int x, const int y);

	void set_loop_func(void (*loop_func) ());
	extern void display();

	void idle();

	int start(int argc = 0, char ** argv = NULL);
}

#endif