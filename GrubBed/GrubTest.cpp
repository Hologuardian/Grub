#include "GrubTest.h"
#include <random>
#include "Chunk.h"
#include "GLChunkRenderer.h"
#include "FastNoise/FastNoise.h"
#include "FastNoise/FastNoise.cpp"

glm::vec3 cam;
float x = 0.0f;
float hi = 0.0f;
const float hiMax = 3.0f;
bool up = false;
const float speed = 20.0f;
const float zOffset = 0.0f;
std::random_device rd;
std::mt19937 gen(0);
std::uniform_int_distribution<> dis(1, 1000);
FastNoise noise(Clock::getCurrentTime());
const int numChunkWidth = 10;
Chunk* c[numChunkWidth][numChunkWidth];
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
Vector3 position;
Vector3 MoveDirection;

GrubTest::GrubTest(int argc, char** argv) : Grub(argc, argv)
{
	for (int i = 0; i < numChunkWidth; i++)
	{
		for (int j = 0; j < numChunkWidth; j++)
		{
			c[i][j] = nullptr;
		}
	}
	Input::ListenForKeyDown(Keyboard);
	Input::ListenForKeyUp(KeyboardUp);
	Input::ListenForMove(MouseMove);
	Input::ListenForDrag(MouseDrag);
	Input::HideCursor(true);
	Input::LockPointer = true;
}

void GrubTest::Initialize()
{
	Vector3 position = Vector3(0, 96, 0);
	window->GetCamera()->Move(position);
	for (int n = 0; n < numChunkWidth; n++)
	{
		for (int m = 0; m < numChunkWidth; m++)
		{
			c[n][m] = new Chunk(n, m, new GLChunkRenderer());
			for (int i = 0; i < ChunkWidth; i++)
			{
				for (int j = 0; j < ChunkWidth; j++)
				{
					float noiseH = (noise.GetNoise((i + ChunkWidth * n) * 1.5f, (j + ChunkWidth * m) * 1.5f) * 0.5f + 0.5f) * (float)ChunkHeight;
					for (int k = 0; k < ChunkHeight; k++)
					{
						if ((int)noiseH == k)
						{
							//float noiseC = noise.GetGradient((i + ChunkWidth * n) * 10.0f, (k)* 10.0f, (j + ChunkWidth * m) * 10.0f);
							c[n][m]->ChunkData[i][j][k] = (noiseH / (float)ChunkHeight) * 0.5f + 0.5f;
						}
						else
							c[n][m]->ChunkData[i][j][k] = -1.0f;
					}
				}
			}
			c[n][m]->Buffer(window->program);
		}
	}
	window->begin();
}

void GrubTest::Update(float Delta)
{
	float x = glm::cos(cameraAngleX);
	float z = glm::sin(cameraAngleX);
	float YA = glm::cos(cameraAngleY);
	float y = glm::sin(cameraAngleY);
	//Vector3 position = window->GetCamera()->GetPosition();
	float vX = x * YA;
	float vZ = z * YA;
	window->GetCamera()->Look(Vector3(x * YA, -y, z * YA), Vector3(0, 1.0f, 0));
	Vector3 direction = glm::normalize(window->GetCamera()->GetDirection());
	direction.y = 0;
	Vector3 forward = direction * MoveDirection.x;
	Vector3 sideways = glm::cross(direction, Vector3(0, 1, 0)) * MoveDirection.z;
	window->GetCamera()->Move((forward + sideways) * 3.0f);
	//Logger::Log(EMessageType::LOG_UPDATE, "Updating, Delta: " + std::to_string(Delta) + " FPS: " + std::to_string(1.0f/Delta));
}

void GrubTest::Keyboard(unsigned char key)
{
	switch (key)
	{
	case 'q':
		glutExit();
		break;
	case 'w':
		MoveDirection.x += 1.0f;
		break;
	case 's':
		MoveDirection.x += -1.0f;
		break;
	case 'a':
		MoveDirection.z += -1.0f;
		break;
	case 'd':
		MoveDirection.z += 1.0f;
	}
}

void GrubTest::KeyboardUp(unsigned char key)
{
	switch (key)
	{
	case 'w':
		MoveDirection.x -= 1.0f;
		break;
	case 's':
		MoveDirection.x -= -1.0f;
		break;
	case 'a':
		MoveDirection.z -= -1.0f;
		break;
	case 'd':
		MoveDirection.z -= 1.0f;
	}
}

void GrubTest::MouseMove(int x, int y)
{
	float width = glutGet(GLUT_WINDOW_WIDTH) / 2;
	float height = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	float aspect = width / height;
	cameraAngleX += (x - width) * 0.001f;
	cameraAngleY += (y - height) * 0.001f * aspect;
}

void GrubTest::MouseDrag(int x, int y)
{
	float width = glutGet(GLUT_WINDOW_WIDTH) / 2;
	float height = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	float aspect = width / height;
	cameraAngleX += (x - width) * 0.001f;
	cameraAngleY += (y - height) * 0.001f * aspect;
}

void GrubTest::Render()
{
	window->startRender();
	for (int i = 0; i < numChunkWidth; i++)
	{
		for (int j = 0; j < numChunkWidth; j++)
		{
			c[i][j]->Render(window);
		}
	}
	window->testDraw(Vector3(0), 0);
	window->endRender();
}


