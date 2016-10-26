#include "GrubTest.h"

void GrubTest::Update(float Delta)
{
	Logger::Log(Logger::EMessageType::INFO, "Updating, Delta: " + std::to_string(Delta) + " FPS: " + std::to_string(1.0f/Delta));
}

void GrubTest::Render()
{
	window->startRender();
	for (int i = -10; i <= 10; i++)
	{
		for (int j = -10; j <= 10; j++)
		{
			window->testDraw(glm::vec3(i * 0.1f, j * 0.025f, j * 0.1f), glm::abs(i + (j % 2)) % 2);
		}
	}
	window->endRender();
}
