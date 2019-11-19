#include "Colision.h"
#include <algorithm>
#include <array>
#include <_debug/_DebugConOut.h>

USING_NS_CC;


bool Colision::operator()(Sprite & sp, actModule& module) const // 当たり判定
{
	auto directer = Director::getInstance();
	auto map = (TMXTiledMap*)directer->getRunningScene()->getChildByName("backLayer")->getChildByName("mapData");
	auto col = map->getLayer("layer");
	auto mapSize = map->getMapSize();
	auto tileSize = col->getMapTileSize();
	
	Vec2 pos = sp.getPosition();
	std::array<Vec2, 2>IDarray;
	/*std::array<Vec2, 3>IDarray;
	IDarray = { ID ,Vec2{0, 0} , mapSize };
	auto minMax = std::minmax_element(IDarray.begin(), IDarray.end());*/
	//if(*minMax.first == Vec2(0, 0) && *minMax.second == mapSize)
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		IDarray[i] = { (pos.x + module.speed.x + module.colSize[i].width) / tileSize.width,
					mapSize.height - ((pos.y + module.speed.y + module.colSize[i].height) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標のID	

		if (IDarray[i].x < mapSize.width && IDarray[i].y < mapSize.height && IDarray[i].x > 0 && IDarray[i].y > 0)			
		{
			if (col->getTileGIDAt({ IDarray[i].x, IDarray[i].y }) != 0)	// mapTileは0が空白
			{
				return false;
			}
		}
	}
	return true;
}

