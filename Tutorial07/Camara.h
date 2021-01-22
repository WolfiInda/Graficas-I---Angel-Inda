#pragma once
#include "Vec.h"
#include<iostream>

class Camara
{
public:
	//Camara();
	Camara(Vec newEye, Vec newLookAt, Vec newUp);
	~Camara();

public:
	Vec Eye, LookAt, Up, xaxis, yaxis, zaxis;

	Vec getLookEye() { return Eye; }
	void setLookEye(Vec newLookEye) { Eye = newLookEye; }

	Vec getLookAt() { return LookAt; }
	void setLookAt(Vec newLookAt) { LookAt = newLookAt; }

	Vec getLookUp() { return Up; }
	void setLookUp(Vec newLookUp) { Up = newLookUp; }

	Vec getZaxis(Vec At, Vec Eye);
	
	Vec getXaxis(Vec Up, Vec Zaxis);

	Vec getYaxis(Vec Zaxis, Vec Xaxis);

	void CamaraMove(Vec newVec);

	float* getViewMatrix(Vec Up, Vec At, Vec Eye);
	float* getViewMatrix();
	float* getPerspectiveMatrix(float FOV, float AspectRatio, float Near, float Far);
	float* getOrthographicMatrix(float ViewWidth, float ViewHeight, float Near, float Far);
};

