#include "Chunk.h"

Chunk::Chunk(int x, int z, ChunkRenderer* renderer)
{
	ChunkData = new std::vector<float>();
	ChunkX = x;
	ChunkZ = z;
	chunkRender = renderer;
}

Chunk Chunk::Load(std::string File)
{
	return Chunk(0,0, nullptr);
}

void Chunk::Render(AbstractWindow* window)
{
	chunkRender->Render(window);
}

void Chunk::Initialize()
{
	pos = new std::vector<Vector3>(); // Positions
	colors = new std::vector<Vector3>();
	for (int i = 0; i < ChunkWidth; i++)
	{
		for (int j = 0; j < ChunkWidth; j++)
		{
			for (int k = 0; k < ChunkHeight; k++)
			{
				float c = ChunkData->at(i * ChunkWidth * ChunkHeight + j * ChunkHeight + k);
				//Logger::Log(EMessageType::LOG_INFO, "" + std::to_string(c));
				if (c > 0)
				{
					float ChunkPosX = ChunkX * ChunkWidth * BlockWidth * 2.0f;
					float ChunkPosZ = ChunkZ * ChunkWidth * BlockWidth * 2.0f;
					float xOffset = i * BlockWidth * 2.0f;
					float yOffset = k * BlockHeight * 2.0f;
					float zOffset = j * BlockWidth * 2.0f;
					pos->push_back(Vector3((xOffset + ChunkPosX) + BlockWidth, yOffset + BlockHeight, (zOffset + ChunkPosZ) - BlockWidth)); //0
					pos->push_back(Vector3((xOffset + ChunkPosX) + BlockWidth, yOffset + BlockHeight, (zOffset + ChunkPosZ) + BlockWidth)); //1
					pos->push_back(Vector3((xOffset + ChunkPosX) - BlockWidth, yOffset + BlockHeight, (zOffset + ChunkPosZ) + BlockWidth)); //2
					pos->push_back(Vector3((xOffset + ChunkPosX) - BlockWidth, yOffset + BlockHeight, (zOffset + ChunkPosZ) - BlockWidth)); //3
					//pos->push_back(Vector3((xOffset + ChunkPosX) + BlockWidth, yOffset - BlockHeight, (zOffset +ChunkPosZ) - BlockWidth)); //4
					//pos->push_back(Vector3((xOffset + ChunkPosX) + BlockWidth, yOffset - BlockHeight, (zOffset +ChunkPosZ) + BlockWidth)); //5
					//pos->push_back(Vector3((xOffset + ChunkPosX) - BlockWidth, yOffset - BlockHeight, (zOffset +ChunkPosZ) + BlockWidth)); //6
					//pos->push_back(Vector3((xOffset + ChunkPosX) - BlockWidth, yOffset - BlockHeight, (zOffset +ChunkPosZ) - BlockWidth)); //7
					pos->push_back(Vector3((xOffset + ChunkPosX) + BlockWidth, yOffset - BlockHeight, (zOffset + ChunkPosZ) + BlockWidth)); //8
					pos->push_back(Vector3((xOffset + ChunkPosX) + BlockWidth, yOffset + BlockHeight, (zOffset + ChunkPosZ) + BlockWidth)); //9
					pos->push_back(Vector3((xOffset + ChunkPosX) + BlockWidth, yOffset + BlockHeight, (zOffset + ChunkPosZ) - BlockWidth)); //10
					pos->push_back(Vector3((xOffset + ChunkPosX) + BlockWidth, yOffset - BlockHeight, (zOffset + ChunkPosZ) - BlockWidth)); //11
					pos->push_back(Vector3((xOffset + ChunkPosX) - BlockWidth, yOffset - BlockHeight, (zOffset + ChunkPosZ) + BlockWidth)); //12
					pos->push_back(Vector3((xOffset + ChunkPosX) - BlockWidth, yOffset + BlockHeight, (zOffset + ChunkPosZ) + BlockWidth)); //13
					pos->push_back(Vector3((xOffset + ChunkPosX) - BlockWidth, yOffset + BlockHeight, (zOffset + ChunkPosZ) - BlockWidth)); //14
					pos->push_back(Vector3((xOffset + ChunkPosX) - BlockWidth, yOffset - BlockHeight, (zOffset + ChunkPosZ) - BlockWidth)); //15
					pos->push_back(Vector3((xOffset + ChunkPosX) - BlockWidth, yOffset + BlockHeight, (zOffset + ChunkPosZ) + BlockWidth)); //16
					pos->push_back(Vector3((xOffset + ChunkPosX) + BlockWidth, yOffset + BlockHeight, (zOffset + ChunkPosZ) + BlockWidth)); //17
					pos->push_back(Vector3((xOffset + ChunkPosX) + BlockWidth, yOffset - BlockHeight, (zOffset + ChunkPosZ) + BlockWidth)); //18
					pos->push_back(Vector3((xOffset + ChunkPosX) - BlockWidth, yOffset - BlockHeight, (zOffset + ChunkPosZ) + BlockWidth)); //19
					pos->push_back(Vector3((xOffset + ChunkPosX) - BlockWidth, yOffset + BlockHeight, (zOffset + ChunkPosZ) - BlockWidth)); //20
					pos->push_back(Vector3((xOffset + ChunkPosX) + BlockWidth, yOffset + BlockHeight, (zOffset + ChunkPosZ) - BlockWidth)); //21
					pos->push_back(Vector3((xOffset + ChunkPosX) + BlockWidth, yOffset - BlockHeight, (zOffset + ChunkPosZ) - BlockWidth)); //22
					pos->push_back(Vector3((xOffset + ChunkPosX) - BlockWidth, yOffset - BlockHeight, (zOffset + ChunkPosZ) - BlockWidth)); //23
					for (int n = 0; n < 20; n++)
					{
						colors->push_back(Vector3(0, 0.8f - c * 0.8f, 0));
					}
				}
			}
		}
	}
}

void Chunk::Buffer()
{
	
	chunkRender->RegisterQuads(pos, colors);
	delete pos;
	pos = nullptr;
	delete colors;
	colors = nullptr;
}

Chunk::~Chunk()
{
	delete ChunkData;
	ChunkData = nullptr;
	delete chunkRender;
	chunkRender = nullptr;
}
