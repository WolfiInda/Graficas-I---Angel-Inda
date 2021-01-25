#pragma once
#include "Vec.h"

struct Float3
{
	float x;
	float y;
	float z;
};

struct Float2
{
	float x;
	float y;
};

struct sVertex 
{
	Float3 Pos; //Vertex
	Float2 Tex; //Textura
};

class Mesh
{
public:
	Mesh();
	~Mesh();

public:
	sVertex* getVertex() { return Vertex_; }
	int getCountVertex() { return CountVertex; }
	void setVertex(sVertex* newVertex, int newCountVertex);

	unsigned short* getIndices() { return Indices; }
	void setIndices(unsigned short* newIndices, int newCountIndices);
	float* getTransformationMatrix();

	Vec getPositionMesh() { return Position; }
	void setPositionMesh(Vec newMesh);

private:
	int CountVertex = 0, CountUVs = 0, CountIndices = 0;
	unsigned short* Indices;
	sVertex* Vertex_;
	Vec Position;
};

