#include "Colision.h"
#include <algorithm>
#include <array>
#include <Unit/Player.h>


USING_NS_CC;

bool Colision::operator()(Sprite & sp, actModule& module) const // ìñÇΩÇËîªíË
{
	auto directer = Director::getInstance();
	auto map = (TMXTiledMap*)directer->getRunningScene()->getChildByName("backLayer")->getChildByName("mapData");
	auto col = map->getLayer("layer");
	auto mapSize = map->getMapSize();
	auto tileSize = col->getMapTileSize();
	
	Vec2 pos = sp.getPosition();
	std::array<Vec2, 2>arrayID;
	auto jumpSpeed = 0.0f;
	
	/*std::array<Vec2, 3>IDarray;
	IDarray = { ID ,Vec2{0, 0} , mapSize };
	auto minMax = std::minmax_element(IDarray.begin(), IDarray.end());*/
	//if(*minMax.first == Vec2(0, 0) && *minMax.second == mapSize)
	for (int i = 0; i < 2; i++)
	{
		// ∫ÿºﬁÆ›µÃæØƒ
		Vec2 colOffset = { Vec2(module.speed.x + module.colSize[i].width, 
							  module.speed.y + jumpSpeed + module.colSize[i].height) };

		arrayID[i] = { (pos.x + colOffset.x) / tileSize.width,
					mapSize.height - ((pos.y + colOffset.y) / tileSize.height) };	// Ãﬂ⁄≤‘∞ç¿ïWÇÃID	

		if (arrayID[i].x < mapSize.width && arrayID[i].y < mapSize.height && arrayID[i].x > 0 && arrayID[i].y > 0)			
		{
			if (col->getTileGIDAt({ arrayID[i].x, arrayID[i].y }) != 0)	// mapTileÇÕ0Ç™ãÛîí
			{
				if (module.actID == ACT_STATE::JUMPING || module.actID == ACT_STATE::FALLING)	// @ïœçXÇ∑ÇÈÇ©Ç‡
				{	
					((Player&)sp).JumpSpeed(0.0f);	
					//sp.setPosition(pos.x, pos.y + module.speed.y + module.colSize[0].height);
				}
				return false;
			}
		}
	}
	return true;
}

