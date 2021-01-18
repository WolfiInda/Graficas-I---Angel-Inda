#include "Vec.h"


Vec::Vec()
{
	
}

Vec::Vec(float newX, float newY, float newZ)
{
	X = newX;
	Y = newY;
	Z = newZ;
}

Vec::~Vec()
{
}

float Vec::getLongitudeVector()
{
	float Longitude = 0;
	Longitude = pow((pow(X, 2) + pow(Y, 2) + pow(Z, 2)), 0.5);

	return Longitude;
}

void Vec::Normalize()
{
	X = X / getLongitudeVector();
	Y = Y / getLongitudeVector();
	Z = Z / getLongitudeVector();
}

Vec Vec::CrossVectors(Vec newVec)
{
	float newX = ((Y * newVec.Z) - (newVec.Y * Z));
	float newY = ((Z * newVec.X) - (newVec.Z * X));
	float newZ = ((X * newVec.Y) - (newVec.X * Y));

	return Vec(newX, newY, newZ);
}

float Vec::ProductPoint(Vec newVec)
{
	X = (X * newVec.X);
	Y = (Y * newVec.Y);
	Z = (Z * newVec.Z);

	return X + Y + Z;
}

float Vec::Distance(Vec newVec)
{
	float Distance = pow((pow((newVec.X - X), 2) + pow((newVec.Y - Y), 2)), 0.5);

	return Distance;
}

Vec Vec::operator-(Vec Minus)
{
	return Vec(X - Minus.X, Y - Minus.Y, Z - Minus.Z);
}
