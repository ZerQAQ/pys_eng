#include<cstdio>
#include<cmath>
#include<ctime>
#include<algorithm>

#define PYS_INCLUDED

namespace pys{

	float XMIN = -400;
	float XMAX = 400;
	float YMIN = -200;
	float YMAX = 250;
	const int COLLISION_DETC_TIME_PER_SEPT = 1;

	class fpair
	{
		public:
			float x, y;
			fpair(float x = 0, float y = 0):x(x), y(y) {}

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
			}

			fpair operator / (const float& v){
				return fpair(this->x / v, this->y / v);
			}
			//重载向量之间的运算符
	}; 

	typedef fpair point;
	typedef fpair vector;

	vector G = vector(0, -2000);

	vector rotate(const vector& vect, const float& angle){
		return vector(vect.x * cos(angle) + vect.y * sin(angle),
					  -vect.x * sin(angle) + vect.y * cos(angle));
	}

	class body{
		public:
			point center;
			vector speed, acceleration, force;
			float rate, mass;
		void receive_force(const vector force){
			this->force = this->force + force;
		}

		void update_1(const float &time){
			this->acceleration = this->force / mass;
			this->speed += this->acceleration * time;
			this->center += this->speed * time;
		}
	};

	class rectangle: public body {
		public:
			point center, leftup, rightdown;
			vector speed, force, acceleration;
			float rate, mass;

			rectangle(point leftup,
					  point rightdown,
					  float mass,
					  vector speed = vector(0, 0))
			:center(center), leftup(leftup), rightdown(rightdown), mass(mass), speed(speed){
				this->rate = sqrt(speed.x * speed.x + speed.y * speed.y);
				this->center = point((leftup.x + rightdown.x) / 2, (leftup.y + rightdown.y) / 2);
			}

			void update_0(const float time){
				update_1(time);
				this->leftup += this->speed * time;
				this->rightdown += this->speed * time;
				this->rate = sqrt(this->speed.x * this->speed.x + this->speed.y * this->speed.y);
			}

			void update(const float time){
				for(int i = 0; i < COLLISION_DETC_TIME_PER_SEPT; i++) update_0(time / COLLISION_DETC_TIME_PER_SEPT);
			}
	};

	class circle{
		public:
			point center, flag_point;
			float mass, radius, rate, anspeed;
			vector speed, acceleration, force;

			circle(point center, float radius, float mass, float anspeed = 0, vector speed = vector(0, 0))
			:center(center), radius(radius), mass(mass), anspeed(anspeed), speed(speed) {
				rate = sqrt(speed.x * speed.x + speed.y * speed.y);
				flag_point = center + point(radius, 0);
			}

			void count_force(float time){
				force = vector(0, 0);
				force += G * mass;
				if(center.y - radius - YMIN < 0) force -= G * mass;
				if(center.y - radius - YMIN < 0 && speed.y < 0) force += vector(0, - 2 * mass * speed.y / time);
				if(YMAX - (center.y + radius) < 0 && speed.y > 0) force += vector(0, - 2 * mass * speed.y / time);
				if(center.x - radius - XMIN < 0 && speed.x < 0) force += vector(2 * mass * - speed.x / time, 0);
				if(XMAX - (center.x + radius) < 0 && speed.x > 0) force += vector(2 * mass * - speed.x / time, 0);
			}

			void transfrom(float ct){
				vector relat_vector = flag_point - center;
				relat_vector = rotate(relat_vector, ct);
				flag_point = center + relat_vector;
			}

			void update_0(float time){
				count_force(time);
			//	printf("%lf, %lf\n", center.x, center.y);
				this->acceleration = this->force / mass;
				this->speed += this->acceleration * time;
				this->center += this->speed * time;
				this->flag_point += this->speed * time;
				this->rate = sqrt(this->speed.x * this->speed.x + this->speed.y * this->speed.y);
				transfrom(anspeed * time);
			}

			void update(const float time){
				for(int i = 0; i < COLLISION_DETC_TIME_PER_SEPT; i++) update_0(time / (float)COLLISION_DETC_TIME_PER_SEPT);
	//			printf("%lf, %lf\n", force.x, force.y);
			}
	};
}
