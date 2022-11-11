#include <experimental/filesystem>

#include "Map.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

inline void testLoadMaps()
{
	MapLoader* loader = new MapLoader();

	std::string path = "C:/Users/Mimi/Documents/GitHub/COMP345/PeaceZone/Map/ConquestMaps";
	int fileCounter = 0;

	for (const auto& entry : std::experimental::filesystem::directory_iterator(path))
	{
		loader->Load(entry.path().u8string());
		fileCounter++;
	}


	std::cout << "Out of the "<< fileCounter <<" maps, only " << loader->maps.size() << " were valid.\n" << std::endl;

	delete loader;
}