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

	float fpair::operator * (const fpair& oth){
		return x * oth.x + y * oth.y;
	}//点乘

	fpair fpair::operator / (const float& v){
		return fpair(this->x / v, this->y / v);
	}
	//重载向量之间的运算符

	fpair fpair::standard(){
		return *this / this->length();
	}//标准化向量

	typedef fpair point;
	typedef fpair vector;

	vector rotate(const vector vect, const float angle){
		return vector(vect.x * cos(angle) + vect.y * sin(angle),
					  -vect.x * sin(angle) + vect.y * cos(angle));
	}
}