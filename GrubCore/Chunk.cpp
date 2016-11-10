#include "Chunk.h"

Chunk::Chunk(int x, int z, ChunkRenderer* renderer)
{
	ChunkData = new float**[ChunkWidth];
	for (int i = 0; i < ChunkWidth; i++)
	{
		ChunkData[i] = new float*[ChunkHeight];
		for (int j = 0; j < ChunkWidth; j++)
		{
			ChunkData[i][j] = new float[ChunkHeight];
		}
	}
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

void Chunk::Buffer(Grubuint program)
{
	int test = 0;
	int m = 0;
	Vector3* positions = new Vector3[ChunkSize * 24];
	Vector3* colors = new Vector3[ChunkSize * 24];
	for (int i = 0; i < ChunkWidth; i++)
	{
		for (int j = 0; j < ChunkWidth; j++)
		{
			for (int k = 0; k < ChunkHeight; k++)
			{
				int x = i * (ChunkWidth * ChunkHeight) * 24;
				int z = j * ChunkHeight * 24;
				int y = k * 24;
				float c = ChunkData[i][j][k]; 
				//Logger::Log(EMessageType::LOG_INFO, "" + std::to_string(c));
				if (c > 0)
				{
					positions[x + y + z + 0] = Vector3((i + ChunkX * ChunkWidth) + 0.5, k + 0.5, (j +ChunkZ * ChunkWidth) - 0.5); //0
					positions[x + y + z + 1] = Vector3((i + ChunkX * ChunkWidth) + 0.5, k + 0.5, (j +ChunkZ * ChunkWidth) + 0.5); //1
					positions[x + y + z + 2] = Vector3((i + ChunkX * ChunkWidth) - 0.5, k + 0.5, (j +ChunkZ * ChunkWidth) + 0.5); //2
					positions[x + y + z + 3] = Vector3((i + ChunkX * ChunkWidth) - 0.5, k + 0.5, (j +ChunkZ * ChunkWidth) - 0.5); //3
					positions[x + y + z + 4] = Vector3((i + ChunkX * ChunkWidth) + 0.5, k - 0.5, (j +ChunkZ * ChunkWidth) - 0.5); //4
					positions[x + y + z + 5] = Vector3((i + ChunkX * ChunkWidth) + 0.5, k - 0.5, (j +ChunkZ * ChunkWidth) + 0.5); //5
					positions[x + y + z + 6] = Vector3((i + ChunkX * ChunkWidth) - 0.5, k - 0.5, (j +ChunkZ * ChunkWidth) + 0.5); //6
					positions[x + y + z + 7] = Vector3((i + ChunkX * ChunkWidth) - 0.5, k - 0.5, (j +ChunkZ * ChunkWidth) - 0.5); //7
					positions[x + y + z + 8] = Vector3((i + ChunkX * ChunkWidth) + 0.5, k - 0.5, (j +ChunkZ * ChunkWidth) + 0.5); //8
					positions[x + y + z + 9] = Vector3((i + ChunkX * ChunkWidth) + 0.5, k + 0.5, (j +ChunkZ * ChunkWidth) + 0.5); //9
					positions[x + y + z + 10] = Vector3((i + ChunkX * ChunkWidth) + 0.5, k + 0.5, (j +ChunkZ * ChunkWidth) - 0.5); //10
					positions[x + y + z + 11] = Vector3((i + ChunkX * ChunkWidth) + 0.5, k - 0.5, (j +ChunkZ * ChunkWidth) - 0.5); //11
					positions[x + y + z + 12] = Vector3((i + ChunkX * ChunkWidth) - 0.5, k - 0.5, (j +ChunkZ * ChunkWidth) + 0.5); //12
					positions[x + y + z + 13] = Vector3((i + ChunkX * ChunkWidth) - 0.5, k + 0.5, (j +ChunkZ * ChunkWidth) + 0.5); //13
					positions[x + y + z + 14] = Vector3((i + ChunkX * ChunkWidth) - 0.5, k + 0.5, (j +ChunkZ * ChunkWidth) - 0.5); //14
					positions[x + y + z + 15] = Vector3((i + ChunkX * ChunkWidth) - 0.5, k - 0.5, (j +ChunkZ * ChunkWidth) - 0.5); //15
					positions[x + y + z + 16] = Vector3((i + ChunkX * ChunkWidth) - 0.5, k + 0.5, (j +ChunkZ * ChunkWidth) + 0.5); //16
					positions[x + y + z + 17] = Vector3((i + ChunkX * ChunkWidth) + 0.5, k + 0.5, (j +ChunkZ * ChunkWidth) + 0.5); //17
					positions[x + y + z + 18] = Vector3((i + ChunkX * ChunkWidth) + 0.5, k - 0.5, (j +ChunkZ * ChunkWidth) + 0.5); //18
					positions[x + y + z + 19] = Vector3((i + ChunkX * ChunkWidth) - 0.5, k - 0.5, (j +ChunkZ * ChunkWidth) + 0.5); //19
					positions[x + y + z + 20] = Vector3((i + ChunkX * ChunkWidth) - 0.5, k + 0.5, (j +ChunkZ * ChunkWidth) - 0.5); //20
					positions[x + y + z + 21] = Vector3((i + ChunkX * ChunkWidth) + 0.5, k + 0.5, (j +ChunkZ * ChunkWidth) - 0.5); //21
					positions[x + y + z + 22] = Vector3((i + ChunkX * ChunkWidth) + 0.5, k - 0.5, (j +ChunkZ * ChunkWidth) - 0.5); //22
					positions[x + y + z + 23] = Vector3((i + ChunkX * ChunkWidth) - 0.5, k - 0.5, (j +ChunkZ * ChunkWidth) - 0.5); //23
					for (int n = 0; n < 24; n++)
					{
						//Logger::Log(EMessageType::LOG_INFO, "" + std::to_string(positions[x + y + z + n][0]) + "," + std::to_string(positions[x + y + z + n][1]) + "," + std::to_string(positions[x + y + z + n][2]) + "," + std::to_string(m));
						m++;
						colors[x + y + z + n] = Vector3(0, 0.8f - c * 0.6f, 0);
					}
				}
			}
		}
	}
	/*Logger::Log(EMessageType::LOG_INFO, "---------------------------------");
	for (int i = 0; i < ChunkSize * 24; i++)
	{
		Logger::Log(EMessageType::LOG_INFO, "" + std::to_string(positions[i][0]) + "," + std::to_string(positions[i][1]) + "," + std::to_string(positions[i][2]) + "," + std::to_string(i));
	}
	Logger::Log(EMessageType::LOG_INFO, "---------------------------------");*/
	chunkRender->RegisterQuads(positions, colors, program);
}

Chunk::~Chunk()
{
	for (int i = 0; i < ChunkWidth; i++)
	{
		for (int j = 0; j < ChunkWidth; j++)
		{
			delete ChunkData[i][j];
		}
		delete ChunkData[i];
	}
	delete ChunkData;
}
