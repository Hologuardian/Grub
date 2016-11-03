#ifndef GRUB_CHUNK
#define GRUB_CHUN
#include "Logger.h"

#include "opengl\include\glew.h"
#include "opengl\include\glut.h"
#include "glut\include\vgl.h"
#include "LoadShaders.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"

class Chunk
{
public:
	int x;
	int z;
	GLuint buffers[3];
	GLuint vao;
	Chunk(int x, int z, GLuint program);
};

#endif