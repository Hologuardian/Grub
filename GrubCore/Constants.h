#ifndef GRUB_CONSTANTS
#define GRUB_CONSTANTS
#include "opengl\include\glew.h"
#include "glm\glm\glm.hpp"
#include "SimpleVertex.h"

//#define GRUB_USEOPENGL
#define GRUB_DX11
//#define GRUB_DX12

typedef SimpleVertex Vert; 
#ifdef GRUB_USEOPENGL
#pragma comment(lib, "glew32.lib")
typedef glm::mat4 Matrix;
typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef GLuint Grubuint;
#else 
#ifdef GRUB_DX11
typedef glm::mat4 Matrix;
typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef GLuint Grubuint;
#else
#ifdef GRUB_DX12
typedef glm::mat4 Matrix;
typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef GLuint Grubuint;
#else
typedef glm::mat4 Matrix;
typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef GLuint Grubuint;
#endif
#endif
#endif

const bool FullScreen = true;

const float screenWidth = 1920;
const float screenHeight = 1080;
const float halfScreenWidth = screenWidth / 2;
const float halfScreenHeight = screenHeight / 2;

const float MouseSensitivity = 0.001f;

const int ThreadPoolSize = 3;

const int ChunkWidth = 7;
const int ChunkHeight = 255;
const float BlockWidth = 1.0f;
const float BlockHeight = 1.0f;
const int ChunkSize = (ChunkWidth+1) * (ChunkWidth+1) * (ChunkHeight+1);
const int BufferCount = 2;

static unsigned int parseFloatColor(float r, float g, float b, float a)
{
	unsigned int color = 0;
	color += ((unsigned int)(r * 255.0f) % 255) << 24;
	color += ((unsigned int)(g * 255.0f) % 255) << 16;
	color += ((unsigned int)(b * 255.0f) % 255) << 8;
	color += ((unsigned int)(a * 255.0f) % 255);
}

static unsigned int parseFloatColor(Vector4 color)
{
//	unsigned int color = 0;
	//color += ((unsigned int)(color.r * 255.0f) % 255) << 24;
	//color += ((unsigned int)(color.g * 255.0f) % 255) << 16;
	//color += ((unsigned int)(color.b * 255.0f) % 255) << 8;
	//color += ((unsigned int)(color.a * 255.0f) % 255);
}

static Vector4 parseIntColor(unsigned int color)
{
	return Vector4(
		((color << 24) & 255) / 255.0f, 
		((color << 16) & 255) / 255.0f, 
		((color << 8) & 255) / 255.0f, 
		(color & 255) / 255.0f);
}
#endif