#include "TestChunkGenerator.h"
const float octave1 = 1.0f;
const float octave2 = 0.5f;
const float octave3 = 0.25f;
const float octave4 = 4.0f;
const float octave5 = 2.0f;
const float octave6 = 8.0f;
void TestChunkGenerator::generateChunkData(ChunkData* data, FastNoise noise)
{
	for (int i = 0; i < ChunkWidth + 1; i++)
	{
		for (int j = 0; j < ChunkWidth + 1; j++)
		{
			float noiseH = (noise.GetGradientFractal((i + ChunkWidth * data->ChunkX) * octave1, (j + ChunkWidth * data->ChunkZ) * octave1) * 0.75f + 0.25f) * (float)ChunkHeight * 1.0f;
			noiseH *= (noise.GetGradientFractal((i + ChunkWidth * data->ChunkX) * octave2, (j + ChunkWidth * data->ChunkZ) * octave2) * 0.5f + 0.5f);
			float biome = (noise.GetNoise((i + ChunkWidth * data->ChunkX) * octave3, (j + ChunkWidth * data->ChunkZ) * octave3) * 0.5f + 0.5f);
			biome *= 2.25;
			biome *= biome;
			biome *= 0.44444444f;
			biome = glm::sqrt(biome);
			noiseH *= biome;
			noiseH *= (noise.GetGradientFractal((i + ChunkWidth * data->ChunkX) * octave4, (j + ChunkWidth * data->ChunkZ) * octave4) * 0.5f + 1.0f);
			noiseH *= (noise.GetGradientFractal((i + ChunkWidth * data->ChunkX) * octave5, (j + ChunkWidth * data->ChunkZ) * octave5) * 0.25f + 1.0f);
			noiseH *= (noise.GetGradientFractal((i + ChunkWidth * data->ChunkX) * octave6, (j + ChunkWidth * data->ChunkZ) * octave6) * 0.125f + 1.0f);
			//noiseH *= (noise.GetNoise((i + ChunkWidth * ChunkX) * 0.25f, (j + ChunkWidth * ChunkZ) * 0.25f) * 0.25f + 0.75f);
			for (int k = 0; k < ChunkHeight + 1; k++)
			{
				//if (noiseH >= k - 2 && noiseH <= k)
				if (noiseH >= k)
				{
					unsigned int color = 0;

					if (k > 20)
					{
						if (k >= 50)
						{
							color = 0xEEEEFF;
						}
						else
						{
							color += ((unsigned int)(170 - (noiseH / (float)ChunkHeight) * 255.0f) % 255) << 16;
							color += ((unsigned int)(170 - (noiseH / (float)ChunkHeight) * 255.0f) % 255) << 8;
							color += ((unsigned int)(170 - (noiseH / (float)ChunkHeight) * 255.0f) % 255);
						}
					}
					else if (k <= 10)
					{
						color += ((unsigned int)(255 - (noiseH / (float)ChunkHeight) * 255.0f) % 255) << 16;
						color += ((unsigned int)(255 - (noiseH / (float)ChunkHeight) * 255.0f) % 255) << 8;
						color += ((unsigned int)(225 - (noiseH / (float)ChunkHeight) * 255.0f) % 255);
					}
					else
					{
						color += 0 << 16;
						color += ((unsigned int)(150 - (noiseH / (float)ChunkHeight) * 255.0f) % 255) << 8;
						color += 0;
					}
					
					//float noiseC = noise.GetGradient((i + ChunkWidth * n) * 10.0f, (k)* 10.0f, (j + ChunkWidth * m) * 10.0f);
					data->values->push_back(color);
				}
				else if (k <= (ChunkHeight + 1) / 32)
				{
					unsigned int color = 0;
					color += 0 << 16;
					color += 0 << 8;
					color += ((unsigned int)(160 + (noiseH / (float)ChunkHeight) * 255.0f) % 255);
					data->values->push_back(color);
				}
				else
					data->values->push_back(0);
			}
		}
	}
}