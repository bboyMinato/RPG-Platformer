#pragma once
#include <string>
#include <vector>
#include "Layer.h"
#include "TextureManager.h"

struct TileSet
{
	int firstID, lastID;
	int rowCount, colCount;
	int tileCount, tileSize;
	std::string name, source;
};

using TileSetList = std::vector<TileSet>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer : public Layer
{
public:
	TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TileSetList tilesets);
	virtual void Render();
	virtual void Update();
	inline TileMap GetTileMap() { return _tileMap; }

private:
	int _tileSize;
	int _rowCount, _colCount;
	TileMap _tileMap;
	TileSetList _tileSets;
};

