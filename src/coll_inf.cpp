#include"fpair.h"
#include"body.h"
#include"coll_inf.h"
#include<cmath>

namespace pys{

    Coll_inf::Coll_inf(Body *a, Body* b):A(a), B(b){}

    void Coll_inf::init(){
        static_friction = sqrt(A->static_friction * B->static_friction);
        dynamic_friction = sqrt(A->dynamic_friction * B->dynamic_friction);
        restitution = min(A->restitution, B->restitution);
    }

    void Coll_inf::apply_impulse(){
        init();
        if(A->inv_mass + B->inv_mass == 0) return;

        for(int i = 0; i < contact_count; i++){
            ra[i] = contact_points[i] - A->center;
            rb[i] = contact_points[i] - B->center;
            Vector rv = B->speed + cross_product(B->anglespeed, rb[i]) -
                        A->speed - cross_product(A->anglespeed, ra[i]); //相对速度
            
            real contact_vec = rv * normal; //碰撞法线上的相对速度

            if(contact_vec > 0) return; //违反常识的碰撞

            real racn = cross_product(ra[i], normal);
            real rbcn = cross_product(rb[i], normal);
            real inv_mass_sum = A->inv_mass + B->inv_mass
                + sqr(racn) * A->inv_inertia
                + sqr(rbcn) * B->inv_inertia;

            real j = - (1.0 + restitution) * contact_vec; //碰撞冲量
            j /= inv_mass_sum;
            j /= (real)contact_count;

            impulse[i] = normal * j;

            Vector t = rv - (normal * (rv * normal));
            t.normalize();

            real jt = - (rv * t);
            jt /= inv_mass_sum;
            jt /= (real)contact_count;

            if(fabs(jt) < EPSILON){
                tangent_impluse[i] = 0;
                continue;
            }

            if(fabs(jt) < j * static_friction)
                tangent_impluse[i] += t * jt; //摩擦冲量
            else
                tangent_impluse[i] += t * -j * dynamic_friction;
        }

        for(int i = 0; i < contact_count; i++){
            A->apply_impulse(-impulse[i], ra[i]);
            B->apply_impulse(impulse[i], rb[i]);
            A->apply_impulse(-tangent_impluse[i], ra[i]);
            B->apply_impulse(tangent_impluse[i], rb[i]);
        }
        position_correct();
    }

    void Coll_inf::position_correct(){
        const real k = PENETRATION_ALLOWANCE;
        const real p = PENETRATION_CORRECT_PERCENT;
        Vector correction = max(peneration - k, 0.0) * p * normal;
        correction /= (A->inv_mass + B->inv_mass);
        A->center -= correction * A->inv_mass;
        B->center += correction * B->inv_mass;
    }
}
