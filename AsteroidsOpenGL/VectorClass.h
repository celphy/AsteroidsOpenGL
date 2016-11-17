#pragma once


//Vector == Point but improves readability
typedef struct vector {
	float x;
	float y;
};

typedef struct Point {
	float x;
	float y;
};

class VectorClass
{
private:
	vector origin;
	vector direction;
	
public:
	VectorClass getIntersection(VectorClass vector); //Result can be 0, Point or Vector
	void addVector(vector v); 
	void subVector(vector v);
	void multVector(float factor);
	vector getOrigin();
	vector getDirection();
	void setOrigin(vector oArg);
	void setDirection(vector dArg);
	VectorClass(void);
	VectorClass(vector oArg, vector dArg);
	~VectorClass(void);
};

