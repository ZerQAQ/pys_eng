#include"coll_inf.h"
#include"circle.h"
#include"rectangle.h"
#include"polygon.h"
#include"collision.h"
#include<cstdio>

namespace pys{

	bool collision_detc(circle *A, circle *B){
		vector rel_pos = B->center - A->center; //相对位置
		float r = A->radius + B->radius;
		if(rel_pos.sqlength() > r * r)
			return 0; //没有碰撞
		
		float d = rel_pos.length();
		coll_inf inf(A, B);

		if(d != 0){
			inf.penetration = r - d;
			inf.normal = rel_pos / d;
		}
		else{
			inf.penetration = r;
			inf.normal = vector(1, 0);
		}

		inf.contact_count = 1;
		inf.contact_point[0] = (A->center + B->center) / 2;
		inf.init();
		inf.solve();
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

	float count_1d_line_penetration(fpair A, fpair B){
		if(A.x > B.x) swap(A, B);
		return A.y - B.x;
	}

	coll_inf SAT_from_A_to_B(polygon *A, polygon *B){
		int len = A->edges_num;
		float min_penetration = 1e10f;
		vector min_normal;
		for(int i = 0; i < len; i++){
			vector n = A->edges_normal[i];
			float projection_between_center = fabs( n * (A->center - B->center));
			float projection_A, projection_B;
			if((B->center - A->center) * n > 0){
				projection_A = (A->get_supporting_point(n) - A->center) * n;
				projection_B = (B->center - B->get_supporting_point(n * -1.0)) * n;
			}
			else{
				projection_A = (A->center - A->get_supporting_point(n * -1.0)) * n;
				projection_B = (B->get_supporting_point(n) - B->center) * n;
			}
			if(projection_A + projection_B <= projection_between_center){
				coll_inf ret(A, B);
				ret.penetration = -1;
				return ret;
			}
			float new_penetration = projection_A + projection_B - projection_between_center;
			if(new_penetration < min_penetration){
				min_penetration = new_penetration;
				min_normal = n;
			}
		}
		coll_inf ret(A, B);
		ret.normal = min_normal;
		ret.penetration = min_penetration;
		return ret;
	}

	point find_clipping_point(polygon *A, polygon *B, coll_inf &inf);

	bool collision_detc(polygon *A, polygon *B){
		coll_inf inf_1 = SAT_from_A_to_B(A, B);
		if(inf_1.penetration < 0) return 0;
		coll_inf inf_2 = SAT_from_A_to_B(B, A);
		if(inf_2.penetration < 0) return 0;
		coll_inf inf(A, B);
		if(inf_1.penetration < inf_2.penetration){
			inf.penetration = inf_1.penetration;
			inf.normal = inf_1.normal;
		}
		else{
			inf.penetration = inf_2.penetration;
			inf.normal = inf_2.normal * -1;
		}

		if(inf.normal * (B->center - A->center) < 0) inf.normal *= -1.0;

		inf.init();
		inf.solve();
		return 1;
	}


	bool collision_detc(polygon *A, circle *B){
		
	}

	bool collision_detc(circle *A, polygon *B){
		return collision_detc(B, A);
	}

	template <typename T>
	bool collision_detc(T A, body *B){
		switch(B->type){
			case 1: return collision_detc(A, (circle*) B);
			case 2: return collision_detc(A, (rectangle*) B);
			case 3: return collision_detc(A, (polygon*) B);
			default: break;
		}
	}

	bool collision_detc(body *A, body *B){
		switch(A->type){
			case 1: return collision_detc<circle*>((circle*) A, B);
			case 2: return collision_detc<rectangle*>((rectangle*) A, B);
			case 3: return collision_detc<polygon*>((polygon*) A, B);
			default: break;
		}
	}
}