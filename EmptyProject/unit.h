#pragma once
struct unit
{
	D3DXVECTOR2 offset;

	unit(const D3DXVECTOR2& offset);
	~unit();

	void Render(LPD3DXSPRITE sprite, weak_ptr<texture> renderTexture, const D3DXVECTOR2& pos, double time, const D3DXMATRIX& mat);
};

struct Units
{
	vector<unit> units;

	bool isLive;
	POINT position;

	double shakeLen;

	void Render(LPD3DXSPRITE sprite, weak_ptr<texture> renderTexture, double time, const D3DXMATRIX& mat);
	Units();
};

class cArmy
{
private:
	vector<Units> vArmy;

	shared_ptr<texture> image;

	D3DXVECTOR2 startPos;
public:
	void Render(LPD3DXSPRITE sprite, double time, const D3DXMATRIX& mat);
};