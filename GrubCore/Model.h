#ifndef GRUB_MODEL_H
#define GRUB_MODEL_H
#include "SimpleVertex.h"
#include "Resource.h"
#include <string>
#include "Material.h"
#include "Constants.h"

class Model : public Resource<Model>
{
public:
	Matrix modelMatrix;
	Material* material;

	Model Load(std::string File) override
	{
		material->Load("");
	}

	~Model()
	{
		delete material;
		material = nullptr;
	}
};

#endif