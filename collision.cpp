#include"collision.h"

namespace pys{
    struct coll_inf{
		body *A, *B;
		float penetration;
		vector normal;

		coll_inf(body *A, body *B, float penetration = 0, vector normal = 0)
		:A(A), B(B), penetration(penetration), normal(normal) {}
	};

	void solve_collision(coll_inf *inf){
		vector rel_speed = inf->B->speed - inf->A->speed; //相对速度
		float rel_along_normal = rel_speed * inf->normal; //相对速度在碰撞法线上的投影

		if(rel_along_normal > 0) return; //违反常识的碰撞

		float e = min(inf->A->restitution, inf->B->restitution); //求最小应变系数
		float A_inv_m = 1 / inf->A->mass, B_inv_m = 1 / inf->B->mass;

		float j = -(1 + e) * rel_along_normal;
		j /= A_inv_m + B_inv_m; //计算冲量大小

		inf->A->speed -= inf->normal * j / inf->A->mass;
		inf->B->speed += inf->normal * j / inf->B->mass;//应用冲量
	}

	bool collision_detc(circle *A, circle *B){
		vector rel_pos = B->center - A->center; //相对位置
		float r = A->radius + B->radius;

		if(rel_pos.sqlength() > r * r)
			return 0; //没有碰撞
		
		float d = rel_pos.length();
		coll_inf inf = coll_inf(A, B);

		if(d != 0){
			inf.penetration = r - d;
			inf.normal = rel_pos / d;
		}
		else{
			inf.penetration = r;
			inf.normal = vector(1, 0);
		}

		solve_collision(&inf);
		return 1;
	}

	bool collision_detc(rectangle *A, rectangle *B){
		vector rel_pos = B->center - A->center;
		float x_dis = A->xlen + B->xlen, x_pene;
		x_dis /= 2;

		if(x_pene = x_dis - fabs(rel_pos.x) > 0){ //x轴投影检测
			float y_dis = A->ylen + B->ylen, y_pene;
			y_dis /= 2;
			if(y_pene = y_dis - fabs(rel_pos.y) > 0){ //y轴投影检测
				coll_inf inf(A, B);
				if(x_pene > y_pene){

				}
			}
		}
	}

	template <typename T>
	bool collision_detc(T A, body *B){
		switch(B->type){
			case 1: return collision_detc(A, (circle*) B);
			case 2: return collision_detc(A, (rectangle*) B);
		}
	}

	bool collision_detc(body *A, body *B){
		switch(A->type){
			case 1: return collision_detc<circle*>((circle*) A, B);
			case 2: return collision_detc<rectangle*>((rectangle*) A, B);
		}
	}
}