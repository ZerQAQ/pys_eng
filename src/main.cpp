#include"pys.h"
#include<ctime>

#if defined(_WIN32) || defined(WIN32)
	#include<windows.h>
	#ifndef GLUT_DISABLE_ATEXIT_HACK
		#define GLUT_DISABLE_ATEXIT_HACK
	#endif
#endif

#include<GL/freeglut.h>

int WINDOWS_WIDTH = 1000; //窗口设置
int WINDOWS_HEIGHT = 600;
int FPS = 120; //帧率
float FRAME_SPAN =  1.0 / FPS;
float PI = 3.1415926535f;
pys::Color BACKGROUND_COLOR = pys::Color(15.0, 15.0, 19.0); //背景颜色 
char WINDOWS_TITLE[100] = "owo";

clock_t last_time = clock();
const clock_t dt = FRAME_SPAN * 1000;

pys::World w(FRAME_SPAN);
pys::Circle c(30);

void initGL(){ 
    //设置背景颜色和抗锯齿
    glClearColor(15.0 / 255.0, 15.0 / 255.0, 19.0 / 255.0, 1.0);
    glPointSize(4);
    glLineWidth(2);
    /*
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    */
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

void display(){
		//循环回调函数
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0);
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);

    w.render();
    w.update();

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

int main(int argc, char** argv){
    glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); //启用双缓冲，避免闪屏

    initGL();

    glutInitWindowPosition(2000, 50);
    glutInitWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT); //启用窗口
    glutCreateWindow(WINDOWS_TITLE);

    std::vector<pys::Point> v_;
    v_.push_back(pys::Point(0, 0));
    v_.push_back(pys::Point(30, 0));
    v_.push_back(pys::Point(30, 30));
    v_.push_back(pys::Point(0, 30));

    std::vector<pys::Point> v;
    v.push_back(pys::Point(-200, 0));
    v.push_back(pys::Point(200, 0));
    v.push_back(pys::Point(200, 10));
    v.push_back(pys::Point(-200, 10));

    pys::Polygon q(v_);
    pys::Polygon p(v);

    w.add(&q, 0, 200);
    w.add(&q, 25, 100);
    w.add(&p, 0, -200);
    w.world[2]->set_static();

    initGL();//设置背景颜色和抗锯齿
    glutReshapeFunc(&reshape);
    glutDisplayFunc(&display);
    glutKeyboardFunc(&keyboard);
    glutIdleFunc(&idle); //设置各种回调函数

    glutMainLoop(); //启用主循环
    return 0;
}
	