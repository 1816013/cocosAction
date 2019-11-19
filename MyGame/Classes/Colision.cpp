#include "Colision.h"
#include <algorithm>
#include <array>

USING_NS_CC;


bool Colision::operator()(Sprite & sp, actModule& module) const // “–‚½‚è”»’è
{
	auto directer = Director::getInstance();
	auto map = (TMXTiledMap*)directer->getRunningScene()->getChildByName("backLayer")->getChildByName("mapData");
	auto col = map->getLayer("layer");
	auto mapSize = map->getMapSize();
	auto tileSize = col->getMapTileSize();
	
	Vec2 pos = sp.getPosition();
	Size size = { 60, 120 };
	std::array<Vec2, 2>IDarray;
	/*std::array<Vec2, 3>IDarray;
	IDarray = { ID ,Vec2{0, 0} , mapSize };
	auto minMax = std::minmax_element(IDarray.begin(), IDarray.end());*/
	//if(*minMax.first == Vec2(0, 0) && *minMax.second == mapSize)
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		IDarray[i] = { (pos.x + module.speed.x + module.colSize[i].width) / tileSize.width,
					mapSize.height - ((pos.y + module.speed.x + module.colSize[i].width) / tileSize.height) };	// ÌßÚ²Ô°À•W‚ÌID	

		if (IDarray[i].x < mapSize.width && IDarray[i].y < mapSize.height && IDarray[i].x > 0 && IDarray[i].y > 0)			
		{
			if (col->getTileGIDAt({ IDarray[i].x, IDarray[i].y }) != 0)	// mapTile‚Í0‚ª‹ó”’
			{
				count++;
			}
		}
	}
	if (count >= 2)
	{
		count = 0;
		return false;
	}
	return true;
}

