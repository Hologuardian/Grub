#ifndef GRUB_CONSTANTS
#define GRUB_CONSTANTS
#include "opengl\include\glew.h"
#include "glm\glm\glm.hpp"
#include "SimpleVertex.h"


typedef SimpleVertex Vert;
typedef glm::mat4 Matrix;
typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef GLuint Grubuint;

const int ChunkWidth = 32;
const int ChunkHeight = 96;
const int ChunkSize = ChunkWidth * ChunkWidth * ChunkHeight;
const int BufferCount = 2;

#endif