#ifndef GRUB_VERTEX_H
#define GRUB_VERTEX_H

struct Vertex
{
public:
	Vertex(float x, float y, float z, float r, float g, float b, float a) 
	{
		Vertex::x = x;
		Vertex::y = y;
		Vertex::z = z;
		Vertex::r = r;
		Vertex::g = g;
		Vertex::b = b;
		Vertex::a = a;
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