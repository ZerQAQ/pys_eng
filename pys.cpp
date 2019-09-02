#include<cstdio>
#include<cmath>
#include<ctime>

#define PYS_INCLUDED

namespace pys{

	float max(float a, float b){
		return a>b?a:b;
	}
	
	float min(float a, float b){
		return a<b?a:b;
	}

	float XMIN = -400;
	float XMAX = 400;
	float YMIN = -200;
	float YMAX = 250;
	float RESTITUTION_ON_WALL = 1.95;
	const int COLLISION_DETC_TIME_PER_SEPT = 10;

	class fpair
	{
		public:
			float x, y;
			fpair(float x = 0, float y = 0):x(x), y(y) {}

			float sqlength(){
				return x * x + y * y;
			}
			
			float length(){
				return sqrt(sqlength());
			}

			fpair operator + (const fpair& oth){
				return fpair(this->x + oth.x, this->y + oth.y);
			}
			
			void operator += (const fpair& oth){
				*this = *this + oth;
			}

			fpair operator - (const fpair& oth){
				return fpair(this->x - oth.x, this->y - oth.y);
			}

			void operator -= (const fpair& oth){
				*this = *this - oth;
			}

			fpair operator * (const float& v){
				return fpair(this->x * v, this->y * v);
			}//数量乘

			float operator * (const fpair& oth){
				return x * oth.x + y * oth.y;
			}//点乘

			fpair operator / (const float& v){
				return fpair(this->x / v, this->y / v);
			}
			//重载向量之间的运算符

			fpair standard(){
				return *this / this->length();
			}//标准化向量
	}; 

	typedef fpair point;
	typedef fpair vector;

	vector G = vector(0, -500);

	vector rotate(const vector& vect, const float& angle){
		return vector(vect.x * cos(angle) + vect.y * sin(angle),
					  -vect.x * sin(angle) + vect.y * cos(angle));
	}

	class body{
		public:
		point center;
		vector speed, acceleration, force;
		float rate, mass, anglespeed, restitution;

		body (point center = point(0, 0), float mass = 0, vector speed = vector(0, 0))
			:center(center), speed(speed), mass(mass){
				acceleration = force = vector(0, 0);
				rate = sqrt(speed.x * speed.x + speed.y * speed.y);
				anglespeed = 0;
				restitution = 0.98;
			}

		virtual ~body() {};

		void set_anglespeed(float v){
			anglespeed = v;
		}

		point transfrom_by_center(float angle, point p){
			vector relat_vector = p - center;
			relat_vector = rotate(relat_vector, angle);
			return center + relat_vector;
		}

		void receive_force(const vector Force){
			force = force + Force;
		}

		virtual float min_x(){
			return center.x;
		}
		
		virtual float max_x(){
			return center.x;
		}

		virtual float min_y(){
			return center.y;
		}

		virtual float max_y(){
			return center.y;
		}

		void count_force(float time){
			force = vector(0, 0);
			force += G * mass;
			if(min_y() < YMIN){
				force -= G * mass;
				if(speed.y < 0)
				force += vector(0, - RESTITUTION_ON_WALL * mass * speed.y / time);
			}
			if(YMAX < max_y() && speed.y > 0) 
				force += vector(0, - RESTITUTION_ON_WALL * mass * speed.y / time);
			if(min_x() < XMIN && speed.x < 0) 
				force += vector(RESTITUTION_ON_WALL * mass * - speed.x / time, 0);
			if(XMAX < max_x() && speed.x > 0) 
				force += vector(RESTITUTION_ON_WALL * mass * - speed.x / time, 0);
		}

		void update_1(const float &time){
			count_force(time);
			acceleration = force / mass;
			speed += acceleration * time;
			center += speed * time;
		}
	};

	class rectangle: public body {
		public:
			point leftup, leftdown, rightup, rightdown;

			rectangle(point leftup,
					  point rightdown,
					  float mass,
					  vector speed = vector(0, 0))
					  :body(point((leftup.x + rightdown.x) / 2, (leftup.y + rightdown.y) / 2), mass, speed),
			 		   leftup(leftup), rightdown(rightdown){
							leftdown = point(leftup.x , rightdown.y);
							rightup = point(rightdown.x, leftup.y);
					}

			float max_x(){
				return max(max(leftdown.x, leftup.x), max(rightdown.x, rightup.x));
			}

			float min_x(){
				return min(min(leftdown.x, leftup.x), min(rightdown.x, rightup.x));
			}

			float max_y(){
				return max(max(leftdown.y, leftup.y), max(rightdown.y, rightup.y));
			}

			float min_y(){
				return min(min(leftdown.y, leftup.y), min(rightdown.y, rightup.y));
			}

			void transfrom(float angle){
				leftup = transfrom_by_center(angle, leftup);
				leftdown = transfrom_by_center(angle, leftdown);
				rightdown = transfrom_by_center(angle, rightdown);
				rightup = transfrom_by_center(angle, rightup);
			}

			void update_0(const float time){
				update_1(time);
				leftup += speed * time;
				leftdown += speed * time;
				rightup += speed * time;
				rightdown += speed * time;
				transfrom(anglespeed * time);
			}

			void update(const float time){
				for(int i = 0; i < COLLISION_DETC_TIME_PER_SEPT; i++) update_0(time / COLLISION_DETC_TIME_PER_SEPT);
			}
	};

	class circle: public body{
		public:
			point flag_point;
			float radius;

			circle(point center, float radius, float mass, vector speed = vector(0, 0))
			:body(center, mass, speed), radius(radius){
				flag_point = center + point(radius, 0);
			}

			float max_x(){
				return center.x + radius;
			}

			float min_x(){
				return center.x - radius;
			}

			float max_y(){
				return center.y + radius;
			}

			float min_y(){
				return center.y - radius;
			}

			void transfrom(float angle){
				flag_point = transfrom_by_center(angle, flag_point);
			}

			void update_0(float time){
				update_1(time);
				this->flag_point += speed * time;
				transfrom(this->anglespeed * time);
			}

			void update(const float time){
				for(int i = 0; i < COLLISION_DETC_TIME_PER_SEPT; i++) update_0(time / (float)COLLISION_DETC_TIME_PER_SEPT);
			//	printf("%lf, %lf\n", force.x, force.y);
			}
	};

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
	}
}
