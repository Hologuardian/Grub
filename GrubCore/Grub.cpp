#include "Grub.h"
#include "LoadShaders.h"

const GLuint NumVertices = 12;

Grub::Grub()
{
	window = new OpenGLWindow();
}

Grub::~Grub()
{
	delete window;
	window = nullptr;
}


//Static Singleton Heartbeat Methods
Grub* Grub::instance = nullptr;

double lastTime = 0;
double currentTime = 0;
void Grub::Update()
{
	Logger::Log(Logger::EMessageType::INFO, "Update Start");
	lastTime = currentTime;
	currentTime = Clock::getCurrentTime();
	instance->Update(currentTime- lastTime);
	Logger::Log(Logger::EMessageType::INFO, "Update End");
	glutPostRedisplay();
}

void Grub::Display()
{
	Logger::Log(Logger::EMessageType::INFO, "Render Start");
	instance->Render();

	Logger::Log(Logger::EMessageType::INFO, "Render End");
}