#include "TreeDecorator.h"

void TreeDecorator::decorateChunkData(ChunkData * data, FastNoise noise)
{
	for (int i = 0; i < ChunkWidth + 1; i++)
	{
		for (int j = 0; j < ChunkWidth + 1; j++)
		{
			bool tree = false;
			float noiseVal = (noise.GetWhiteNoise(i + data->ChunkX * (ChunkWidth), j + data->ChunkZ * (ChunkWidth)) * 0.5f + 0.5f);
			bool shouldTree = noiseVal < 0.025f;
			unsigned int previous = 0;
			int height = 0;
			for (int k = 0; k < ChunkHeight; k++)
			{
				if (!tree && shouldTree && k < 20 && k > 11)
				{
					unsigned int c = data->values->at(i * (ChunkWidth + 1) * (ChunkHeight + 1) + j * (ChunkHeight + 1) + k);
					if (previous > 0 && c % 255 + (c >> 8) % 255 + (c >> 16) % 255 <= 0)
					{
						tree = true;
					}
					previous = c;
				}

				if (tree)
				{
					if (height < 2)
					{
						height++;
						unsigned int color = 0xf08080;
						data->values->at(i * (ChunkWidth + 1) * (ChunkHeight + 1) + j * (ChunkHeight + 1) + k) = color;
					}
					else if (height < 3)
					{
						height++;
						unsigned int color = 0xaaaaaa;
						data->values->at(i * (ChunkWidth + 1) * (ChunkHeight + 1) + j * (ChunkHeight + 1) + k) = color;
					}
					else if (height < 10)
					{
						height++;
						unsigned int color = 0xf8990e;
						data->values->at(i * (ChunkWidth + 1) * (ChunkHeight + 1) + j * (ChunkHeight + 1) + k) = color;
					}
					else if (height == 10)
					{
						height++;
						unsigned int color = 0x777777;
						data->values->at(i * (ChunkWidth + 1) * (ChunkHeight + 1) + j * (ChunkHeight + 1) + k) = color;
					}
				}
			}
		}
	}
}