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
	Logger::Log(EMessageType::LOG_UPDATE, "Update Start");
	lastTime = currentTime;
	currentTime = Clock::getCurrentTime();
	instance->Update(currentTime- lastTime);
	Logger::Log(EMessageType::LOG_UPDATE, "Update End");
	glutPostRedisplay();
}

void Grub::Display()
{
	Logger::Log(EMessageType::LOG_UPDATE, "Render Start");
	instance->Render();

	Logger::Log(EMessageType::LOG_UPDATE, "Render End");
}