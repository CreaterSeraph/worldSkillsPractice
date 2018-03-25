#pragma once

struct Units
{
	Units(shared_ptr<texture> image);

	void InitPos(const vector<POINT>& ptList, const POINT& renderPos);
	void ResetPos();

	vector<POINT> ptList;
	POINT renderPos;

	shared_ptr<texture> image;

	void Render(LPD3DXSPRITE sprite, const D3DXVECTOR2& pos, double time, const D3DXMATRIX& mat);
};

class cArmy
{
private:
	vector<Units> vArmy;

	D3DXVECTOR2 startPos;
public:
	cArmy(const D3DXVECTOR2& pos);

	void Render(LPD3DXSPRITE sprite, double time, const D3DXMATRIX& mat);
	void AddUnit(const Units& unit);
	bool Hit(const POINT& pt);
};