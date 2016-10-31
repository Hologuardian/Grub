#include "GrubTest.h"
#include <random>

glm::vec3 cam;
float x = 0.0f;
float hi = 0.0f;
bool up = false;
const int width = 70;
const int length = 40;
const float speed = 20.0f;
const float zOffset = -2.5f;
float heights[width][length];
std::random_device rd;
std::mt19937 gen(0);
std::uniform_int_distribution<> dis(1, 10);

GrubTest::GrubTest()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			int h = dis(gen);
			heights[i][j] =  h / 100.0f;
		}
	}
}

int n = 0;
void GrubTest::Update(float Delta)
{
	x += speed * Delta;
	Logger::Log(EMessageType::LOG_UPDATE, "Updating, Delta: " + std::to_string(Delta) + " FPS: " + std::to_string(1.0f/Delta));
	while (x > 1.0f)
	{
		n++;
		if (up)
		{
			hi += 0.01f;
			if (hi >= 1.0f)
			{
				up = false;
			}
		}
		else
		{
			hi -= 0.01f;
			if (hi <= 0.2f)
			{
				up = true;
			}
		}
		x -= 1.0f;
		for (int j = length - 1; j > 0; j--)
		{
			for (int i = 0; i < width; i++)
			{
				heights[i][j] = heights[i][j - 1];
			}
		}
		for (int i = 0; i < width; i++)
		{
			int h = dis(gen);
			float y = glm::cos(n * 0.1f) * 10.0f;
			float y2 = glm::cos(n * 0.1f + glm::two_pi<float>()/3.05f) * 10.0f;
			float delta = glm::sin(((y + y2) + i) * 0.06f);
			heights[i][0] = (h / 100.0f) + hi * delta;
		}
	}
}

void GrubTest::Render()
{
	window->startRender();
	for (int i = 0; i < width; i++)
	{
		std::string str = "";
		for (int j = 0; j < length; j++)
		{
			int col = 0;// glm::abs((i + (j % 2))) % 2;
			cam = glm::vec3(0, 2.0f, 5.0f);// +x * 0.1f);
			//str += ":" + std::to_string(i) + "" + std::to_string(j) + "" + std::to_string(col) + "";
			window->testDraw(glm::vec3(i * 0.2f - ((float)width) / 10.0f - 0.1f, heights[i][j], j * 0.2f + zOffset), col, cam);
		}
		//Logger::Log(EMessageType::LOG_WARNING, str);
	}
	//window->testDraw(glm::vec3(0,0,0), 0);
	window->endRender();
}
