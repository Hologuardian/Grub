#ifndef GRUB_TEXTURE
#define GRUB_TEXTURE
#include "Resource.h"
#include "TextureVertex.h"

class Texture : public Resource<Texture>
{
public:
	std::vector<TextureVertex> data;
	Texture Load(std::string file) override
	{
		;
	}
};

#endif