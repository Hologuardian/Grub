#ifndef GRUB_MODEL_H
#define GRUB_MODEL_H
#include "Vertex.h"
#include <string>
#include "glm\glm\glm.hpp"

typedef Vertex vert;
typedef glm::mat4 matrix;

class Model
{
public:
	Model(vert vertices[])
	{
		Model::vertices = vertices;
		vertexCount = sizeof(vertices) / sizeof(vert);
	}

	vert* vertices;
	int vertexCount;
	matrix modelMatrix;

	~Model()
	{
		delete vertices;
		vertices = nullptr;
	}
};

#endif