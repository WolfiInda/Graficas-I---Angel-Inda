#include "Camara.h"

Camara::Camara()
{
}

Camara::~Camara()
{
}

float* Camara::getViewMatrix(Vec Up, Vec At, Vec Eye)
{
    Vec zaxis = (At - Eye);    
    zaxis.Normalize();

    Vec xaxis = Up.CrossVectors(zaxis); 
    xaxis.Normalize();

    Vec yaxis = zaxis.CrossVectors(xaxis);     

    float* viewMatrix = new float[16]{
        xaxis.getX(), yaxis.getX(), zaxis.getX(), 0.0f,
        xaxis.getY(), yaxis.getY(), zaxis.getY(), 0.0f,
        xaxis.getZ(), yaxis.getZ(), zaxis.getZ(), 0.0f,
      -xaxis.ProductPoint(Eye), -yaxis.ProductPoint(Eye), -zaxis.ProductPoint(Eye),  1
    };

    return viewMatrix;
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