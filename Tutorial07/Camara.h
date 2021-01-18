#pragma once
#include "Vec.h"
#include<iostream>

class Camara
{
public:
	Camara();
	~Camara();

public:
	Vec LookUp, LookAt, LookEye;

	Vec getLookUp() { return LookUp; }
	void setLookUp(Vec newLookUp) { LookUp = newLookUp; }

	Vec getLookAt() { return LookAt; }
	void setLookAt(Vec newLookAt) { LookAt = newLookAt; }

	Vec getLookEye() { return LookEye; }
	void setLookEye(Vec newLookEye) { LookEye = newLookEye; }

	float* getViewMatrix(Vec Up, Vec At, Vec Eye);
	float* getPerspectiveMatrix(float FOV, float AspectRatio, float Near, float Far);
	float* getOrthographicMatrix(float ViewWidth, float ViewHeight, float Near, float Far);
};

