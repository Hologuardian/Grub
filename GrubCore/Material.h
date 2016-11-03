#ifndef GRUB_MATERIAL
#define GRUB_MATERIAL
#include "Resource.h"
#include "Texture.h"
#include "Color.h"

class Material : public Resource<Material>
{
public:
	Texture alphaTexture;
	Texture ambientTexture;
	Texture bumpTexture;
	Texture diffuseTexture;
	Texture emissiveTexture;
	Texture specularTexture;
	Color ambient;
	Color diffuse;
	Color emmisive;
	Color specular;
	float specCoeff;

	Material Load(std::string file) override
	{
		;
	}

};

#endif