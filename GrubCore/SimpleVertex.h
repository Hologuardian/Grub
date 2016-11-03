#ifndef GRUB_SIMPLEVERTEX_H
#define GRUB_SIMPLEVERTEX_H

struct SimpleVertex
{
public:
	SimpleVertex(float x, float y, float z, float r, float g, float b, float a) 
	{
		SimpleVertex::x = x;
		SimpleVertex::y = y;
		SimpleVertex::z = z;
		SimpleVertex::r = r;
		SimpleVertex::g = g;
		SimpleVertex::b = b;
		SimpleVertex::a = a;
	}

	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float a;
};

#endif