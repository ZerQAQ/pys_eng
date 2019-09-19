#include"gra.h"
#include"pys.h"
#include<ctime>

#if defined(_WIN32) || defined(WIN32)
	#include<windows.h>
	#ifndef GLUT_DISABLE_ATEXIT_HACK
		#define GLUT_DISABLE_ATEXIT_HACK
	#endif
#endif

#include<GL/freeglut.h>

namespace gra{


	color::color(GLfloat r, GLfloat g, GLfloat b, GLfloat apl):r(r / 255), g(g / 255), b(b / 255), alp(alp) {}

	point::point(GLfloat x, GLfloat y):x(x), y(y) {}

	point::point(pys::point v):x(v.x), y(v.y) {}

	int WINDOWS_WIDTH = 1000; //窗口设置
	int WINDOWS_HEIGHT = 600;
	int FPS = 120; //帧率
	float FRAME_SPAN =  1.0 / FPS;
	float PI = 3.1415926535f;
	color BACKGROUND_COLOR = color(15.0, 15.0, 19.0); //背景颜色 
	char WINDOWS_TITLE[100] = "default window title";

	typedef void (*LFT) (); //loop function tpye
	LFT LOOP_FUNCTION; //循环回调函数

	const color WHITE = color(255, 255, 255);

	clock_t last_time = clock();
	const clock_t dt = FRAME_SPAN * 1000;
	

	point point_transfrom(pys::point p){
		return point(p.x, p.y);
	}

	pys::point point_transfrom(point p){
		return pys::point(p.x, p.y);
	}

	void set_background_color(color c){
		BACKGROUND_COLOR = c;
	}

	color get_background_color(){
		return BACKGROUND_COLOR;
	}

	void set_windows_size(int width, int height){
		WINDOWS_HEIGHT = height;
		WINDOWS_WIDTH = width;
	}

	int get_windows_height(){
		return WINDOWS_HEIGHT;
	}

	int get_windows_width(){
		return WINDOWS_WIDTH;
	}

	void set_windows_title(char *v){
		memcpy(WINDOWS_TITLE, v, sizeof(WINDOWS_TITLE));
	}

	void set_fps(int fps){
		FPS = fps;
		FRAME_SPAN = 1.0 / FPS;
	}

	int get_fps(){
		return FPS;
	}

	void initGL(){ 
		//设置背景颜色和抗锯齿
		glClearColor(BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.alp);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	}

	void gl_draw_triangele(const point x, const point y, const point z, const color col){
		//绘制三角形
		glBegin(GL_TRIANGLES);
			glColor3f(col.r, col.g, col.b);
			glVertex2f(x.x, y.y);
			glVertex2f(y.x, y.y);
			glVertex2f(z.x, z.y);
		glEnd();
	}

	void gl_draw_quads(const point a, const point b, const point c, const point d, const color col){
		//opengl绘制矩形
		glBegin(GL_QUADS);
			glColor3f(col.r, col.g, col.b);
			glVertex2f(a.x, a.y);
			glVertex2f(b.x, b.y);
			glVertex2f(c.x, c.y);
			glVertex2f(d.x, d.y);
		glEnd();
	}

	void gl_draw_line(const point a, const point b, const color col){
		//opengl绘制线
		glBegin(GL_LINES);
			glColor3f(col.r, col.g, col.b);
			glVertex2f(a.x, a.y);
			glVertex2f(b.x, b.y);
		glEnd();
	}

	void gl_draw_polygon(std::vector<pys::point> points, const color col){
		//opengl绘制凸多边形
		int n = points.size();
		glBegin(GL_POLYGON);
			glColor3f(col.r, col.g, col.b);
			for(int i = 0; i < n; i++){
				glVertex2f(points[i].x, points[i].y);
			}
		glEnd();
	}

	void draw_line(pys::point A, pys::point B, color col){
		//绘制线
		gl_draw_line(point(A), point(B), col);
	}

	void draw_line(point A, point B, color col = WHITE){
		//绘制线
		gl_draw_line(A, B, col);
	}

