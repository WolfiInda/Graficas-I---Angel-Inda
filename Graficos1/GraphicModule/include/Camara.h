#pragma once
#include "Vec.h"
#include<iostream>
#include <math.h>

class Camara
{
public:
	Camara();
	Camara(Vec newEye, Vec newLookAt, Vec newUp, float newFOV, float newNear, float newFar, float newViewWidth, float newViewHeight, bool newPerspective);
	Camara(Vec newEye, Vec newLookAt, Vec newUp);
	~Camara();

public:

	bool Perspective = true;
	float FOV = 0, Near = 0, Far = 0, ViewWidth = 0, ViewHeight = 0, AspectRatio = 0;
	Vec Eye, LookAt, Up, xaxis, yaxis, zaxis;

	Vec getLookEye() { return Eye; }
	void setLookEye(Vec newLookEye) { Eye = newLookEye; }

	Vec getLookAt() { return LookAt; }
	void setLookAt(Vec newLookAt) { LookAt = newLookAt; }

	Vec getLookUp() { return Up; }
	void setLookUp(Vec newLookUp) { Up = newLookUp; }

	bool getPerspective() { return Perspective; }
	void setPerspective(bool newPerspective) { Perspective = newPerspective; }

	Vec getZaxis() { return zaxis; };
	void setZaxis();
	
	Vec getXaxis() { return xaxis; }
	void setXaxis();

	Vec getYaxis() { return yaxis; }
	void setYaxis();

	void CamaraMove(Vec newVec);

	void setWidth(int newwidth) { ViewWidth = newwidth; }
	int getWidth() { return ViewWidth; }
	void setheight(int newheight) { ViewHeight = newheight; }
	int getheight() { return ViewHeight ; }

	float* getViewMatrix(Vec Up, Vec At, Vec Eye);
	float* getViewMatrix();
	float* getProyection();
	float* getPerspectiveMatrix(float FOV, float AspectRatio, float Near, float Far);
	float* getOrthographicMatrix(float ViewWidth, float ViewHeight, float Near, float Far);

	Vec setMouseRotate(Vec MouseVec);
	Vec getRotation(Vec MouseOld, Vec MouseNew);
};

