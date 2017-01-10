#ifndef GRUB_CHUNKUPDATE
#define GRUB_CHUNKUPDATE
#include <vector>

struct ChunkUpdate
{
	long long int chunkLocation;
	std::vector<long long int> updates;
};
#endif