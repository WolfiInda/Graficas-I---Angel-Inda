#include "Camara.h"

Camara::Camara()
{

}

Camara::Camara(Vec newEye, Vec newLookAt, Vec newUp, float newFOV, float newNear, float newFar, float newViewWidth, float newViewHeight, bool newPerspective)
{
    Perspective = newPerspective;

    Up = newUp;
    LookAt = newLookAt;
    Eye = newEye;

    FOV = newFOV;
    Near = newNear;
    Far = newFar;
    ViewWidth = newViewWidth;
    ViewHeight = newViewHeight;

    setZaxis();
    setXaxis();
    setYaxis();
}


Camara::Camara(Vec newEye, Vec newLookAt, Vec newUp)
{
    Up = newUp;
    LookAt = newLookAt;
    Eye = newEye;

    setZaxis();
    setXaxis();
    setYaxis();
}

Camara::~Camara()
{
}

void Camara::setZaxis()
{
    //Front
    zaxis = (LookAt - Eye);
    zaxis.Normalize();
}

void Camara::setXaxis()
{
    //Right - Up Cross Front
    xaxis = Up.CrossVectors(zaxis);
    xaxis.Normalize();
}

void Camara::setYaxis()
{
    //Up - Front cross Right
    yaxis = zaxis.CrossVectors(xaxis);
}

void Camara::CamaraMove(Vec newVec)
{
    Eye += xaxis * newVec.getX();
    Eye += yaxis * newVec.getY();
    Eye += zaxis * newVec.getZ();

    LookAt += xaxis * newVec.getX();
    LookAt += yaxis * newVec.getY();
    LookAt += zaxis * newVec.getZ();
}

float* Camara::getViewMatrix(Vec Up, Vec At, Vec Eye)
{
    /*
    //Up
    zaxis = (At - Eye);    
    zaxis.Normalize();

    //Right
    xaxis = Up.CrossVectors(zaxis); 
    xaxis.Normalize();

    //Front
    yaxis = zaxis.CrossVectors(xaxis);     
    */

    float* viewMatrix = new float[16]{
        xaxis.getX(), yaxis.getX(), zaxis.getX(), 0.0f,
        xaxis.getY(), yaxis.getY(), zaxis.getY(), 0.0f,
        xaxis.getZ(), yaxis.getZ(), zaxis.getZ(), 0.0f,
      -xaxis.ProductPoint(Eye), -yaxis.ProductPoint(Eye), -zaxis.ProductPoint(Eye),  1
    };

    return viewMatrix;
}

float* Camara::getViewMatrix()
{
    float* viewMatrix = new float[16]{
        xaxis.getX(), yaxis.getX(), zaxis.getX(), 0.0f,
        xaxis.getY(), yaxis.getY(), zaxis.getY(), 0.0f,
        xaxis.getZ(), yaxis.getZ(), zaxis.getZ(), 0.0f,
      -xaxis.ProductPoint(Eye), -yaxis.ProductPoint(Eye), -zaxis.ProductPoint(Eye),  1
    };

    return viewMatrix;
}

float* Camara::getProyection()
{
    if (Perspective == true)
    {
        return getPerspectiveMatrix(FOV, ViewWidth / ViewHeight, Near, Far);
    }
    else
    {
        return getOrthographicMatrix(ViewWidth, ViewHeight, Near, Far);
    }
}

float* Camara::getPerspectiveMatrix(float FOV, float AspectRatio, float Near, float Far)
{
    float Height = cos(FOV * .5) / sin(FOV * .5);
    float Width = Height / AspectRatio;

    return  new float[16]{
        Width, 0.0f, 0.0f, 0.0f,
        0.0f, Height, 0.0f, 0.0f,
        0.0f, 0.0f, Far / (Far - Near), 1.0f,
        0.0f, 0.0f, (-Far / (Far - Near)) * Near, 0.0f
    };
}

float* Camara::getOrthographicMatrix(float ViewWidth, float ViewHeight, float Near, float Far)
{ 
    return new float[16]{
        (2.0f / ViewWidth), 0.0f, 0.0f, 0.0f,
        0.0f, (2.0f / ViewHeight), 0.0f, 0.0f,
        0.0f, 0.0f, (1.0f / (Far - Near)), 0.0f,
        0.0f, 0.0f, (-(1.0f / (Far - Near))) * Near, 1.0f 
    };
}

Vec Camara::setMouseRotate(Vec MouseVec)
{
    return Vec(MouseVec.getX(), MouseVec.getY(), 0);
}

Vec Camara::getRotation(Vec MouseOld, Vec MouseNew)
{
    MouseNew -= MouseOld;
    MouseNew /= 100;
    LookAt += MouseNew;

    setZaxis();
    setXaxis();
    setYaxis(); 

    return LookAt;
}
