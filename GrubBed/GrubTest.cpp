#include "GrubTest.h"
#include "FastNoise.cpp"

bool GrubTest::doneGen = false;

GrubTest::GrubTest(int argc, char** argv) : Grub(argc, argv)
{
	ChunkManager::Initialize();
	gen = new std::mt19937(0.0f);
	dis = new std::uniform_int_distribution<>(0, 1000);

	Input::ListenForKeyDown(Keyboard);
	Input::ListenForKeyUp(KeyboardUp);
	Input::ListenForSpecialKeyDown(SpecialKeyboard);
	Input::ListenForSpecialKeyUp(SpecialKeyboardUp);
	Input::ListenForMove(MouseMove);
	Input::ListenForDrag(MouseDrag);
	Input::HideCursor(false);
	Input::LockPointer = true;
}

void GrubTest::Initialize()
{
	Vector3 position = Vector3(240, 256, -146);
	window->GetCamera()->Move(position);
	cameraAngleX = glm::half_pi<float>();
	cameraAngleY = glm::quarter_pi<float>();
	PreGenerate();
	window->begin();
}

void GrubTest::PreGenerate()
{
	ChunkManager::SetSeed(Clock::getCurrentTime());
	int nSet = 0;
	int mSet = 0;
	int width = ((GrubTest*)instance)->numChunkWidth;
	while (mSet < width)
	{
		while (nSet < width)
		{
			for (int n = nSet; n < glm::min(nSet + largeChunk, width); n++)
			{
				for (int m = mSet; m < glm::min(mSet + largeChunk, width); m++)
				{
					if(doneGen)
						ChunkManager::RemoveChunk(n, m);
					std::vector<ChunkDecorator*>* decorators = new std::vector<ChunkDecorator*>();

					#ifdef GRUB_OPENGL
					ChunkManager::RequestChunk(n, m, new GLChunkRenderer(((GrubTest*)instance)->window->program), new TestChunkGenerator(), decorators);
				#endif
				}
			}
			nSet += largeChunk;
		}
		nSet = 0;
		mSet += largeChunk;
	}
	doneGen = true;
}

void GrubTest::Update(float Delta)
{
	/*float posX = glm::cos(x);
	float posZ = glm::sin(x);
	window->GetCamera()->Look(Vector3(50, 0, 50), Vector3(0, 1.0f, 0));
	window->GetCamera()->Move(Vector3(posX, 0, posZ));*/
	//
	float x = glm::cos(cameraAngleX);
	float z = glm::sin(cameraAngleX);
	float YA = glm::cos(cameraAngleY);
	float y = glm::sin(cameraAngleY);
	//Vector3 position = window->GetCamera()->GetPosition();
	float vX = x * YA;
	float vZ = z * YA;
	if(Input::LockPointer)
		window->GetCamera()->Look(Vector3(x * YA, -y, z * YA), Vector3(0, 1.0f, 0));
	Vector3 direction = glm::normalize(window->GetCamera()->GetDirection());
	direction.y = 0;
	Vector3 forward = direction * MoveDirection.x;
	Vector3 sideways = glm::cross(direction, Vector3(0, 1, 0)) * MoveDirection.z;
	window->GetCamera()->Move((forward + sideways) * speed * Delta);
	window->GetCamera()->Move(Vector3(0, MoveDirection.y * speed / 2 * Delta, 0));
	//Logger::Log(EMessageType::LOG_UPDATE, "Updating, Delta: " + std::to_string(Delta) + " FPS: " + std::to_string(1.0f/Delta));
}

