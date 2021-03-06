#include "DXUT.h"
#include "tiles.h"


tile::tile()
	:isTile(false), item(0), state(TS_NORMAL)
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

bool tiles::SetTile(POINT startPos, size_t scale, TILE_DIR dir)
{
	constexpr int maxSize = 5;
	assert(scale > maxSize);

	startPos.x = startPos.x * 2 + startPos.y % 2;
	if (startPos.x < 0 || startPos.y < 0 || startPos.x >= 20 || startPos.y >= 10) return false;
	if (dir >= 6 || dir < 0) return false;

	POINT ptList[maxSize];
	ptList[0] = startPos;
	if (m_arrTile[startPos.x / 2 + startPos.y * 10].isTile) return false;
	for (int i = 1; i < scale; i++)
	{
		startPos.x += *("124542" + dir) - '3';
		startPos.y += *("211233" + dir) - '2';
		if (startPos.x < 0 || startPos.y < 0 || startPos.x >= 20 || startPos.y >= 10) return false;
		if (m_arrTile[startPos.x / 2 + startPos.y * 10].isTile) return false;

		ptList[i] = startPos;
	}

	for (int i = 0; i < scale; i++)
	{
		POINT pt = ptList[i];
		pt.x /= 2;
		m_arrTile[GetIdx(pt)].isTile = true;
	}

	return true;
}

void tiles::SetTile(vector<POINT> tileList, bool isTile)
{
	for (auto iter : tileList)
		m_arrTile[GetIdx(iter)].isTile = isTile;
}

pair<bool, vector<POINT>> tiles::IsSetInTile(POINT pt, size_t scale, TILE_DIR dir)
{
	bool result = true;
	pt.x = pt.x * 2 + (unsigned)pt.y % 2;
	if (dir >= 6 || dir < 0) result = false;

	vector<POINT> ptList;
	ptList.resize(scale);
	ptList[0] = pt;
	if (pt.x < 0 || pt.y < 0 || pt.x >= 20 || pt.y >= 10) result = false;
	else if (m_arrTile[pt.x / 2 + pt.y * 10].isTile) result = false;
	for (int i = 1; i < scale; i++)
	{
		pt.x += *("124542" + dir) - '3';
		pt.y += *("211233" + dir) - '2';
		if (pt.x < 0 || pt.y < 0 || pt.x >= 20 || pt.y >= 10) result = false;
		else if (m_arrTile[pt.x / 2 + pt.y * 10].isTile) result = false;

		ptList[i] = pt;
	}

	for (int i = 0; i < scale; i++)
	{
		if (ptList[i].x < 0)
			ptList[i].x -= 1;
		ptList[i].x /= 2;
	}

	return make_pair(result, ptList);
}

TILE_STATE tiles::CheckTile(size_t idx)
{
	return m_arrTile[idx].state;
}

bool tiles::HitTile(size_t idx)
{
	if (m_arrTile[idx].state != TS_NORMAL) return false;
	m_arrTile[idx].state = TS_EMPTY;
	return true;
}
