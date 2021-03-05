#pragma once
#include<iostream>

class Vec
{
public:
	Vec();
	Vec(float X, float Y, float Z);
	~Vec();

private:
	float X = 0, Y = 0, Z = 0;

public:
	//X
	float getX() { return X; }
	void setX(float newX) { X = newX; }

	//Y
	float getY() { return Y; }
	void setY(float newY) { Y = newY; }

	//Z
	float getZ() { return Z; }
	void setZ(float newZ) { Z = newZ; }

	float getLongitudeVector();
	void Normalize();
	Vec CrossVectors(Vec newVec);
	float ProductPoint(Vec newVec);
	float Distance(Vec newVec);


	Vec operator-(Vec Minus);
	Vec operator-=(Vec MinusEqual);
	Vec operator+(Vec Sum);
	Vec operator+=(Vec SumEqual);
	Vec operator*(float Multiply);
	Vec operator=(float Equal);
	Vec operator/=(int DivisionEqual);
};

