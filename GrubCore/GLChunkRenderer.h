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
	//Vertex Array Object that holds all of the buffers for easy access to 
	GLuint ChunkVAO;
	GLuint ChunkBuffers[BufferCount];
	int length;
	/**
	Requires a uint pointer to a shader program to be constructed.
	*/
	GLChunkRenderer(const Grubuint const program);
	/**
	Draws the chunk to the specified window.
	*/
	void Render(Window* window);
	/**
	Registers all of the data required sent from the chunk file, this is put into the buffer to be drawn.
	*/
	void RegisterPrimitives(const std::vector<Vector3>* const Points, const std::vector<Vector3>* const Colors, Primitive p);
	/**
	Destroys the object
	*/
	virtual ~GLChunkRenderer();
};

#endif