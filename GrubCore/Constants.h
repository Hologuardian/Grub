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

const float screenWidth = 1520;
const float screenHeight = 790;
const float halfScreenWidth = screenWidth / 2;
const float halfScreenHeight = screenHeight / 2;

const float MouseSensitivity = 0.001f;

const int ChunkWidth = 16;
const int ChunkHeight = 128;
const float BlockWidth = 1.0f;
const float BlockHeight = 1.0f;
const int ChunkSize = ChunkWidth * ChunkWidth * ChunkHeight;
const int BufferCount = 2;

#endif