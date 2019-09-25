#include"fpair.h"
#include<algorithm>
#include<cmath>

namespace pys{

	Fpair::Fpair(real x, real y):x(x), y(y) {}

	void Fpair::set(real x_, real y_){
		x = x_;
		y = y_;
	}

	real Fpair::sqrlen(){
		return x * x + y * y;
	}
	
	real Fpair::len(){
		return sqrt(sqrlen());
	}

	Fpair Fpair::operator + (const Fpair& oth){
		return Fpair(this->x + oth.x, this->y + oth.y);
	}
	
	void Fpair::operator += (const Fpair& oth){
		*this = *this + oth;
	}

	Fpair Fpair::operator - (void) const{
		return Fpair(-x, -y);
	}

	Fpair Fpair::operator - (const Fpair& oth){
		return Fpair(this->x - oth.x, this->y - oth.y);
	}

	void Fpair::operator -= (const Fpair& oth){
		*this = *this - oth;
	}

	Fpair Fpair::operator * (const real& v){
		return Fpair(this->x * v, this->y * v);
	}//数量乘

	void Fpair::operator *= (const real& v){
		*this = *this * v;
	}

	real Fpair::operator * (const Fpair& oth){
		return x * oth.x + y * oth.y;
	}//点乘

	void Fpair::operator *= (const Fpair& oth){
		*this = *this * oth;
	}

	Fpair Fpair::operator / (const real& v){
		return Fpair(this->x / v, this->y / v);
	}
	//重载向量之间的运算符

	void Fpair::operator /= (const real& v){
		*this = *this / v;
	}

	void Fpair::normalize(){
		if(this->len() == 0) return;
		return *this /= this->len();
	}//标准化向量

	Fpair Fpair::right_normal(){
		return Fpair(-this->y, this->x);
	}

	void Fpair::rotate(const real angle){
		real nx = x * cos(angle) - y * sin(angle);
		real ny = x * sin(angle) + y * cos(angle);
		this->x = nx;
		this->y = ny;
	}

	Vector operator * (float s, const Vector& v){
    	return Vector(s * v.x, s * v.y);
    }

	Vector rotate(Vector vect, const real angle, const Vector center){
		vect -= center;
		vect = Vector(vect.x * cos(angle) + vect.y * sin(angle),
					  -vect.x * sin(angle) + vect.y * cos(angle));
		vect += center;
		return vect;
	}

	real cross_product(const Vector a, const Vector b){
		return a.x * b.y - a.y * b.x;
	}

	Vector cross_product(const Vector a, const real v){
		return Vector(v * a.y, -v * a.x);
	}

	Vector cross_product(const real v, const Vector a){
		return Vector(-v * a.y, v * a.x);
	}

	real sqr(real v){
		return v * v;
	}

	real max(real a, real b){
		return a>b?a:b;
	}

	real min(real a, real b){
		return a<b?a:b;
	}

	int max(int a, int b){
		return a>b?a:b;
	}

	int min(int a, int b){
		return a<b?a:b;
	}
}