void GrubTest::Keyboard(unsigned char key)
{
	switch (key)
	{
	case 'P':
	case 'p':
		glutExit();
		break;
	case 'W':
		((GrubTest*)instance)->speed = 150.0f;
		((GrubTest*)instance)->MoveDirection.x += 1.0f;
		break;
	case 'w':
		((GrubTest*)instance)->speed = 25.0f;
		((GrubTest*)instance)->MoveDirection.x += 1.0f;
		break;
	case 'S':
		((GrubTest*)instance)->speed = 150.0f;
		((GrubTest*)instance)->MoveDirection.x -= 1.0f;
		break;
	case 's':
		((GrubTest*)instance)->speed = 25.0f;
		((GrubTest*)instance)->MoveDirection.x -= 1.0f;
		break;
	case 'A':
		((GrubTest*)instance)->speed = 150.0f;
		((GrubTest*)instance)->MoveDirection.z -= 1.0f;
		break;
	case 'a':
		((GrubTest*)instance)->speed = 25.0f;
		((GrubTest*)instance)->MoveDirection.z -= 1.0f;
		break;
	case 'D':
		((GrubTest*)instance)->speed = 150.0f;
		((GrubTest*)instance)->MoveDirection.z += 1.0f;
		break;
	case 'd':
		((GrubTest*)instance)->speed = 25.0f;
		((GrubTest*)instance)->MoveDirection.z += 1.0f;
		break;
	case 'Q':
		((GrubTest*)instance)->speed = 150.0f;
		((GrubTest*)instance)->MoveDirection.y += 1.0f;
		break;
	case 'q':
		((GrubTest*)instance)->speed = 25.0f;
		((GrubTest*)instance)->MoveDirection.y += 1.0f;
		break;
	case 'E':
		((GrubTest*)instance)->speed = 150.0f;
		((GrubTest*)instance)->MoveDirection.y -= 1.0f;
		break;
	case 'e':
		((GrubTest*)instance)->speed = 25.0f;
		((GrubTest*)instance)->MoveDirection.y -= 1.0f;
		break;
	case 'F':
	case 'f':
		((GrubTest*)instance)->MoveDirection.x = 0.0f;
		((GrubTest*)instance)->MoveDirection.y = 0.0f;
		((GrubTest*)instance)->MoveDirection.z = 0.0f;
		break;
	case 'G':
	case 'g':
		((GrubTest*)instance)->PreGenerate();
		break;
	case 'Z':
	case 'z':
		Input::LockPointer = Input::LockPointer ? false : true;
		Input::HideCursor(Input::LockPointer);
		Input::warped = true;
		glutWarpPointer(halfScreenWidth, halfScreenHeight);
		break;
	}
}

void GrubTest::KeyboardUp(unsigned char key)
{
	switch (key)
	{
	case 'W':
	case 'w':
		((GrubTest*)instance)->MoveDirection.x -= 1.0f;
		break;
	case 'S':
	case 's':
		((GrubTest*)instance)->MoveDirection.x -= -1.0f;
		break;
	case 'A':
	case 'a':
		((GrubTest*)instance)->MoveDirection.z -= -1.0f;
		break;
	case 'D':
	case 'd':
		((GrubTest*)instance)->MoveDirection.z -= 1.0f;
		break;
	case 'Q':
	case 'q':
		((GrubTest*)instance)->MoveDirection.y += -1.0f;
		break;
	case 'E':
	case 'e':
		((GrubTest*)instance)->MoveDirection.y += 1.0f;
		break;
	}
}

void GrubTest::SpecialKeyboard(int key)
{
	switch (key)
	{
	case MAXINT:
		break;
	}
}

void GrubTest::SpecialKeyboardUp(int key)
{
	switch (key)
	{
	case MAXINT:
		break;
	}
}

void GrubTest::MouseMove(int x, int y)
{
	if (Input::LockPointer)
	{
		float width = glutGet(GLUT_WINDOW_WIDTH) / 2;
		float height = glutGet(GLUT_WINDOW_HEIGHT) / 2;
		float aspect = width / height;
		((GrubTest*)instance)->cameraAngleX += (x - width) * MouseSensitivity;
		((GrubTest*)instance)->cameraAngleY += (y - height) * MouseSensitivity * aspect;
	}
}

void GrubTest::MouseDrag(int x, int y)
{
	if (Input::LockPointer)
	{
		float width = glutGet(GLUT_WINDOW_WIDTH) / 2;
		float height = glutGet(GLUT_WINDOW_HEIGHT) / 2;
		float aspect = width / height;
		((GrubTest*)instance)->cameraAngleX += (x - width) * MouseSensitivity;
		((GrubTest*)instance)->cameraAngleY += (y - height) * MouseSensitivity * aspect;
	}
}

void GrubTest::Render()
{
	window->startRender();
	ChunkManager::DrawChunks(window);
	//window->testDraw(Vector3(0),0);
	window->endRender();
}