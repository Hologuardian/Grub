#ifndef GRUB_COLOR	
#define GRUB_COLOR

struct Color
{
public:
	Color(float r, float g, float b, float a)
	{
		Color::r = r;
		Color::g = g;
		Color::b = b;
		Color::a = a;
	}
	float r;
	float g;
	float b;
	float a;

	/*operator float*()
	{
		float* arr = new float[4]{ r, g, b, a };
		return arr;
	}*/
};

#endif