	void draw_rectangle(pys::rectangle &A, color col = WHITE){
		//绘制矩形
		gl_draw_quads(
			point(A.leftup.x, A.leftup.y),
			point(A.leftdown.x, A.leftdown.y),
			point(A.rightdown.x, A.rightdown.y),
			point(A.rightup.x, A.rightup.y),
			col
		);

		//圆的标志线 用于更好的显示旋转效果
		gl_draw_line(
			point(A.center.x, A.center.y),
			point(A.rightup.x, A.rightup.y),
			color(200, 0, 0)
		);
	}

	void draw_circle(pys::circle &A, color col = WHITE, int pn){
		glBegin(GL_POLYGON);
		glColor3f(col.r, col.g, col.b);
		if(pn == -1) pn = A.radius;
		for(int i = 0; i < pn; i++){
			float xt = 2.0 * PI / pn * i;
			glVertex2f(A.center.x + cos(xt) * A.radius, A.center.y + sin(xt) * A.radius);
		}
		glEnd();
		//圆的标志线 用于更好的显示旋转效果
		gl_draw_line(
			point(A.center.x, A.center.y),
			point(A.flag_point.x, A.flag_point.y),
			color(200, 0, 0)
		);
	}

	void draw_polygon(pys::polygon &object, color col = WHITE){
		gl_draw_polygon(object.vertexs, col);
	}

	void draw(pys::world& world){
		const int len = world.size();
		for(int i = 0; i < len; i++){
			switch(world[i]->type){
				case 1:
					draw_circle(*(pys::circle*) world[i]);
					break;
				case 2:
					draw_rectangle(*(pys::rectangle*) world[i]);
					break;
				case 3:
					draw_polygon(*(pys::polygon*) world[i]);
				default:;
			}
		}
	}

	void update(pys::world &world){
		world.update(FRAME_SPAN);
	}

	void update(pys::rectangle &object){
		object.update(FRAME_SPAN);
	}

	void update(pys::circle &object){
		object.update(FRAME_SPAN);
	}

	void reshape(const GLsizei width, GLsizei height){
		//窗口大小变化回调函数
		if(height == 0) height = 1; 
		//防止被0除
		GLfloat aspect = (GLfloat)width / (GLfloat)height; 
		//计算长宽比

		glViewport(0, 0, width, height);
		//设置视窗

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if(aspect > (GLfloat)WINDOWS_WIDTH / WINDOWS_HEIGHT){
			gluOrtho2D((GLfloat)-WINDOWS_HEIGHT * aspect / 2,
					(GLfloat)WINDOWS_HEIGHT * aspect / 2,
					(GLfloat)-WINDOWS_HEIGHT / 2,
					(GLfloat)WINDOWS_HEIGHT / 2);
		} //长宽比偏小 拉长宽
		else{
			gluOrtho2D((GLfloat)-WINDOWS_WIDTH / 2,
					(GLfloat)WINDOWS_WIDTH / 2,
					(GLfloat)-WINDOWS_WIDTH / 2 / aspect,
					(GLfloat)WINDOWS_WIDTH / 2 / aspect);
		} //长宽比偏大 拉长高

	}

	void keyboard(const unsigned char key, const int x, const int y){
		switch(key){
			case 27: //esc退出
				glutLeaveMainLoop();
			default:
				break;
		}
	}

	void set_loop_func(void (*loop_func) ()){
		LOOP_FUNCTION = loop_func;
	}

	void display(){
		//循环回调函数
		glClear(GL_COLOR_BUFFER_BIT);
		glLineWidth(2.0);
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);

		LOOP_FUNCTION();

		glFlush();
	}

	void idle(){ //锁帧
		static clock_t now;
		now = clock();
		if(dt <= now - last_time){
			last_time = now;
			display();
		}
	}

	int start(int argc, char ** argv){

		glutInit(&argc, argv);
	//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); //启用双缓冲，避免闪屏

		glutInitWindowPosition(2000, 0);
		glutInitWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT); //启用窗口
		glutCreateWindow(WINDOWS_TITLE);

		initGL();//设置背景颜色和抗锯齿
		glutReshapeFunc(&reshape);
		glutDisplayFunc(&display);
		glutKeyboardFunc(&keyboard);
		glutIdleFunc(&idle); //设置各种回调函数

		glutMainLoop(); //启用主循环
		return 0;
	}
}