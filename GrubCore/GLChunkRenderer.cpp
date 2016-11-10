#include "GLChunkRenderer.h"

GLChunkRenderer::GLChunkRenderer()
{
}

void GLChunkRenderer::Render(AbstractWindow* window)
{
	window->renderPrimitive(AbstractWindow::PrimativeType::QUAD, ChunkVAO, 0, ChunkSize * 24);
}

void GLChunkRenderer::RegisterQuads(Vector3 Points[], Vector3 Colors[], GLuint program)
{
	/*for (int i = 0; i < ChunkSize * 24; i++)
	{
		Logger::Log(EMessageType::LOG_INFO, "Updating, What: " + std::to_string(Points[i][0]) + " The: " + std::to_string(Points[i][1]) + " Fuck: " + std::to_string(Points[i][2]));
	}*/
	GLuint tempVAO = 0;

	glGenVertexArrays(1, &tempVAO);
	glBindVertexArray(tempVAO);

	glGenBuffers(BufferCount, &ChunkBuffers[0]);

	glBindBuffer(GL_ARRAY_BUFFER, ChunkBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, ChunkSize * 24 * sizeof(Vector3), &Points[0], GL_STATIC_DRAW);
	glBindAttribLocation(program, 0, "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, ChunkBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, ChunkSize * 24 * sizeof(Vector3), &Colors[0], GL_STATIC_DRAW);
	glBindAttribLocation(program, 1, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	delete Points;
	delete Colors;
	ChunkVAO = tempVAO;
}
