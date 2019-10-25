#include "Colision.h"
#include <algorithm>
#include <array>

USING_NS_CC;


bool Colision::operator()(Sprite & sp, TMXTiledMap & map, Size distance) const // “–‚½‚è”»’è
{
	auto col = map.getLayer("footing");
	auto mapSize = map.getMapSize();
	auto tileSize = col->getMapTileSize();
	
	Vec2 pos = sp.getPosition();
	Size size = { 60, 120 };
	
	Vec2 ID = { (pos.x + distance.width) / tileSize.width,
				mapSize.height - ((pos.y + distance.height) / tileSize.height) };	// ÌßÚ²Ô°À•W‚ÌID	
	/*std::array<Vec2, 3>IDarray;
	IDarray = { ID ,Vec2{0, 0} , mapSize };
	auto minMax = std::minmax_element(IDarray.begin(), IDarray.end());*/
	if (ID.x < mapSize.width && ID.y < mapSize.height && ID.x > 0 && ID.y > 0)
	//if(*minMax.first == Vec2(0, 0) && *minMax.second == mapSize)
	{
		if (col->getTileGIDAt({ ID.x, ID.y }) == 0)	// mapTile‚Í0‚ª‹ó”’
		{
			return true;
		}
	}
	return false;
}

