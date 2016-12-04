#include "GLChunkRenderer.h"

GLChunkRenderer::GLChunkRenderer(const Grubuint const program)
{
	glGenVertexArrays(1, &ChunkVAO);
	glBindVertexArray(ChunkVAO);

	glGenBuffers(BufferCount, &ChunkBuffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, ChunkBuffers[0]);
	glBindAttribLocation(program, 0, "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, ChunkBuffers[1]);
	glBindAttribLocation(program, 1, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void GLChunkRenderer::Render(Window* window)
{
	window->renderPrimitive(prim, ChunkVAO, 0, length);
}

void GLChunkRenderer::RegisterPrimitives(const std::vector<Vector3>* const Points, const std::vector<Vector3>* const Colors, Primitive p)
{
	if (Points->size() == 0 || Colors->size() == 0)
		return;
	prim = p;
	glBindVertexArray(ChunkVAO);
	glBindBuffer(GL_ARRAY_BUFFER, ChunkBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, Points->size() * sizeof(Vector3), &Points->at(0), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, ChunkBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, Colors->size() * sizeof(Vector3), &Colors->at(0), GL_STATIC_DRAW);
	length = glm::min(Points->size(), Colors->size());
	glBindVertexArray(0);
}

GLChunkRenderer::~GLChunkRenderer()
{
	glBindVertexArray(ChunkVAO);
	glDeleteBuffers(BufferCount, &ChunkBuffers[0]);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &ChunkVAO);
}
