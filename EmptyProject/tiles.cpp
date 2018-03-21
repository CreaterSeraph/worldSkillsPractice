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

	startPos.x = startPos.x * 2 + startPos.y % 2;
	if (startPos.x < 0 || startPos.y < 0 || startPos.x >= 20 || startPos.y >= 10) return false;
	if (dir >= 6 || dir < 0) return false;

	POINT ptList[maxSize];
	ptList[0] = startPos;
	if (m_arrTile[startPos.x / 2 + startPos.y * 10].objNum) return false;
	for (int i = 1; i < scale; i++)
	{
		startPos.x += *("124542" + dir) - '3';
		startPos.y += *("211233" + dir) - '2';
		if (startPos.x < 0 || startPos.y < 0 || startPos.x >= 20 || startPos.y >= 10) return false;
		if (m_arrTile[startPos.x / 2 + startPos.y * 10].objNum) return false;

		ptList[i] = startPos;
	}

	for (int i = 0; i < scale; i++)
	{
		POINT pt = ptList[i];
		pt.x /= 2;
		m_arrTile[GetIdx(pt)].objNum = objNum;
	}

	return true;
}

TILE_STATE tiles::CheckTile(size_t idx)
{
	return m_arrTile[idx].state;
}

bool tiles::HitTile(size_t idx)
{
	if (m_arrTile[idx].state != TS_NORMAL) return false;
	m_arrTile[idx].state = TS_EMPTY;
}
