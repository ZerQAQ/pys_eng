#include"const.h"
#include"body.h"
#include"fpair.h"
#include"shape.h"
#include<Vector>

namespace pys{

    Circle::Circle(real r){
        radius = r;
    }

    Shape* Circle::clone() const{
        return new Circle(radius);
    }

    void Circle::rotate_shape(real) {}

    void Circle::compute_mass(real density){
        body->mass = density * PI * radius * radius;
        body->inertia = body->mass * sqr(radius) / 2;
        if(body->mass == 0) body->inv_mass = 0;
        else body->inv_mass = 1 / body->mass;
        if(body->inertia == 0) body->inv_inertia = 0;
        else body->inv_inertia = 1 / body->inertia;
    }

    void Circle::init(){
        compute_mass(DENSITY);
    }

    Shape::type Circle::get_type(){
        return circle;
    }


    Polygon::Polygon(std::vector<Point> vectices_){
        vectices = vectices_;
        vectices_num = vectices.size();
    }

    void Polygon::rotate_shape(real angle){
        for(int i = 0; i < vectices_num; i++){
            vectices[i] = rotate(vectices[i], -angle);
        }
        for(int i = 0; i < vectices_num; i++){
            normals[i] = rotate(normals[i], -angle);
        }
    }

    void Polygon::init(){
        Point center = Point(0, 0);
        for(int i = 0; i < vectices_num; i++){
            Vector edge = vectices[i + 1 == vectices_num?0:i + 1] - vectices[i];
            Vector normal = cross_product(edge, -1);
            if(normal * vectices[i] < 0) normal = -normal;
            normal.normalize();
            normals.push_back(normal); //计算边的法向量 朝外
            center += vectices[i];
        }
        center /= vectices_num;

        for(int i = 0; i < vectices_num; i++){
            vectices[i] -= center;
        } //确保图形的中心是(0, 0)

        compute_mass(DENSITY);
    }

    void Polygon::compute_mass(real density){
        body->mass = 0;
        body->inertia = 0;
        for(int i = 0; i < vectices_num; i++){
            real tri_mass = cross_product(
                (vectices[i + 1 == vectices_num?0:i + 1] - vectices[i]),
                (vectices[i])
            );
            tri_mass /= 2;
            tri_mass = tri_mass < 0? -tri_mass : tri_mass;
            tri_mass *= density;
            body->mass += tri_mass; //计算三角形质量并类加

            real a, b, c;
            a = (vectices[i]).len();
            b = (vectices[i + 1 == vectices_num?0:i + 1]).len();
            c = (vectices[i + 1 == vectices_num?0:i + 1] - vectices[i]).len(); //计算三边长
            real a3, b3, c3;
            a3 = a * a * a;
            b3 = b * b * b;
            c3 = c * c * c;
            real tri_inertia = tri_mass * (a3 + b3 + c3 + 3 * a * b * c);
            tri_inertia /= 12 * (a + b + c); //计算三角形绕质心的转动惯量
            Point mass_center = vectices[i]
                + vectices[i + 1 == vectices_num?0:i + 1];
            mass_center /= 3;
            real dist = mass_center.len();
            body->inertia += tri_inertia + tri_mass * sqr(dist); //平行轴定理 求三角形关于中心的转动惯量
        }
        if(body->mass == 0) body->inv_mass = 0;
        else body->inv_mass = 1 / body->mass;
        if(body->inertia == 0) body->inv_inertia = 0;
        else body->inv_inertia = 1 / body->inertia;
    }

    Shape* Polygon::clone() const{
        Polygon *ret = new Polygon(vectices);
        return ret;
    }

    Shape::type Polygon::get_type(){
        return polygon;
    }

    Point Polygon::get_support(Vector dir, int* index){
        int bestp = 0;
        real best_pro = vectices[0] * dir;
        for(int i = 1; i < vectices_num; i++){
            if(vectices[i] * dir > best_pro){
                best_pro = vectices[i] * dir;
                bestp = i;
            }
        }
        if(index) *index = bestp;
        return vectices[bestp];
    }
}