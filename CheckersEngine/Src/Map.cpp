#include "Map.h"
#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include <fstream>

Map::Map()
{
	

}
Map::~Map()
{
	
}

//void Map::LoadMap(std::string path, int sizeX, int sizeY)
//{
//	char tile;
//	std::fstream mapFile;
//	mapFile.open(path);
//	int i = 0;
//
//	for (int y = 0; y < sizeY; y++) 
//	{
//		for(int x = 0; x < sizeX; x++)
//		{
//			mapFile.get(tile);
//			Game::AddChecker(atoi(&tile), x * 32, y * 32, i++ );
//			mapFile.ignore();
//	}
//}
//
//
//}