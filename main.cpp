#include<cstdio>
#include<time.h>
#include<algorithm>
#include<cmath>
#include"phy.cpp"

#if defined(_WIN32) || defined(WIN32)
	#include<windows.h>
	#ifndef GLUT_DISABLE_ATEXIT_HACK
		#define GLUT_DISABLE_ATEXIT_HACK
	#endif
#endif
// 解决win32下的兼容性问题

#include<GL/freeglut.h>

#define WINDOWS_WIDTH 1000 //窗口设置
#define WINDOWS_HEIGHT 600
#define FPS 120
#define FRAME_SPAN 1.0/FPS
#define PI 3.1415926535f

struct color{
	GLfloat r, g, b, alp;
	color(GLfloat r, GLfloat g, GLfloat b, GLfloat apl = 1.0):r(r / 255), g(g / 255), b(b / 255), alp(alp) {}
};

struct point{
	GLfloat x, y;
	point(GLfloat x, GLfloat y):x(x), y(y) {}
};

const color BACKGROUND_COLOR = color(15.0, 15.0, 19.0); //背景颜色
const color WHITE = color(255, 255, 255);

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

void draw_triangele(const point x, const point y, const point z, const color col){
	//绘制三角形
	glBegin(GL_TRIANGLES);
		glColor3f(col.r, col.g, col.b);
		glVertex2f(x.x, y.y);
		glVertex2f(y.x, y.y);
		glVertex2f(z.x, z.y);
	glEnd();
}

void draw_quads(const point a, const point b, const point c, const point d, const color col){
	//绘制矩形
	glBegin(GL_QUADS);
		glColor3f(col.r, col.g, col.b);
		glVertex2f(a.x, a.y);
		glVertex2f(b.x, b.y);
		glVertex2f(c.x, c.y);
		glVertex2f(d.x, d.y);
	glEnd();
}

void draw_line(const point a, const point b, const color col){
	glBegin(GL_LINES);
		glColor3f(col.r, col.g, col.b);
		glVertex2f(a.x, a.y);
		glVertex2f(b.x, b.y);
	glEnd();
}

void display();

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

clock_t last_time = clock();
const clock_t dt = FRAME_SPAN * 1000;
void idle(){ //锁帧
	static clock_t now;
	now = clock();
	if(dt <= now - last_time){
		last_time = now;
		display();
	}
}

void draw_rectangle(pys::rectangle A){
	draw_quads(
		point(A.leftup.x, A.leftup.y),
		point(A.leftup.x, A.rightdown.y),
		point(A.rightdown.x, A.rightdown.y),
		point(A.rightdown.x, A.leftup.y),
		WHITE
	);
}

void draw_circle(pys::circle A, color col){
	glBegin(GL_POLYGON);
	glColor3f(col.r, col.g, col.b);
	int pn = A.radius;
	for(int i = 0; i < pn; i++){
		float xt = 2.0 * PI / pn * i;
		glVertex2f(A.center.x + cos(xt) * A.radius, A.center.y + sin(xt) * A.radius);
	}
	glEnd();

	glBegin(GL_LINES);
	glColor3f(200, 0, 0);
	glVertex2f(A.center.x, A.center.y);
	glVertex2f(A.flag_point.x, A.flag_point.y);
	glEnd();
}

pys::circle A(pys::point(0, 200), 30, 10.0, PI * 1.5, pys::vector(670, 0));
int main(int argc, char ** argv){

	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); //启用双缓冲，避免闪屏

	glutInitWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT); //启用窗口
	glutCreateWindow("qwq");

	initGL();//设置背景颜色和抗锯齿
	glutReshapeFunc(&reshape);
	glutDisplayFunc(&display);
	glutKeyboardFunc(&keyboard);
	glutIdleFunc(&idle);

	glutMainLoop();
	return 0;
}

int k = 0;
float hi = 0;
extern void display(){
	//循环回调函数
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2.0);

	draw_line(point(-400, -200), point(400, -200), WHITE);
	draw_line(point(-400, -200), point(-400, 300), WHITE);
	draw_line(point(400, -200), point(400, 300), WHITE);

	for(int i = 0; i < 100; i++) A.update(FRAME_SPAN / 100);
	draw_circle(A, WHITE);

	hi = std::max(hi, A.center.y);
	if(++k % FPS == 0){
		printf("V = %lf %lf\nC = %lf %lf\nF = %lf %lf", A.speed.x, A.speed.y, A.center.x, A.center.y, A.force.x, A.force.y);
		if(k % 200 == 0) printf ("highest = %lf", hi), hi = 0;
		printf("\n");
	}

	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	glFlush();
}