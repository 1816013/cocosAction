#include "Colision.h"

bool Colision::operator()(const Vec2 ID, TMXLayer & col, const Size mapTile) const
{
	if (ID.x < mapTile.width && ID.y < mapTile.height && ID.x > 0 && ID.y > 0)
	{
		if (col.getTileGIDAt({ ID.x, ID.y }) == 0)	// mapTile‚Í0‚ª‹ó”’
		{
			return true;
		}
	}
	return false;
}

