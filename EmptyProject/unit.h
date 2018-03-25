#pragma once

struct Units
{
	Units(vector<POINT>&& ptList, const POINT& renderPos);

	vector<POINT> ptList;
	POINT renderPos;

	void Render(LPD3DXSPRITE sprite, weak_ptr<texture> renderTexture, const D3DXVECTOR2& pos, double time, const D3DXMATRIX& mat);
};

class cArmy
{
private:
	vector<Units> vArmy;

	shared_ptr<texture> image;
	shared_ptr<texture> deathImage;

	D3DXVECTOR2 startPos;
public:
	cArmy(shared_ptr<texture> image, const D3DXVECTOR2& pos);

	void Render(LPD3DXSPRITE sprite, double time, const D3DXMATRIX& mat);
	void AddUnit(const Units& unit);
	bool Hit(const POINT& pt);
};