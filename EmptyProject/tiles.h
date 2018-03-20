#pragma once

enum TILE_STATE
{
	TS_NORMAL, TS_BROKEN, TS_EMPTY
};

struct tile
{
	tile();
	~tile();

	int objNum;//깔린 오브젝트 번호라던가...
	int item;//현재 받고있는 아이템 효과
	TILE_STATE state;
};

enum TILE_DIR
{
	TD_U, TD_RU, TD_RD, TD_D, TD_LD, TD_LU
};

class tiles
{
private:
	array<tile, 100> m_arrTile;

	int GetIdx(const POINT& pt);
public:
	tiles();
	~tiles();

	array<tile, 100>& GetTiles() { return m_arrTile; }
	bool SetTile(POINT startPos, size_t scale, TILE_DIR dir, int objNum);
	TILE_STATE CheckTile(const POINT& pt);
	void HitTile(const POINT& pt);
};
