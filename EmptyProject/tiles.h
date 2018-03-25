#pragma once

enum TILE_STATE
{
	TS_NORMAL, TS_BROKEN, TS_EMPTY
};

struct tile
{
	tile();
	~tile();

	bool isTile;
	int item;//현재 받고있는 아이템 효과
	TILE_STATE state;
};

enum TILE_DIR
{
	TD_L, TD_LU, TD_RU, TD_R, TD_RD, TD_LD
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
	bool SetTile(POINT startPos, size_t scale, TILE_DIR dir);
	void SetTile(vector<POINT> tileList, bool isTile = true);
	pair<bool, vector<POINT>> IsSetInTile(POINT pt, size_t scale, TILE_DIR dir);
	TILE_STATE CheckTile(size_t idx);
	bool HitTile(size_t idx);
};
