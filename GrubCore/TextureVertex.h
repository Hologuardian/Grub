#ifndef GRUB_TEXTUREVERTEX_H
#define GRUB_TEXTUREVERTEX_H

struct TextureVertex
{
public:
	TextureVertex(float x, float y, float z, float u, float v)
	{
		TextureVertex::x = x;
		TextureVertex::y = y;
		TextureVertex::z = z;
		TextureVertex::u = u;
		TextureVertex::v = v;
	}

	float x;
	float y;
	float z;
	float u;
	float v;
};

#endif