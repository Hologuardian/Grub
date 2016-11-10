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
const int numChunkWidth = 5;
Chunk* c[numChunkWidth][numChunkWidth];

GrubTest::GrubTest()
{
	
	for (int i = 0; i < numChunkWidth; i++)
	{
		for (int j = 0; j < numChunkWidth; j++)
		{
			c[i][j] = nullptr;
		}
	}
}

void GrubTest::Initialize()
{
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
						if ((int)noiseH - 1 == k || (int)noiseH == k || (int)noiseH + 1 == k)
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

float time = 0.0f;
void GrubTest::Update(float Delta)
{
	time += Delta * 0.25f;
	float center = numChunkWidth * (ChunkWidth / 2);
	float radius = numChunkWidth * (ChunkWidth / 2) * 1.2f;
	float x = glm::cos(time) * radius + center;
	float z = glm::sin(time) * radius + center;
	window->GetCamera()->SetPosition(Vector3(x, 96, z));
	window->GetCamera()->Look(Vector3(center, 0, center), Vector3(0, 1.0f, 0));
	//Logger::Log(EMessageType::LOG_UPDATE, "Updating, Delta: " + std::to_string(Delta) + " FPS: " + std::to_string(1.0f/Delta));
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


