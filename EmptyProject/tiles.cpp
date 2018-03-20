#include "DXUT.h"
#include "tiles.h"


tile::tile()
	:objNum(0), item(0), state(TS_NORMAL)
{
}


tile::~tile()
{
}

tiles::tiles()
{
}

tiles::~tiles()
{
}

int tiles::GetIdx(const POINT& pt)
{
	return pt.y * 10 + pt.x;
}

bool tiles::SetTile(POINT startPos, size_t scale, TILE_DIR dir, int objNum)
{
	const int maxSize = 5;

	cin >> startPos.x >> startPos.y;
	startPos.y = startPos.y * 2 + startPos.x % 2;
	if (startPos.x < 0 || startPos.y < 0 || startPos.x >= 10 || startPos.y >= 20) return false;
	if (scale > maxSize + 1) return false;
	if (dir > 6 || dir < 0) return false;

	POINT ptList[maxSize];
	ptList[0] = startPos;
	for (int i = 1; i < scale; i++)
	{
		startPos.x += *("bccbaa" + dir) - 'b';
		startPos.y += *("abdedb" + dir) - 'c';
		if (startPos.x < 0 || startPos.y < 0 || startPos.x >= 10 || startPos.y >= 20) return false;
		if (m_arrTile[startPos.x + startPos.y / 2 * 10].objNum) return false;

		ptList[i] = startPos;
	}

	for (int i = 0; i < scale; i++)
	{
		POINT pt = ptList[i];
		pt.y /= 2;
		m_arrTile[GetIdx(pt)].objNum = objNum;
	}

	return true;
}

TILE_STATE tiles::CheckTile(const POINT& pt)
{
	return m_arrTile[GetIdx(pt)].state;
}