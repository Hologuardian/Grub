#include "Chunk.h"

Chunk::Chunk(int x, int z, GLuint program)
{
	Chunk::x = x;
	Chunk::z = z;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(3, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 1024, NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 1024, NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 1024, NULL, GL_STATIC_DRAW);

	glVertexAttribPointer(buffers[0], 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(buffers[1], 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(buffers[2], 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	
	glEnableVertexAttribArray(buffers[0]);
	glEnableVertexAttribArray(buffers[1]);
	glEnableVertexAttribArray(buffers[2]);

	glBindAttribLocation(program, buffers[0], "vPosition");
	glBindAttribLocation(program, buffers[1], "vertexColor");
	glBindAttribLocation(program, buffers[2], "vTexture");
}
