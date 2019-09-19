#include"fpair.h"

namespace pys{

	fpair::fpair(float x, float y):x(x), y(y) {}

	float fpair::sqlength(){
		return x * x + y * y;
	}
	
	float fpair::length(){
		return sqrt(sqlength());
	}

	fpair fpair::operator + (const fpair& oth){
		return fpair(this->x + oth.x, this->y + oth.y);
	}
	
	void fpair::operator += (const fpair& oth){
		*this = *this + oth;
	}

	fpair fpair::operator - (const fpair& oth){
		return fpair(this->x - oth.x, this->y - oth.y);
	}

	void fpair::operator -= (const fpair& oth){
		*this = *this - oth;
	}

	fpair fpair::operator * (const float& v){
		return fpair(this->x * v, this->y * v);
	}//数量乘

	void fpair::operator *= (const float& v){
		*this = *this * v;
	}

	float fpair::operator * (const fpair& oth){
		return x * oth.x + y * oth.y;
	}//点乘

	void fpair::operator *= (const fpair& oth){
		*this = *this * oth;
	}

	fpair fpair::operator / (const float& v){
		return fpair(this->x / v, this->y / v);
	}
	//重载向量之间的运算符

	void fpair::operator /= (const float& v){
		*this = *this / v;
	}

	void fpair::standard(){
		return *this /= this->length();
	}//标准化向量

	fpair fpair::right_normal(){
		return fpair(-this->y, this->x);
	}

	void fpair::rotate(const float angle){
		float nx = x * cos(angle) + y * sin(angle);
		float ny = -x * sin(angle) + y * cos(angle);
		this->x = nx;
		this->y = ny;
	}

	vector rotate(vector vect, const float angle, const vector center){
		vect -= center;
		vect = vector(vect.x * cos(angle) + vect.y * sin(angle),
					  -vect.x * sin(angle) + vect.y * cos(angle));
		vect += center;
		return vect;
	}

	float cross_product(const vector a, const vector b){
		return a.x * b.y - a.y * b.x;
	}

	vector cross_product(const vector a, const float v){
		return vector(v * a.y, -v * a.x);
	}

	vector cross_product(const float v, const vector a){
		return vector(-v * a.y, v * a.x);
	}

	float sqr(float v){
		return v * v;
	}
}