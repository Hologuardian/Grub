#include "GrubTest.h"
#include <random>

void GrubTest::Update(float Delta)
{
	Logger::Log(EMessageType::LOG_UPDATE, "Updating, Delta: " + std::to_string(Delta) + " FPS: " + std::to_string(1.0f/Delta));
}

void GrubTest::Render()
{
	std::random_device rd;
	std::mt19937 gen(0);
	window->startRender();
	for (int i = -8; i <= 8; i++)
	{
		std::string str = "";
		for (int j = -8; j <= 8; j++)
		{
			int col = 0;// glm::abs((i + (j % 2))) % 2;
			std::uniform_int_distribution<> dis(1, 10);
			int h = dis(gen);
			//str += ":" + std::to_string(i) + "" + std::to_string(j) + "" + std::to_string(col) + "";
			window->testDraw(glm::vec3(i * 0.2f, h / 100.0f, j * 0.2f), col);
		}
		//Logger::Log(EMessageType::LOG_WARNING, str);
	}
	//window->testDraw(glm::vec3(0,0,0), 0);
	window->endRender();
}
