#include "Grub.h"

const GLuint NumVertices = 12;

Grub::Grub(int argc, char** argv)
{
	window = new OpenGLWindow();
	window->MakeWindow(argc, argv);
	window->SetUpdate(Grub::Update);
	window->SetDisplay(Grub::Display);
	window->SetInput(Input::KeyboardDownFunc, Input::KeyboardUpFunc, Input::ClickFunc, Input::MoveFunc, Input::DragFunc);
	Input::LockPointer = false;
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
	if (lastTime == 0)
		lastTime = currentTime;
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