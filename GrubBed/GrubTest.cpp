#include "GrubTest.h"
#include "FastNoise/FastNoise.cpp"

std::vector<Chunk*> GrubTest::c;
std::queue<Chunk*> GrubTest::requestedChunks;
std::queue<Chunk*> GrubTest::generatedChunks;
bool GrubTest::doneGen = false;

GrubTest::GrubTest(int argc, char** argv) : Grub(argc, argv)
{
	gen = new std::mt19937(0.0f);
	dis = new std::uniform_int_distribution<>(0, 1000);
	noise = new FastNoise((Clock::getCurrentTime()));

	Input::ListenForKeyDown(Keyboard);
	Input::ListenForKeyUp(KeyboardUp);
	Input::ListenForMove(MouseMove);
	Input::ListenForDrag(MouseDrag);
	Input::HideCursor(false);
	Input::LockPointer = true;
}

void GrubTest::Initialize()
{
	Vector3 position = Vector3(-64, 512, -64);
	window->GetCamera()->Move(position);
	PreGenerate();
	window->begin();
}

void GrubTest::PreGenerate()
{
	for each(Chunk* chunk in GrubTest::c)
	{
		delete chunk;
		chunk = nullptr;
	}
	GrubTest::c.clear();
	noise->SetSeed(Clock::getCurrentTime());
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
					GrubTest::requestedChunks.push(new Chunk(n, m, new GLChunkRenderer(((GrubTest*)instance)->window->program)));
				}
			}
			nSet += largeChunk;
		}
		nSet = 0;
		mSet += largeChunk;
	}
	generationThread = std::thread(Generate);
	generationThread.detach();
}


void GrubTest::Generate()
{
	while (true)
	{
		if (requestedChunks.size() > 0)
		{
			Chunk* toGen = requestedChunks.front();
			requestedChunks.pop();
			int m = toGen->ChunkZ;
			int n = toGen->ChunkX;
			FastNoise* noise = ((GrubTest*)instance)->noise;
			for (int i = 0; i < ChunkWidth; i++)
			{
				for (int j = 0; j < ChunkWidth; j++)
				{
					float noiseH = (noise->GetNoise((i + ChunkWidth * n) * 2.0f, (j + ChunkWidth * m) * 2.0f) * 0.5f + 0.5f) * (float)ChunkHeight * 0.25f;
					noiseH *= (noise->GetNoise((i + ChunkWidth * n) * 1.0f, (j + ChunkWidth * m) * 1.0f) * 0.5f + 0.5f);
					noiseH *= (noise->GetNoise((i + ChunkWidth * n) * 0.25f, (j + ChunkWidth * m) * 0.25f) * 0.25f + 0.75f);
					for (int k = 0; k < ChunkHeight; k++)
					{
						if (noiseH >= k - 2 && noiseH <= k)
						{
							//float noiseC = noise.GetGradient((i + ChunkWidth * n) * 10.0f, (k)* 10.0f, (j + ChunkWidth * m) * 10.0f);
							toGen->ChunkData->push_back((noiseH / (float)ChunkHeight) * 0.5f + 0.5f);
						}
						else
							toGen->ChunkData->push_back(-1.0f);
					}
				}
			}
			toGen->Initialize();
			generatedChunks.push(toGen);
		}
	}
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
	if(Input::LockPointer)
		window->GetCamera()->Look(Vector3(x * YA, -y, z * YA), Vector3(0, 1.0f, 0));
	Vector3 direction = glm::normalize(window->GetCamera()->GetDirection());
	direction.y = 0;
	Vector3 forward = direction * MoveDirection.x;
	Vector3 sideways = glm::cross(direction, Vector3(0, 1, 0)) * MoveDirection.z;
	window->GetCamera()->Move((forward + sideways) * 150.0f * Delta);
	window->GetCamera()->Move(Vector3(0, MoveDirection.y * 75.0f * Delta, 0));
	//Logger::Log(EMessageType::LOG_UPDATE, "Updating, Delta: " + std::to_string(Delta) + " FPS: " + std::to_string(1.0f/Delta));
}

void GrubTest::Keyboard(unsigned char key)
{
	switch (key)
	{
	case 'p':
		glutExit();
		break;
	case 'w':
		((GrubTest*)instance)->MoveDirection.x += 1.0f;
		break;
	case 's':
		((GrubTest*)instance)->MoveDirection.x += -1.0f;
		break;
	case 'a':
		((GrubTest*)instance)->MoveDirection.z += -1.0f;
		break;
	case 'd':
		((GrubTest*)instance)->MoveDirection.z += 1.0f;
		break;
	case 'q':
		((GrubTest*)instance)->MoveDirection.y += 1.0f;
		break;
	case 'e':
		((GrubTest*)instance)->MoveDirection.y += -1.0f;
		break;
	case 'f':
		((GrubTest*)instance)->MoveDirection.x = 0.0f;
		((GrubTest*)instance)->MoveDirection.y = 0.0f;
		((GrubTest*)instance)->MoveDirection.z = 0.0f;
		break;
	case 'g':
		((GrubTest*)instance)->PreGenerate();
		break;
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
	case 'w':
		((GrubTest*)instance)->MoveDirection.x -= 1.0f;
		break;
	case 's':
		((GrubTest*)instance)->MoveDirection.x -= -1.0f;
		break;
	case 'a':
		((GrubTest*)instance)->MoveDirection.z -= -1.0f;
		break;
	case 'd':
		((GrubTest*)instance)->MoveDirection.z -= 1.0f;
		break;
	case 'q':
		((GrubTest*)instance)->MoveDirection.y += -1.0f;
		break;
	case 'e':
		((GrubTest*)instance)->MoveDirection.y += 1.0f;
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
	if (generatedChunks.size() > 0)
	{
		Chunk* chunk = generatedChunks.front();
		chunk->Buffer();
		GrubTest::c.push_back(chunk);
		generatedChunks.pop();
	}
	window->startRender();
	for each(Chunk* chunk in GrubTest::c)
		chunk->Render(window);
	window->testDraw(Vector3(0), 0);
	window->endRender();
}