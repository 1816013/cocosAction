#include "Colision.h"
#include <algorithm>
#include <array>
#include <Unit/Player.h>


USING_NS_CC;

bool Colision::operator()(Sprite & sp, actModule& module) const // 当たり判定
{
	auto directer = Director::getInstance();
	auto map = (TMXTiledMap*)directer->getRunningScene()->getChildByName("flontLayer")->getChildByName("mapData");
	auto col = map->getLayer("footing");
	auto mapSize = map->getMapSize();
	auto tileSize = col->getMapTileSize();
	
	Vec2 pos = sp.getPosition();
	std::array<Vec2, 2>arrayID;
	auto jumpSpeed = 0.0f;
	if (module.actID == ACT_STATE::FALLING || module.actID == ACT_STATE::FALL || module.actID == ACT_STATE::JUMPING)
	{
		jumpSpeed = ((Player&)sp).JumpSpeed();
	}
	
	/*std::array<Vec2, 3>IDarray;
	IDarray = { ID ,Vec2{0, 0} , mapSize };
	auto minMax = std::minmax_element(IDarray.begin(), IDarray.end());*/
	//if(*minMax.first == Vec2(0, 0) && *minMax.second == mapSize)
	for (int i = 0; i < 2; i++)
	{
		// ｺﾘｼﾞｮﾝｵﾌｾｯﾄ
		Vec2 colOffset = { Vec2(module.speed.x + module.colSize[i].width, 
							  module.speed.y + jumpSpeed + module.colSize[i].height) };

		arrayID[i] = { (pos.x + colOffset.x) / tileSize.width,
					mapSize.height - ((pos.y + colOffset.y) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標のID	

		if (arrayID[i].x < mapSize.width && arrayID[i].y < mapSize.height && arrayID[i].x > 0 && arrayID[i].y > 0)			
		{
			if (col->getTileGIDAt({ arrayID[i].x, arrayID[i].y }) != 0)	// mapTileは0が空白
			{
				if (module.actID == ACT_STATE::JUMPING/* || module.actID == ACT_STATE::FALL*/ || module.actID == ACT_STATE::FALLING)	// @変更するかも
				{	
					((Player&)sp).JumpSpeed(-1.0f);	
				}
				return false;
			}
		}
	}
	return true;
}

