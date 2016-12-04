#include "CubicChunkMesher.h"

void CubicChunkMesher::MeshChunk(ChunkData* data, Primitive p)
{
	data->vertices = new std::vector<Vector3>(); // Positions
	data->colors = new std::vector<Vector3>();
	for (int i = 0; i < ChunkWidth; i++)
	{
		for (int j = 0; j < ChunkWidth; j++)
		{
			for (int k = 0; k < ChunkHeight; k++)
			{
				unsigned int c = data->values->at(i * (ChunkWidth+1) * (ChunkHeight+1)+j * (ChunkHeight+1)+k);
				//Logger::Log(EMessageType::LOG_INFO, ""+std::to_string(c));
				if (c > 0)
				{
					float ChunkPosX = data->ChunkX * ChunkWidth * BlockWidth * 2.0f;
					float ChunkPosZ = data->ChunkZ * ChunkWidth * BlockWidth * 2.0f;
					float xOffset = i * BlockWidth * 2.0f;
					float yOffset = k * BlockHeight * 2.0f;
					float zOffset = j * BlockWidth * 2.0f;
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)+BlockWidth, yOffset+BlockHeight, (zOffset+ChunkPosZ)-BlockWidth)); //0
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)+BlockWidth, yOffset+BlockHeight, (zOffset+ChunkPosZ)+BlockWidth)); //1
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)-BlockWidth, yOffset+BlockHeight, (zOffset+ChunkPosZ)+BlockWidth)); //2
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)-BlockWidth, yOffset+BlockHeight, (zOffset+ChunkPosZ)-BlockWidth)); //3
					//vertices->push_back(Vector3((xOffset+ChunkPosX)+BlockWidth, yOffset-BlockHeight, (zOffset +ChunkPosZ)-BlockWidth)); //4
					//vertices->push_back(Vector3((xOffset+ChunkPosX)+BlockWidth, yOffset-BlockHeight, (zOffset +ChunkPosZ)+BlockWidth)); //5
					//vertices->push_back(Vector3((xOffset+ChunkPosX)-BlockWidth, yOffset-BlockHeight, (zOffset +ChunkPosZ)+BlockWidth)); //6
					//vertices->push_back(Vector3((xOffset+ChunkPosX)-BlockWidth, yOffset-BlockHeight, (zOffset +ChunkPosZ)-BlockWidth)); //7
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)+BlockWidth, yOffset-BlockHeight, (zOffset+ChunkPosZ)+BlockWidth)); //8
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)+BlockWidth, yOffset+BlockHeight, (zOffset+ChunkPosZ)+BlockWidth)); //9
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)+BlockWidth, yOffset+BlockHeight, (zOffset+ChunkPosZ)-BlockWidth)); //10
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)+BlockWidth, yOffset-BlockHeight, (zOffset+ChunkPosZ)-BlockWidth)); //11
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)-BlockWidth, yOffset-BlockHeight, (zOffset+ChunkPosZ)+BlockWidth)); //12
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)-BlockWidth, yOffset+BlockHeight, (zOffset+ChunkPosZ)+BlockWidth)); //13
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)-BlockWidth, yOffset+BlockHeight, (zOffset+ChunkPosZ)-BlockWidth)); //14
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)-BlockWidth, yOffset-BlockHeight, (zOffset+ChunkPosZ)-BlockWidth)); //15
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)-BlockWidth, yOffset+BlockHeight, (zOffset+ChunkPosZ)+BlockWidth)); //16
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)+BlockWidth, yOffset+BlockHeight, (zOffset+ChunkPosZ)+BlockWidth)); //17
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)+BlockWidth, yOffset-BlockHeight, (zOffset+ChunkPosZ)+BlockWidth)); //18
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)-BlockWidth, yOffset-BlockHeight, (zOffset+ChunkPosZ)+BlockWidth)); //19
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)-BlockWidth, yOffset+BlockHeight, (zOffset+ChunkPosZ)-BlockWidth)); //20
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)+BlockWidth, yOffset+BlockHeight, (zOffset+ChunkPosZ)-BlockWidth)); //21
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)+BlockWidth, yOffset-BlockHeight, (zOffset+ChunkPosZ)-BlockWidth)); //22
					data->vertices->push_back(Vector3((xOffset+ChunkPosX)-BlockWidth, yOffset-BlockHeight, (zOffset+ChunkPosZ)-BlockWidth)); //23
					for (int n = 0; n < 20; n++)
					{
						data->colors->push_back(Vector3(c % 255, (c << 8) % 255, (c << 16) % 255));
					}
				}
			}
		}
	}
}