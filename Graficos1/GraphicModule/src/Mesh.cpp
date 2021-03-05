#include "Mesh.h"

Mesh::Mesh()
{
    

}

Mesh::~Mesh()
{
}

void Mesh::setVertex(sVertex* newVertex, int newCountVertex)
{
    Vertex_ = new sVertex[newCountVertex];
    CountVertex = newCountVertex;
    memcpy(Vertex_, newVertex, newCountVertex * sizeof(sVertex));
}

void Mesh::setIndices(unsigned short* newIndices, int newCountIndices)
{
    Indices = new unsigned short[newCountIndices];
    CountIndices = newCountIndices;
    memcpy(Indices, newIndices, newCountIndices * sizeof(unsigned short));
}

float* Mesh::getTransformationMatrix()
{
    return new float[16]{
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 2.0f, 1.0f
    };
}

void Mesh::setPositionMesh(Vec newPosition)
{
    Position = newPosition;
}
