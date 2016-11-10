#ifndef GRUB_GLCHUNKRENDERER
#define GRUB_GLCHUNKRENDERER
#include "ChunkRenderer.h"

#include "Logger.h"
#include <string>

#include "opengl\include\glew.h"
#include "opengl\include\glut.h"
#include "glut\include\vgl.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"

class GLChunkRenderer : public ChunkRenderer
{
public:
	GLuint ChunkVAO;
	GLuint ChunkBuffers[BufferCount];
	GLChunkRenderer();
	void Render(AbstractWindow* window);
	void RegisterQuads(Vector3 Points[], Vector3 Colors[], Grubuint program);
};

#endif