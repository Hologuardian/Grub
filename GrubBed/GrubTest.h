#ifndef GRUB_GRUB_TEST_H
#define GRUB_GRUB_TEST_H
#include "Grub.h"
#include <random>
#include "GLChunkRenderer.h"
#include "FastNoise.h"
#include <thread>  
#include <queue>
#include "ChunkManager.h"
#include <ft2build.h>
#include "TestChunkGenerator.h"
#include "TreeDecorator.h"
#include FT_FREETYPE_H  


class GrubTest : public Grub
{
public:
	glm::vec3 cam;
	float x = 0.0f;
	float hi = 0.0f;
	const float hiMax = 3.0f;
	bool up = false;
	const float speed = 20.0f;
	const float zOffset = 0.0f;
	std::random_device rd;
	std::mt19937* gen;
	std::uniform_int_distribution<>* dis;
	const int numChunkWidth = 60;
	const int largeChunk = 5;
	static bool doneGen;
	float cameraAngleX = 0.0f;
	float cameraAngleY = 0.0f;
	Vector3 position;
	Vector3 MoveDirection;
	std::thread generationThread;
public:
	GrubTest(int argc, char** argv);
	void Update(float Delta);
	void Render();
	void Initialize();
	static void Keyboard(unsigned char key);
	static void KeyboardUp(unsigned char key);
	static void SpecialKeyboard(int key);
	static void SpecialKeyboardUp(int key);
	static void MouseMove(int x, int y);
	static void MouseDrag(int x, int y);
	void PreGenerate();
};

#endif