#include"body.h"
#include"shape.h"
#include"coll_inf.h"
#include"collision.h"
#include"cmath"

namespace pys{

    typedef bool (*collision_func) (Body *A, Body *B, Coll_inf*);

    collision_func coll_dect_func[Shape::count][Shape::count] ={
        {
            circle_to_circle, circle_to_polygon
        },
        {
            polygon_to_circle, polygon_to_polygon
        },
    };

    bool collision_dect(Body *A, Body *B, Coll_inf *inf){
        inf->A = A;
        inf->B = B;
        return coll_dect_func[A->shape->get_type()][B->shape->get_type()](A, B, inf);
    }

    bool circle_to_circle(Body *A, Body *B, Coll_inf *inf){

        Circle *a = (Circle*) A->shape;
        Circle *b = (Circle*) B->shape;

        Vector rel_pos = B->center - A->center;
        real r_sum = a->radius + b->radius;

        if(rel_pos.sqrlen() > sqr(r_sum)){
            return 0; //没有碰撞
        }

        real d = rel_pos.len();
        inf->peneration = r_sum - d;

        if(d != 0)
            inf->normal = rel_pos / d;
        else
            inf->normal = Vector(1, 0);

        inf->contact_count = 1;
        inf->contact_points[0] = (A->center + B->center) / 2;
        return 1;
    }

    bool circle_to_polygon(Body *A, Body *B, Coll_inf* inf){
        Circle *a = (Circle*) A->shape;
        Polygon *b = (Polygon*) B->shape;
        for(int i = 0; i < b->vectices_num; i++){
            Vector n = b->normals[i];

        }
    }

    bool polygon_to_circle(Body *A, Body *B, Coll_inf* inf){
        
    }

    void count_best_line(Polygon *o, Vector dir, Point *line){
        int *p_ind = new int;
        Point p = o->get_support(dir, p_ind);
        Point np = o->vectices[(*p_ind + 1) == o->vectices_num?0:(*p_ind + 1)];
        Point pp = o->vectices[*p_ind? (*p_ind - 1) : o->vectices_num - 1];
        Vector l1 = p - np;
        Vector l2 = pp - p;
        l1.normalize();
        l2.normalize();

        if(fabs(l1 * dir) < fabs(l2 * dir)){
            line[0] = p + o->body->center;
            line[1] = np + o->body->center;
        }
        else{
            line[0] = pp + o->body->center;
            line[1] = p + o->body->center;
        }
        return;
    }

    void cut(Point* Points, int &pn, Point cp, Vector dir, int last_sept = 0){
        if(pn == 1) return;
        Point pa = Points[0];
        Point pb = Points[1];
        pn = 0;

        real pro_cp = cp * dir;
        real pro_a = pa * dir - pro_cp;
        real pro_b = pb * dir - pro_cp;

        if(pro_a > 0) Points[pn++] = pa;
        if(pro_b > 0) Points[pn++] = pb;  //加入在cp为分解 dir方向上的点

        if(pro_a * pro_b < 0){
            Vector dv = pb - pa;
            real k = pro_a / (pro_a - pro_b);
            Points[pn++] = pa + dv * k;
        }

        if(last_sept){
            real pro0 = Points[0] * dir;
            real pro1 = Points[1] * dir;
            if(fabs(pro0 - pro1) < EPSILON) return;
            if(pro0 > pro1){
                pn = 1;
            }
            if(pro1 > pro0){
                pn = 1;
                Points[0] = Points[1];
            }
        }

        return;
    }

    void count_contact_points(Polygon *A, Polygon *B, Coll_inf *inf){
        Point la[2], lb[2];
        count_best_line(A, inf->normal, la);
        count_best_line(B, -inf->normal, lb);

        Point *ref, *inc;
        Vector la_ = la[1] - la[0];
        Vector lb_ = lb[1] - lb[0];
        la_.normalize();
        lb_.normalize(); 

        Vector normal;

        if(fabs(la_ * inf->normal) < fabs(lb_ * inf->normal)){
            ref = la;
            inc = lb;
            normal = -inf->normal;
        }
        else{
            ref = lb;
            inc = la;
            normal = inf->normal;
        } //确定反射面和碰撞面 以及碰撞法线

        inf->contact_points[0] = inc[0];
        inf->contact_points[1] = inc[1];
        Vector ref_ = ref[1] - ref[0];
        ref_.normalize();

        cut(inf->contact_points, inf->contact_count, ref[0], ref_);
        cut(inf->contact_points, inf->contact_count, ref[1], -ref_);
        cut(inf->contact_points, inf->contact_count, ref[1], normal, 1);
    }


    bool SAT(Polygon *A, Polygon *B, Coll_inf* inf){ 
        //分离轴检测算法
        Point Acenter = A->body->center;
        Point Bcenter = B->body->center;
        Vector rel_p = Bcenter - Acenter;

        real min_penetration = 1e10f;
        Vector best_normal(0, 0);

        for(int i = 0; i < A->vectices_num; i++){
            Vector n = A->normals[i];
            float pro_bet_cent = fabs(n * rel_p);
            float pro_A, pro_B;
            if(rel_p * n > 0){
                Point pa = A->get_support(n);
                Point pb = B->get_support(-n);
                pro_A = A->get_support(n) * n;
                pro_B = B->get_support(-n) * -n;
            }
            else{
                pro_A = A->get_support(-n) * -n;
                pro_B = B->get_support(n) * n;
            }
            if(pro_A + pro_B - pro_bet_cent < 0){
                return 0; //找到分离轴
            }
            real new_penetration = pro_A + pro_B - pro_bet_cent;
            if(min_penetration > new_penetration){
                min_penetration = new_penetration;
                best_normal = n;
            }
        }
        if(inf->peneration > min_penetration){
            inf->peneration = min_penetration;
            inf->normal = best_normal;
        }
        return 1;
    }

    bool polygon_to_polygon(Body *A, Body *B, Coll_inf* inf){
        Polygon *a = (Polygon*) (A->shape);
        Polygon *b = (Polygon*) (B->shape);
        inf->peneration = 1e10;
        if(!SAT(a, b, inf)) return 0;
        if(!SAT(b, a, inf)) return 0;
        if(inf->normal * (B->center - A->center) < 0) inf->normal = -inf->normal;
        count_contact_points(a, b, inf);
        return 1;
    }
}