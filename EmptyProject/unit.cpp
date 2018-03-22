#include "DXUT.h"
#include "unit.h"

unit::unit(const D3DXVECTOR2& offset)
	:offset(offset)
{
}

unit::~unit()
{
}

void unit::Render(LPD3DXSPRITE sprite, weak_ptr<texture> renderTexture, const D3DXVECTOR2& pos, double time, const D3DXMATRIX& mat)
{
	renderTexture.lock()->Render(sprite, pos + offset, mat);
}

void Units::Render(LPD3DXSPRITE sprite, weak_ptr<texture> renderTexture, double time, const D3DXMATRIX& mat)
{
	for (auto iter : units)
	{
		iter.Render(sprite, renderTexture, D3DXVECTOR2(0, 0), time, mat);
	}
}

Units::Units()
{
}

void cArmy::Render(LPD3DXSPRITE sprite, double time, const D3DXMATRIX& mat)
{
	for (auto iter : vArmy)
		iter.Render(sprite, image, time, mat);
}
