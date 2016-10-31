#ifndef GRUB_IMAGE
#define GRUB_IMAGE
#include "Resource.h"

class Image : public Resource<Image>
{
	public Material material;
protected:
	Image Load(std::string file) override
	{
		;
	}
};

#endif