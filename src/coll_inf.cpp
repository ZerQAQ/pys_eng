#include"coll_inf.h"
#include"polygon.h"
#include"cstdio"
#include"line.h"
#include<algorithm>

using std::swap;

#define pre(object, i) i == 0? object->edges_num : i - 1 
#define next(object, i) i == object->edges_num? 0 : i + 1

namespace pys{

    float inv(float v){
        return v == 0? 0 : 1.0 / v;
    }

    coll_inf::coll_inf(body *A = NULL, body *B = NULL):A(A), B(B){
        if(A != NULL && B != NULL)
            init();
    }

    void coll_inf::init(){
        sf = sqrt(A->static_friction * B->static_friction);
        df = sqrt(A->dynamic_friction * B->dynamic_friction);
        e = min(A->restitution, B->restitution);
    }

    float get_k(point A, point B){
        return (A.y - B.y) / (A.x - B.x);
    }

    line get_best_edge(polygon *object, vector dir){
        int spi;
        int *spip = &spi;
        point sp = object->get_supporting_point(dir, spip); //supporting point
        int npi = next(object, spi);
        int ppi = pre(object, spi);
        point np = object->vertexs[npi]; //next point
        point pp = object->vertexs[ppi]; //pervious point

        vector l1 = pp - sp;
        vector l2 = sp - np;
        l1.standard();
        l2.standard();

        if(fabs(l1 * dir) < fabs(l2 * dir)){
            return line(pp, sp);
        }
        else{
            return line(sp, np);
        }
    }

    void cut(point* points, int &pn, point cp, vector dir, int last_sept = 0){ //保留cp作为起点 dir为方向的点
        if(pn == 1) return;
        float o = cp * dir; //切割点在切割法线上的投影
        point pa = points[0];
        point pb = points[1];
        pn = 0;
        float a = pa * dir - o;
        float b = pb * dir - o; //两个入射边端点的投影
        
        if(a > 0) points[pn++] = pa;
        if(b > 0) points[pn++] = pb;

        if(a * b < 0){
            vector dv = pb - pa;
            float k = a / (a - b);
            points[pn++] = pa + dv * k; //计算被切割的点
        }

        if(last_sept){
            a = points[0] * dir;
            b = points[1] * dir;
            if(a > b){
                pn = 1;
            }
            if(b > a){
                pn = 1;
                points[0] = points[1];
            }
        }

        return;
    }

    void count_contact_points(polygon *A, polygon *B, coll_inf &inf){
        line ae = get_best_edge(A, inf.normal);
        line be = get_best_edge(B, inf.normal * -1);
        vector aev = ae.p2 - ae.p1;
        vector bev = be.p2 - be.p1;

        line ref, inc;
        vector normal;
        aev.standard(); bev.standard();
        if(fabs(aev * inf.normal) < fabs(bev * inf.normal)){
            ref = ae;
            inc = be;
            normal = A->center - ref.p1;
        }
        else{
            ref = be;
            inc = ae;
            normal = B->center - ref.p1;
        }

        inf.contact_point[0] = inc.p1;
        inf.contact_point[1] = inc.p2;
        inf.contact_count = 2;


        vector prodir = ref.p2 - ref.p1;
        prodir.standard();

        normal = normal - (prodir * (normal * prodir));
        normal.standard();

        if((ref.p2 - ref.p1) * prodir > 0){
            swap(ref.p1, ref.p2);
        }

        cut(inf.contact_point, inf.contact_count, ref.p1, prodir);
        cut(inf.contact_point, inf.contact_count, ref.p2, prodir * -1);
        cut(inf.contact_point, inf.contact_count, ref.p1, normal, 1);

    }

    void coll_inf::solve(){
        count_contact_points((polygon* ) A,(polygon* ) B, *this);

        float ima, imb, iia, iib;
        ima = inv(A->mass);
        imb = inv(B->mass);
        iia = inv(A->inertia);
        iib = inv(B->inertia);

        for(int i = 0; i < contact_count; i++){
            point cp = contact_point[i];
            vector ra = cp - A->center;
            vector rb = cp - B->center;
            vector va = A->speed + cross_product(A->anglespeed, ra);
            vector vb = B->speed + cross_product(B->anglespeed, rb);
            vector rv = vb - va;//求相对速度

            float van = rv * normal; //v along normal 在碰撞法线上的相对分速度
            if(van > 0) return; //违背常识的碰撞

            float acn = cross_product(ra, normal);
            float bcn = cross_product(rb, normal);
            float den = ima + imb  + sqr(acn) * iia + sqr(bcn) * iib; //求分母

            float coll_len = -(1.0 + e) * van / den;
            coll_len /= (float)contact_count; //碰撞冲量的大小

            vector impulse = normal * coll_len; //求碰撞冲量

            A->apply_impulse( impulse * -1, ra);
            A->apply_impulse( impulse, rb);

            rv = B->speed + cross_product(B->anglespeed, rb) -
                 A->speed - cross_product(A->anglespeed, ra);
            vector t_dir =  rv - (normal * (rv * normal));
            if(t_dir.length() == 0) return;
            t_dir.standard(); //求摩擦力方向
            
            float vat = rv * t_dir * -1; //v along t 在摩擦力反方向上的相对分速度
            float t_len = vat / den;
            t_len /= (float)contact_count; //摩擦力大小

            if(t_len == 0) break;

            vector tangen_impulse; 
            if(t_len < coll_len * sf){
                tangen_impulse = t_dir * t_len;
            }
            else{
                tangen_impulse = t_dir * coll_len * df * -1;
            }//求摩擦力冲量

            A->apply_impulse(tangen_impulse * -1, ra);
            B->apply_impulse(tangen_impulse, rb);
        }

        //位置修正

        vector correction = normal * (penetration / (ima + imb) * 0.8);
        A->position_correct(correction * - ima);
        B->position_correct(correction * imb);
    }
}